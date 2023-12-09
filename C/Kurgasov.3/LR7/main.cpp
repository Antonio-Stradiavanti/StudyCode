#include "classes.h"

void menu() {

  String^ mainMenu = gcnew String(
	"*** Главное Меню\n\n1. Завершить работу программы\n2. Вывести перечень товаров\n3. Вывести справку\n\nГлавное Меню ***"
  );
  String^ inventoryMenu = gcnew String(
	"### Меню производителя\n\n1. Вывести список складов и идентификаторов товаров на каждом из них\n2. Добавить новый товар на склад\n3. Удалить товар со склада\n4. Редактировать информацию о товаре\n\nПеречень товаров ###"
  );

  Int32 c;
  ManufacturerInventory^ mi;

  while (true) {
	Console::WriteLine(mainMenu);
	Console::Write(">> Введите команду >> "); c = Convert::ToInt32(Console::ReadLine());

	switch (c)
	{
	case 1:
	  Console::WriteLine("** Завершаю работу **");
	  return;
	case 2:

	  break;
	default:
	}

  }
}

int main() {


  //Product^ g = gcnew Product(gcnew String("23232"), gcnew String("chair"), gcnew DateTime(2023, 12, 9), 10000, 12.23);
  //g->input();
  //g->print();
  Random^ rnd = gcnew Random();

  Console::WriteLine(rnd->Next(1000000000, Int32::MaxValue-1));

  Console::Read();

  return 0;
}