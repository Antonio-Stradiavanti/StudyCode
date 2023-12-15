#pragma once
#include <string>
#include <vector>
#include <exception>

using namespace System;
using Collections::Generic::List;

ref class Product;
/* Сохраняет сообщения о сработавших событиях в файл, с использованием System::IO::StreamWriter, ведет лог. */
ref class EventLogger {

public:
  static void log(String^ message) {
	DateTime curDate = DateTime::Now;
	Globalization::CultureInfo^ ci = gcnew Globalization::CultureInfo("ru-RU");

	String^ fileName = Convert::ToString(curDate.Day) + "_" + Convert::ToString(curDate.Month) + "_" + Convert::ToString(curDate.Year) + "_event_log.txt";

	try {
	  IO::FileStream^ fs = gcnew IO::FileStream(
		fileName, IO::FileMode::Append,
		IO::FileAccess::Write,
		IO::FileShare::Read
	  );
	  // Принимает текст и преобразует его в поток байт.
	  IO::StreamWriter^ sw = gcnew IO::StreamWriter(fs);

	  sw->WriteLine("[ << ] В момент {0} , произошло событие : {1}", curDate.ToString(ci), message);

	  sw->Flush();
	  sw->Close();

	}
	catch (Exception^ e) {
	  Console::WriteLine("[ ! ] Что-то пошло не так, выведем сообщение об ошибке:\n{0}.", e->ToString());
	}


  }

};

delegate void CreateProductHandler();
delegate void EditProductHandler(Product^);
delegate void DeleteProductHandler(Product^);

// Источник событий, в нем нужно объявить события
ref class Product {
public:

  // В ид. описываем при каких условиях вызываем
  event CreateProductHandler^ OnCreateProduct;
  event EditProductHandler^ OnEditProduct;
  event DeleteProductHandler^ OnDeleteProduct;

  // Объявим методы, вызывающие события
  void fireCreateProduct() {
	OnCreateProduct();
  }
  void fireEditProduct(Product^ p) {
	OnEditProduct(p);
  }
  void fireDeleteProduct(Product^ p) {
	OnDeleteProduct(p);
  }

  Product() : price{}, weight{}, id{} {
	name = "";
	manufactured = gcnew DateTime();
  }

  Product(String^ name, DateTime^ manufactured, double price, double weight) : name{ name }, manufactured{ manufactured }, price{ price }, weight{ weight }
  {
	Random^ rnd = gcnew Random();
	id = rnd->Next(1000000000, Int32::MaxValue - 1);
  }

  void setName(String^ name) { this->name = name; }
  void setManufactured(DateTime^ manufactured) { this->manufactured = manufactured; }
  void setPrice(Double price) { this->price = price; }
  void setWeight(Double weight) { this->weight = weight; }

  String^ getName() { return name; }
  DateTime^ getManufactured() { return manufactured; }
  Double getPrice() { return price; }
  Double getWeight() { return weight; }
  Int32 getId() { return id; }


  void input() {

	Random^ rnd = gcnew Random();
	id = rnd->Next(1000000000, Int32::MaxValue - 1);

	Console::WriteLine("[ 1.] Введите Название товара :");
	Console::Write("[ >> ] ");  name = Console::ReadLine();

	Int32 year, month, day;

  label:
	try {
	  Console::WriteLine("[ 2.] Введите дату производства товара :");

	  Console::Write("[ >> ] Год = ");
	  year = Convert::ToInt32(Console::ReadLine());

	  Console::Write("[ >> ] Месяц = ");
	  month = Convert::ToInt32(Console::ReadLine());

	  Console::Write("[ >> ] День = ");
	  day = Convert::ToInt32(Console::ReadLine());

	  manufactured = gcnew DateTime(year, month, day);

	} catch (System::ArgumentOutOfRangeException^ e) {
	  Console::WriteLine("[ ! ] Вы ввели некорректную дату, попробуйте еще раз.");
	  goto label;
	}

  label1:
	try {
	  Console::WriteLine("[ 3.] Укажите цену товара в рублях");
	  Console::Write("[ >> ] Цена = "); price = Convert::ToDouble(Console::ReadLine());

	  Console::WriteLine("[ 4.] Укажите вес товара в граммах");
	  Console::Write("[ >> ] Вес = "); weight = Convert::ToDouble(Console::ReadLine());
	} catch (FormatException^ e) {
	  Console::WriteLine("[ ! ] Вы ввели некорректные данные, их нельзя преобразовать в вещественный тип, попробуйте еще раз.");
	  goto label1;
	}
	

  }

  void print(int width) {
	Globalization::CultureInfo^ ci = gcnew Globalization::CultureInfo("ru-RU");
	String ^pad = "", ^padding = pad->PadLeft(width);
	Console::WriteLine(padding + "{{\n\n" + padding + "\"id\" : \"{0}\",\n" + padding + "\"Наименование\" : \"{1}\",\n" + padding + "\"Дата производства\" : \"{2}\",\n" + padding + "\"Цена товара\" : \"{3}\"\n" + padding + "\"Вес товара\" : \"{4}г.\".\n\n" + padding + "}};", id, name, manufactured->ToString("d", ci), price.ToString("C", ci), weight);

  }


private:

  Int32 id;
  String^ name;
  DateTime^ manufactured;

  Double price;
  Double weight;

};

