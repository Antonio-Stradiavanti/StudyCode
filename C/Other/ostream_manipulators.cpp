#include <iostream>
#include <string>
#include <vector>
#include "pugixml.hpp"
using namespace std;
using namespace pugi;
//Базовый класс мебель
class furniture {
public:
	xml_document doc;
	xml_node child;//Используется для храннения узла, которыйпосле будет добавлен в xml документ
	string name;
	string type;
	string width;
	string height;
	string price;
	//Используем виртуальный метод чтобы дочерние классы по своему реализовывали данную функцию
	virtual void input() {
		cout << "Enter the name" << endl;
		cin >> name;
		cout << "Enter the width" << endl;
		cin >> width;
		cout << "Enter the height" << endl;
		cin >> height;
		cout << "Enter the price" << endl;
		cin >> price;
		/*
		c_str() используется для преобразования строки, в формат
		const char*, необходимый для методов библиотеки pugixml, ожидающих аргументы типа const char* 
		*/
		//Присаиваем новое имя узлу
		child.set_name(name.c_str());
		//Присваиваем значения аттрибутам
		child.attribute("width").set_value(width.c_str());
		child.attribute("height").set_value(height.c_str());
		child.attribute("price").set_value(price.c_str());
	}
	furniture() {
		name = "name";
		type = "other";
		width = "0";
		height = "0";
		price = "0";
		child = doc.append_child(name.c_str());
		child.append_attribute("width").set_value(0);
		child.append_attribute("height").set_value(0);
		child.append_attribute("price").set_value(0);
	}
	furniture(string tname,string twidth, string theight, string tprice) {
		name = tname;
		type = "other";
		width = twidth;
		height = theight;
		price = tprice;
		child=doc.append_child(tname.c_str());
		child.append_attribute("width").set_value(twidth.c_str());
		child.append_attribute("height").set_value(theight.c_str());
		child.append_attribute("price").set_value(tprice.c_str());
	}
	virtual void print() {
		cout << "Название:" << name << endl;
		cout << "Ширина:" << width << endl;
		cout << "Высота:" << height << endl;
		cout << "Цена:" << price << endl;
	}
};
/*
* Делаем базовый класс виртуальным, чтобы при множественном наследование от одного базового класса 
* не возникало двусмыслености и была лишь одна копия базового класса
*/
class tabouret: virtual public furniture{
public:
	string length;
	void input() {
		furniture::input();//Вызываем одноименный метод класса furniture
		cout << "Enter the length" << endl;
		cin >> length;
		child.attribute("length").set_value(length.c_str());
	}
	tabouret():furniture(){
		type = "tabouret";
		length = "0";
		child.append_attribute("length").set_value(0);
	}
	tabouret(string tlength) {
		length = tlength;
	}
	//Вызывем сначала конструктор базового класса с параметрами, после используем конструктор текщего класса
	//В текущем конструкторе присваиваем свойства характерные данному классу, остальные свойства присвоили конструкторы предыдущих классов.
	tabouret(string tname,string twidth, string theight, string tprice, string tlength):
		furniture(tname,twidth,theight,tprice) {
		type = "tabouret";
		length = tlength;
		child.append_attribute("length").set_value(length.c_str());
	}
	void print() {
		furniture::print();
		cout << "Длина:" << length << endl;
	}
};
class chair: virtual public tabouret {
public:
	string backheight;
	string backwidth;
	void input() {
		tabouret::input();
		cout << "Enter the backheight" << endl;
		cin >> backheight;
		cout << "Enter the backwidth" << endl;
		cin >> backwidth;
		child.attribute("backheight").set_value(backheight.c_str());
		child.attribute("backwidth").set_value(backwidth.c_str());
	}
	chair() :furniture(), tabouret() {
		type = "chair";
		backheight = "0";
		backwidth = "0";
		child.append_attribute("backheight").set_value(0);
		child.append_attribute("backwidth").set_value(0);
	}
	chair(string tbackheight, string tbackwidth) {
		backheight = tbackheight;
		backwidth = tbackwidth;
		child.append_attribute("backheight").set_value(backheight.c_str());
		child.append_attribute("backwidth").set_value(backwidth.c_str());
	}
	chair(string tname,string twidth, string theight, string tprice, string tlength,
		string tbackheight, string tbackwidth): tabouret(tlength),
		furniture(tname,twidth,theight,tprice){
		type = "chair";
		backheight = tbackheight;
		backwidth = tbackwidth;
		child.append_attribute("backheight").set_value(backheight.c_str());
		child.append_attribute("backwidth").set_value(backwidth.c_str());
	}
	void print() {
		tabouret::print();
		cout << "Высота спинки: " << backheight << endl;
		cout << "Ширина спинки: " << backwidth << endl;
	}
};
class barstool: virtual public tabouret{
public:
	string armresheight;
	void input() {
		tabouret::input();
		cout << "Enter the armresheight" << endl;
		cin >> armresheight;
		child.attribute("armresheight").set_value(armresheight.c_str());
	}
	barstool() :furniture(), tabouret() {
		type = "barstool";
		armresheight = "0";
		child.append_attribute("armresheight").set_value(0);
	}
	barstool(string tarmresheight) {
		armresheight = tarmresheight;
		child.append_attribute("armresheight").set_value(armresheight.c_str());
	}
	barstool(string tname, string twidth, string theight, string tprice, string tlength,
		string tarmresheight) : tabouret(tlength),
		furniture(tname, twidth, theight, tprice) {
		type = "barstool";
		armresheight = tarmresheight;
		child.append_attribute("armresheight").set_value(armresheight.c_str());
	}
	void print() {
		tabouret::print();
		cout << "Высота подлокотников: " << armresheight << endl;
	}
};
//Используем множественное наследование
class armchair:public chair, public barstool {
public:
	void input() {
		tabouret::input();
		cout << "Enter the backheight" << endl;
		cin >> backheight;
		cout << "Enter the backwidth" << endl;
		cin >> backwidth;
		cout << "Enter the armresheight" << endl;
		cin >> armresheight;
		child.attribute("backheight").set_value(backheight.c_str());
		child.attribute("backwidth").set_value(backwidth.c_str());
		child.attribute("armresheight").set_value(armresheight.c_str());
	}
	armchair() :furniture(), tabouret(),chair(),barstool() {
		type = "armchair";
	}
	armchair(string tname,string twidth, string theight, string tprice, string tlength,
		string tbackheight, string tbackwidth, string tarmresheight) :
		barstool(tarmresheight),chair(tbackheight, tbackwidth),
		tabouret(tlength),furniture(tname,twidth, theight, tprice)
	{
		type = "armchair";
	}
	void print() {
		tabouret::print();
		cout << "Высота спинки: " << backheight << endl;
		cout << "Ширина спинки: " << backwidth << endl;
		cout << "Высота подлокотников: " << armresheight << endl;
	}
};
class XML {
	//XML
public:
	xml_document document;
	XML() {
		//Инициализируем 4 дочерних узла характеризующие типы мебели и корень 
		xml_node furnitures = document.append_child("furnitures");
		furnitures.append_child("tabouret");
		furnitures.append_child("chair");
		furnitures.append_child("barstool");
		furnitures.append_child("armchair");
	}
	void reset() {
		//Перед загрузкой очищаем таблицу
		document.reset();
		xml_node furnitures = document.append_child("furnitures");
		furnitures.append_child("tabouret");
		furnitures.append_child("chair");
		furnitures.append_child("barstool");
		furnitures.append_child("armchair");
	}
	void save_xml() {
		string name;
		cout << "Enter the name of filename for save" << endl;
		cin >> name;
		document.save_file(name.c_str());
	}
	void load_xml(vector<furniture*> &list) {
		string name;
		furniture* temp;
		cout << "Enter the name of filename for load" << endl;
		cin >> name;
		document.load_file(name.c_str());
		//Проходимся по всем дочерним узлам узла furnitures
		for (xml_node node : document.child("furnitures").children())
		{
			//Проходимся по всем дочерним узлам каждого дочернего узла
			for (xml_node child : node.children())
			{
				//Смотрим название родительсого узла и по нему определяем тип мебели
				//Используем приведение типов, т.к node.name() формат const char*
				if ((string)node.name() == "armchair") {
					//Добавляем в конец новую единицу мебели из xml
					list.push_back(temp);
					//Используя конструктор заполняем свойства для данного объкта мебели
					list[list.size() - 1] = new armchair(child.name(), child.attribute("width").value(),
						child.attribute("height").value(), child.attribute("price").value(), child.attribute("length").value(),
						child.attribute("backheight").value(), child.attribute("backwidth").value(), child.attribute("armsheight").value());
				}
				else if ((string)node.name() == "barstool") {
					list.push_back(temp);
					list[list.size() - 1] = new barstool(child.name(), child.attribute("width").value(),
						child.attribute("height").value(), child.attribute("price").value(), child.attribute("length").value(),
						child.attribute("armsheight").value());
				}
				else if ((string)node.name() == "chair") {
					list.push_back(temp);
					list[list.size() - 1] = new chair(child.name(), child.attribute("width").value(),
						child.attribute("height").value(), child.attribute("price").value(), child.attribute("length").value(),
						child.attribute("backheight").value(), child.attribute("backwidth").value());
				}
				else if ((string)node.name() == "tabouret") {
					list.push_back(temp);
					list[list.size() - 1] = new tabouret(child.name(), child.attribute("width").value(),
						child.attribute("height").value(), child.attribute("price").value(), child.attribute("length").value());
				}
			}

		}
	}
	//По заданному названию узла добавляем узел
	void add_child(string type, xml_node child) {
		xml_node furnitures = document.child("furnitures");
		xml_node choosentype = furnitures.child(type.c_str());
		//Создаем новый дрчерний узел для данного типа мебели
		xml_node newchild = choosentype.append_child(child.name());
		//Проходися по всем атрибутам узла и записываем их название и значение в узел xml
		for (xml_attribute attr : child.attributes())
		{
			newchild.append_attribute(attr.name()).set_value(attr.value());
		}
	}
	//Выводим xml проходясь по узлам и их атриббутам
	void print() {
		for (xml_node node : document.child("furnitures").children())
		{
			cout << node.name() << endl;

			for (xml_node child : node.children())
			{
				cout << child.name() << endl;
				for (xml_attribute attr : child.attributes())
				{
					cout << attr.name() << " - " << attr.value();
					cout << endl;

				}
			}

		}
	}
protected:
	/*
	* Редактирование данных в xml
	void edit_attribute(xml_node child, string furniturestype) {
		string temp;
		for (xml_attribute attribute : child.attributes()) {
			cout << "Enter the new attibute's value " << attribute.name() << endl;
			cin >> temp;
			attribute.set_value(temp.c_str());
		}
	}
	*/
};
int main() {
	setlocale(LC_ALL,"Russian");
	XML xml;
	furniture* temp;
	vector<furniture*> list;
	int command;
	string type,searchname;
	cout << "Command list:\n0 - close programm\n1 - add furnitures\n2 - remove furnitures\n3 - edit furnitures\n4 - save to xml\n5 - load from xml\n6 - print xml\n7 - print furnitures\n";
	while (1) {
		cin >> command;
		switch (command)
		{
		case(0):
			cin >> type;
			return 0;
			break;
		case(1):
			cout << "Enter the type of furnitures" << endl;
			cout << "types: tabouret, barstool, chair, armchair"<<endl;
			cin >> type;
			if (type == "armchair") {
				list.push_back(temp);
				//Инициализация объекта
				list[list.size() - 1] = new armchair;
			}
			else if (type == "chair") {
				list.push_back(temp);
				list[list.size() - 1] = new chair;
			}
			else if (type == "barstool") {
				list.push_back(temp);
				list[list.size() - 1] = new barstool;
			}
			else if (type == "tabouret") {
				list.push_back(temp);
				list[list.size() - 1] = new tabouret;
			}
			else {
				cout << "The choosen type doesn't found" << endl;
				break;
			}
			//Вводим данные
			list[list.size() - 1]->input();
			//list[list.size() - 1]->print();
			break;
		case(2):
			cout << "Enter the name of oblect for delliting" << endl;
			cin >> searchname;
			//Последовательно проходися по вектору, если имя элемента совпало, то удаляем элемент по индексу
			for (int i = 0; i < list.size(); i++) {
				if (list[i]->name == searchname) {
					// К указателю на начальный элемент прибавляем количество элементов, до нужного для удаления
					list.erase(list.begin()+i);
					break;
				}
			}
			break;
		case(3):
			cout << "Enter the name of oblect for editting" << endl;
			cin >> searchname;
			for (int i = 0; i < list.size(); i++) {
				if (list[i]->name == searchname) {
					list[i]->input();
					break;
				}
			}
			break;
		case(4):
			xml.reset();
			for (int i = 0; i < list.size(); i++) {
				xml.add_child(list[i]->type, list[i]->child);
			}
			xml.save_xml();
			break;
		case(5):
			//Unpacking
			//Очищаем вектор перед тем как в него загрузить данные из xml
			list.clear();
			xml.load_xml(list);
			break;
		case(6):
			xml.print();
			break;
		case(7):
			for (int i = 0; i < list.size(); i++) {
				list[i]->print();
			}
			break;
		default:
			break;
		}
	}
}
