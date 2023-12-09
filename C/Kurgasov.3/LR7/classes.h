#pragma once
#include <string>
#include <vector>

using namespace System;
using Collections::Generic::List;


ref class Product {
public:

  Product() : name{}, manufactured{}, price{}, weight{} {}

  Product(String^ name, DateTime^ manufactured, double price, double weight) : name{ name }, manufactured{ manufactured }, price{ price }, weight{ weight }
  {
	Random^ rnd = gcnew Random();
	id = rnd->Next(1000000000, Int32::MaxValue - 1);
  }

  void input() {

	Random^ rnd = gcnew Random();
	id = rnd->Next(1000000000, Int32::MaxValue - 1);

	Console::WriteLine("[Info] 1. Введите Название товара :");
	Console::Write(">> ");  name = Console::ReadLine();

	Int32 year, month, day;
	label:
	Console::WriteLine("[Info] 2. Введите дату производства товара :");
	try {
	  Console::Write(">> Введите год >> ");
	  year = Convert::ToInt32(Console::ReadLine());

	  Console::Write(">> Введите месяц >> ");
	  month = Convert::ToInt32(Console::ReadLine());

	  Console::Write(">> Введите день >> ");
	  day = Convert::ToInt32(Console::ReadLine());

	  manufactured = gcnew DateTime(year, month, day);
	} catch (System::ArgumentOutOfRangeException^ e) {
	  Console::WriteLine("[Error] Вы ввели некорректную дату, попробуйте еще раз.");
	  goto label;
	}

	Console::WriteLine("[Info] 3. Укажите цену товара в рублях");
	Console::Write(">> ");  price = Convert::ToDouble(Console::ReadLine());

	Console::WriteLine("[Info] 4. Укажите вес товара в граммах");
	Console::Write(">> "); weight = Convert::ToDouble(Console::ReadLine());

  }

  void print() {
	Globalization::CultureInfo^ ci = gcnew Globalization::CultureInfo("ru-RU");
	Console::WriteLine("{{\n\n\"id\" : \"{0}\",\n\"Наименование\" : \"{1}\",\n\"Дата производства\" : \"{2}\",\n\"Цена товара\" : \"{3}\"\n\"Вес товара\" : \"{4}г.\".\n\n}};\n", id, name, manufactured->ToString("d", ci), price.ToString("C", ci), weight);

  }


private:

  Int32^ id;
  String^ name;
  DateTime^ manufactured;

  Double price;
  Double weight;

};

// События : создание товара, редактирование товара, удаление товара
delegate Product^ CreateProduct();
delegate void EditProduct(String^);
delegate void DeleteProduct(String^);
/* Аггрегирует товары, является источником событий */
ref class Warehouse
{
public:
  event CreateProduct^ onCreate;
  event EditProduct^ onEdit;
  event DeleteProduct^ onDelete;

private:
  String^ name;
  List< Product^ > products;

};
/* Получатель событий */
ref class ManufacturerInventory {

public:

  // TODO определить конструкторы

  // Получить информацию о количестве товаров определенных типов на складах
  //List< Int32 >^ getIdList() {

  //}

private:
  String^ name;
  List< Warehouse^ > warehouses;


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
