#pragma once
#include <string>
#include <vector>
#include <exception>

using namespace System;
using Collections::Generic::List;

ref class Product;

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
	Console::WriteLine("[ 2.] Введите дату производства товара :");
	try {
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
	  Console::Write("[ >> ] Цена = ");  price = Convert::ToDouble(Console::ReadLine());

	  Console::WriteLine("[ 4.] Укажите вес товара в граммах");
	  Console::Write("[ >> ] Вес = "); weight = Convert::ToDouble(Console::ReadLine());
	
	} catch(FormatException^ e) {
	  Console::WriteLine("[ ! ] Вы ввели некорректные данные, их нельзя преобразовать в вещественный тип, попробуйте еще раз.");
	  goto label1;
	}


  }

  void print(int width) {
	Globalization::CultureInfo^ ci = gcnew Globalization::CultureInfo("ru-RU");
	String ^pad = "", ^padding = pad->PadLeft(width);
	Console::WriteLine(padding + "{{\n\n" + padding + "\"id\" : \"{0}\",\n" + padding + "\"Наименование\" : \"{1}\",\n" + padding + "\"Дата производства\" : \"{2}\",\n" + padding + "\"Цена товара\" : \"{3}\"\n" + padding + "\"Вес товара\" : \"{4}г.\".\n\n" + padding + "}};\n", id, name, manufactured->ToString("d", ci), price.ToString("C", ci), weight);

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

  Warehouse(Product^ src, String^ name) : name{ name }
  {
	if (src == nullptr) {
	  throw gcnew ArgumentNullException("[ ! ] Товар несуществует.");
	}
	theSource = src;
	products = gcnew List< Product^ >();

	// Связываем добавляем обработчики в списки вызовов делегатов.
	src->OnCreateProduct += gcnew CreateProductHandler(this, &Warehouse::createProduct);
	src->OnEditProduct += gcnew EditProductHandler(this, &Warehouse::editProduct);
	src->OnDeleteProduct += gcnew DeleteProductHandler(this, &Warehouse::deleteProduct);

  }

  String^ getName() { return name; }

  void print(int width) {
	String ^pad = "", ^padding = pad->PadLeft(width);
	Console::WriteLine(padding + "\"Название склада\" : \"{0}\" {{\n" + padding + "\"Число товаров\" : \"{1}\"", name, products->Count);
	for each (Product^ p in products) {
	  p->print(width + 2);
	}
	Console::WriteLine("\n" + padding + "};");
  }

  // Объявляем обработчиков событий
  // TODO реализовать логику
  void createProduct() {
	theSource->input();
	products->Add(theSource);
	Console::WriteLine("[ Обработчик события CreateProduct ] [ V ] Товар p с идентификатором {0} успешно добавлен.", theSource->getId());
  }
  void editProduct(Product^ p) {

	if (p == nullptr) {
	  throw gcnew ArgumentNullException("[ ! ] Товар не существует.");
	}

	Int32 c; String^ s;
	Int32 day, month, year;
	Double tmpPrice, tmpWeight;

	Console::WriteLine("[ << ] Какое из свойств вы хотите изменить : {\n  1 -> Изменить название товара\n  2 -> Изменить дату производства\n  3 -> Изменить цену товара\n  4 -> Изменить вес товара\n  5 -> Изменить все свойства товара\n}");
	Console::Write("[ >> ]"); c = Convert::ToInt32(Console::ReadLine());

	switch (c) {
	case 1 :
	  Console::WriteLine("[ << ] Введите Наименование товара ( Текущее Наименование = {0} )", p->getName());
	  Console::Write("[ >> ] Новое Наменование = "); s = Console::ReadLine(); p->setName(s);
	  break;
	case 2:
	  Console::WriteLine("[ << ] Введите Новую Дату производства товара ( Текущая Дата производства  = {0} )", p->getManufactured());
	  try {
		Console::Write("[ >> ] Год = ");
		year = Convert::ToInt32(Console::ReadLine());

		Console::Write("[ >> ] Месяц = ");
		month = Convert::ToInt32(Console::ReadLine());

		Console::Write("[ >> ] День = ");
		day = Convert::ToInt32(Console::ReadLine());

		p->setManufactured(gcnew DateTime(year, month, day));
	  }
	  catch (System::ArgumentOutOfRangeException^ e) {
		Console::WriteLine("[ ! ] Вы ввели некорректную дату, отбой операции.");
	  }
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
	default:
	  Console::WriteLine("[ ? ] Такого свойства нет, отмена операции ...");
	}

  }
  void deleteProduct(Product^ p) {
	if (products->Remove(p))
	  Console::WriteLine("[ Обработчик события DeleteProduct ] [ V ] Операция успешно выполнена.");
	else Console::WriteLine("[ Обработчик события DeleteProduct ] [ ! ] Операция провалена.");
	// Если на объект не ссылается ни один из указателей, то сборщик мусора автоматически освободит выделенную под него память.

  }

private:

  String^ name;

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
	Console::WriteLine("[ << ] Введите название склада в который хотите добавить товар, если указаный склад будет отсутствовать в перечне, мы создадим новый.");
	String^ warehouseName;
	Console::Write("[ >> ] "); warehouseName = Console::ReadLine();
	searchCriteria = warehouseName;
	// Указатель на 0 - значение экземпляра по умолчанию.
	tmpWarehouse = warehouses->Find(match);
	if (tmpWarehouse == nullptr) {
	  Console::WriteLine("[ << ] Создадим новый склад с именем {0}.", warehouseName);
	  
	  tmpWarehouse = gcnew Warehouse(tmpProduct, warehouseName);
	  
	  warehouses->Add(tmpWarehouse);
	  warehouses[warehouses->IndexOf(tmpWarehouse)]->createProduct();
	}
  }

private:

  bool findWareHouseByName(Warehouse^ wh) {
	return wh->getName() == searchCriteria ? true : false;
  }

  void init() {
	match = gcnew Predicate<Warehouse^>(this, &ManufacturerInventory::findWareHouseByName);
	searchCriteria = "";
	tmpProduct = gcnew Product();
	tmpWarehouse = nullptr;
	warehouses = gcnew List< Warehouse^ >();
  }

  String^ name;

  Product^ tmpProduct;

  Warehouse^ tmpWarehouse;
  String^ searchCriteria;
  Predicate<Warehouse^>^ match;

  List< Warehouse^ >^ warehouses;

};
/* Сохраняет сообщения о сработавших событиях в файл, с использованием System::IO::StreamWriter, ведет лог. */
ref class EventLogger {

public: 
  // TODO Расписать логику
  static void LogEvent(String^ message) {
	DateTime curDate = DateTime::Now;
	String^ fileName = Convert::ToString(curDate.Day) + "_" + Convert::ToString(curDate.Month) + "_" + Convert::ToString(curDate.Year) + "_event_log.txt";

  }


};
