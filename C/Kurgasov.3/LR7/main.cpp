#include "classes.h"

void menu() {

  String^ mainMenu = gcnew String(
	"*** Главное Меню\n\n1. Завершить работу программы\n2. Вывести перечень товаров\n3. Вывести справку\n\nГлавное Меню ***"
  );
  String^ inventoryMenu = gcnew String(
	"### Меню производителя\n\n1. Вывести список товаров\n2. Добавить новый товар в перечень\n3. Удалить товар из перечня\n4. Редактировать информацию о товаре\n\nПеречень товаров ###"
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
	  break;
	}

  }
}

ref class Tst {

  String^ searchCriteria;

public :  
  List<String^>^ list;

  Tst () {
	list = gcnew List<String^>();
  }

  void add(String^ str) {
	list->Add(str);

  }

  void find(String^ searchCriteria) {
	this->searchCriteria = searchCriteria;
	Predicate<String^>^ match = gcnew Predicate<String^>(this, &Tst::pred);
	Console::WriteLine(list->Find(match));
  }

  void print() {
	for each (String^ str in list) {
	  Console::WriteLine(str);
	}
  }

  bool pred(String^ str) {
	if (str == searchCriteria) {
	  return true;
	} else {
	  return false;
	}
  }



};

ref class forPred {
public:
  static Int32 productSearchCriteria = 0;
  static bool findProdcutById(Product^ pr){
	return pr->getId() == productSearchCriteria ? true : false;
  }
};
int main() {
  
  ManufacturerInventory^ inv = gcnew ManufacturerInventory("Перечень 1");
  inv->add();
  inv->add();
  //inv->add();

  inv->print();

  inv->remove();
  inv->print();

  //inv->edit();
  //inv->print();

  //Console::Read();
  //inv->print();
  //Product^ pr;
  //Product^ product = gcnew Product();
  //Warehouse^ wh = gcnew Warehouse(product, "Склад");
  //Predicate<Product^>^ matchProduct = gcnew Predicate<Product^>(&forPred::findProdcutById);
  //wh->createProduct();
  //wh->print(2);
  //// Теперь выполним поиск.
  //Console::Write("[ Id ] ");
  //forPred::productSearchCriteria = Convert::ToInt32(Console::ReadLine());
  //pr = wh->getProducts()->Find(matchProduct);
  //product->fireDeleteProduct(pr);

  //wh->print(2);


  //Int32 c;
  //Console::Write("[ >> ]"); c = Convert::ToInt32(Console::ReadLine());



  Console::Read();

  return 0;
}