// Объявляю сигнатуры обработчиков событий
/* Получатель событий */
ref class Warehouse
{
public:

  Warehouse(Product^ src, String^ name) : name{name}
  {
	if (src == nullptr) {
	  throw gcnew ArgumentNullException("[ ! ] Товар несуществует.");
	}
	theSource = src;
	products = gcnew List< Product^ >();

	productSearchCriteria = 0;
	matchProduct = gcnew Predicate<Product^>(this, &Warehouse::findProdcutById);

	// Связываем добавляем обработчики в списки вызовов делегатов.
	src->OnCreateProduct += gcnew CreateProductHandler(this, &Warehouse::createProduct);
	src->OnEditProduct += gcnew EditProductHandler(this, &Warehouse::editProduct);
	src->OnDeleteProduct += gcnew DeleteProductHandler(this, &Warehouse::deleteProduct);

  }

  void setName(String^ name) { this->name = name; }

  String^ getName() { return name; }
  Int32 getCount() { return products->Count; }
  List< Product^ >^ getProducts() { return products; }

  void print(int width) {
	String ^pad = "", ^padding = pad->PadLeft(width);
	Console::WriteLine(padding + "\"Название склада\" : \"{0}\" {{\n\n" + padding + padding + "\"Число товаров\" : \"{1}\";\n", name, products->Count);
	for each (Product^ p in products) {
	  p->print(width + 2);
	}
	Console::WriteLine("\n" + padding + "};");
  }

  Product^ find(Int32 id) {
	productSearchCriteria = id;
	return products->Find(matchProduct);
  }

  // Объявляем обработчиков событий
  // TODO реализовать логику
  void createProduct() {
	Product^ pr = gcnew Product();
	pr->input();
	products->Add(pr);
	Console::WriteLine("[ Обработчик события CreateProduct ] [ V ] Товар p с идентификатором {0} успешно добавлен.", pr->getId());
	EventLogger::log("создан товар с идентификатором " + Convert::ToString(pr->getId()));
  }
  void editProduct(Product^ p) {

	Int32 c; String^ s;
	Int32 day, month, year;
	Double tmpPrice, tmpWeight;

	try {

	  Console::WriteLine("[ << ] Какое из свойств вы хотите изменить : {\n  1 -> Изменить название товара\n  2 -> Изменить дату производства\n  3 -> Изменить цену товара\n  4 -> Изменить вес товара\n  5 -> Изменить все свойства товара\n  6 -> Завершить операцию. \n}\n");
	  Console::Write("[ >> ] "); c = Convert::ToInt32(Console::ReadLine());

	  switch (c) {
	  case 1:
		Console::WriteLine("[ << ] Введите Наименование товара ( Текущее Наименование = {0} )", p->getName());
		Console::Write("[ >> ] Новое Наменование = "); s = Console::ReadLine(); p->setName(s);
		break;
	  case 2:

		Console::WriteLine("[ << ] Введите Новую Дату производства товара ( Текущая Дата производства  = {0} )", p->getManufactured());
		
		Console::Write("[ >> ] Год = ");
		year = Convert::ToInt32(Console::ReadLine());

		Console::Write("[ >> ] Месяц = ");
		month = Convert::ToInt32(Console::ReadLine());

		Console::Write("[ >> ] День = ");
		day = Convert::ToInt32(Console::ReadLine());

		p->setManufactured(gcnew DateTime(year, month, day));

		break;
	  case 3:
		Console::WriteLine("[ << ] Введите Новую Цену товара в рублях ( Текущая Цена товара = {0} )", p->getPrice());
		Console::Write("[ >> ] Цена = "); tmpPrice = Convert::ToDouble(Console::ReadLine()); p->setPrice(tmpPrice);
		break;
	  case 4:
		Console::WriteLine("[ << ] Введите Новый Вес товара ( Текущая Вес товара = {0} )", p->getWeight());
		Console::Write("[ >> ] Вес = "); tmpWeight = Convert::ToDouble(Console::ReadLine()); p->setWeight(tmpWeight);
		break;
	  case 5:
		Console::WriteLine("[ << ] Обновим все свойства товара :");
		p->input();
		break;
	  case 6:
		Console::WriteLine("[ V ] Редактирование товара успешно завершено.");
		return;
	  default:
		Console::WriteLine("[ ? ] Такого свойства нет, отмена операции ...");
		break;
	  }

	} catch (FormatException^ e) {
	  Console::WriteLine("[ ! ] Вы ввели неккоректные данные, их невозможно преобразовать к числу. Отмена операции.");
	} catch (System::ArgumentOutOfRangeException^ e) {
	  Console::WriteLine("[ ! ] Вы ввели некорректную дату. Отмена операции");
	}

	EventLogger::log("в запись товара с идентфикатором : " + Convert::ToString(p->getId()) + " внесены изменения");

  }

  
  
  void deleteProduct(Product^ p) {
	EventLogger::log("удалена запись товара с идентфикатором : " + Convert::ToString(p->getId()));
	products->Remove(p);
	Console::WriteLine("[ Обработчик события DeleteProduct ] [ V ] Операция успешно выполнена.");

  }

private:

  bool findProdcutById(Product^ pr) {
	return pr->getId() == productSearchCriteria ? true : false;
  }

  String^ name;

  Int32 productSearchCriteria;
  Predicate<Product^>^ matchProduct;

  Product^ theSource;
  List< Product^ >^ products;
};
/* Соединим события и методы, их обр. */
ref class ManufacturerInventory {

public:

  ManufacturerInventory() {
	name = "";
	init();
  }
  ManufacturerInventory(String^ name) : name{ name }
  {
	init();
  }

  void print() {
	Console::WriteLine("[ << ] Выведем перечень товаров\n\n***\n\n\"Имя Производителя\" : \"{0}\" {{\n", name);
	for each (Warehouse^ wh in warehouses) {
	  wh->print(2);
	}
	Console::WriteLine("};\n\n***");
  }

  void add() {
	wh = findWarehouse("создадим новый склад");
	
	if (wh == nullptr) {
	  Console::WriteLine("[ << ] Создадим новый склад.");

	  rcv = gcnew Warehouse(src, warehouseSearchCriteria);
	  warehouses->Add(rcv);
	}

	warehouses[warehouses->IndexOf(rcv)]->createProduct();

  }

  void remove() {
	wh = findWarehouse("операция будет немедленно завершена");
	if (wh == nullptr) {
	  Console::WriteLine("[ ! ] Склад не найден.");
	  return;
	}
	rcv = wh;
	Console::WriteLine("[ V ] Склад {0} -> найден, Текущее Количество товаров : {1}", rcv->getName(), rcv->getCount());

	Int32 c, id;
	label:
	Console::WriteLine("[ << ] Что вы хотите сделать : { 1 -> удалить товар, 2 -> удалить склад, 3 -> вывести список товаров. }");
	try {
	  Console::Write("[ >> ] "); c = Convert::ToInt32(Console::ReadLine());
	  switch (c) {
	  case 1:
		Console::WriteLine("[ << ] Введите id товара :");
		Console::Write("[ >> ] "); id = Convert::ToInt32(Console::ReadLine());
		pr = rcv->find(id);

		if (pr == nullptr) {
		  Console::WriteLine("[ ! ] Товар НЕ найден.");
		} else {
		  Console::WriteLine("[ V ] Товар найден, удалим его.");
		  src->fireDeleteProduct(pr);
		}

		break;
	  case2:
		rcv->getProducts()->Clear();
		warehouses->Remove(rcv);
		Console::WriteLine("[ V ] Склад успешно удален.");
		break;
	  case 3:
		rcv->print(2);
		goto label;
		break;
	  default:
		Console::WriteLine("[ ! ] Нет такой команды. Отмена операции.");
	  }
	} catch (FormatException^ e) {
	  Console::WriteLine("[ ! ] Введены некорректные данные. Отмена операции.");
	}

  }

  void edit() {
	wh = findWarehouse("операция будет немедленно завершена");

	if (wh == nullptr) {
	  Console::WriteLine("[ ! ] Склад не найден.");
	  return;
	}

	rcv = wh;
	Console::WriteLine("[ V ] Склад {0} -> найден выведем список товаров.", rcv->getName());
	rcv->print(2);

	Int32 id;
	Console::WriteLine("[ << ] Введите id товара :");
	Console::Write("[ >> ] "); id = Convert::ToInt32(Console::ReadLine());
	pr = rcv->find(id);
	
	if (pr == nullptr) {
	  Console::WriteLine("[ ! ] Товар НЕ найден.");
	}
	else {
	  Console::WriteLine("[ V ] Товар найден, отредактируем его.\n");
	  src->fireEditProduct(pr);
	  Console::WriteLine("\n[ V ] Товар успешно отредактирован.");
	}
  }

private:

  bool findWareHouseByName(Warehouse^ wh) {
	return wh->getName() == warehouseSearchCriteria ? true : false;
  }
  
  Warehouse^ findWarehouse(String^ pr) {
	Warehouse^ wh = nullptr;
	Console::WriteLine("[ << ] Введите название склада, если указаный склад будет отсутствовать в перечне, то {0}.", pr);
	String^ warehouseName;
	Console::Write("[ >> ] "); warehouseName = Console::ReadLine();
	warehouseSearchCriteria = warehouseName;
	wh = warehouses->Find(matchWarehouse);

	return wh;
  }

  void init() {
	matchWarehouse = gcnew Predicate<Warehouse^>(this, &ManufacturerInventory::findWareHouseByName);

	warehouseSearchCriteria = "";

	src = gcnew Product();
	rcv = gcnew Warehouse(src, name);
	
	wh = nullptr;
	pr = nullptr;

	warehouses = gcnew List< Warehouse^ >();
  }

  String^ name;

  Warehouse^ wh;
  Product^ pr;

  Product^ src;
  Warehouse^ rcv;
  String^ warehouseSearchCriteria;

  Predicate<Warehouse^>^ matchWarehouse;

  List< Warehouse^ >^ warehouses;

};