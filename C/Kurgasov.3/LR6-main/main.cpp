#include "pugixml.hpp"
#include "Hierarchy.h"
//using namespace pugi;
/* 

  Задание : Отработать механизм с потоками ввода и вывода на примере xml файла, а не изучать географию, нужна только приблизительная модель справочника условных знаков, только родительский и дочерние узлы, в роли справочника будет выступать xml файл.

  Реализовать ведение справочников для предметной области "условные знаки"
  Необходимо : 3 уровня в иерархии классов с множественным наследованием, операции : добавление, редактирование, удаление записей.

  - [ ] Нужно разобраться с структурой XML справочника, понять : какие мне нужны свойства для каждого из классов чтобы его идентифицировать.

  Операции сериализации выполняем с классом XML (он аггрегирует данные)

*/
enum VegCoverType {
  forest
};
enum HumanSettlementType {
  city, village
};

/* XML : Справочник */
class XML {
  /*
  
  Существуют всего 3 класса, представляющих дерево DOM : xml_document, xml_node, xml_attribute.
  создание, удаление, редактирование объектов, загрузку/выгрузку в файл.
  
  */
public: 
  // Получаем из метода класса, производного от MapSymbol
  XML() : doc{} {
    // Инициализируем корень
    init();

  }

  void writeLatAndLong(const array<int, 2>& latAndLong) {
    landMap.child("x").text().set(latAndLong[0]);
    landMap.child("y").text().set(latAndLong[1]);

  }

  void reset() {
    doc.reset();
    init();

  }

  void save(string fileName) {
    doc.save_file(fileName.c_str());
  }
  // Принимает вектор указателей на корень иерархии классов
  /* 1я Сторона сериализации : создаем справочник из файла */
  void load(string fileName, vector < MapSymbol* >& store) {
    //writeLatAndLong(store[0]->getLatAndLong());
    doc.load_file(fileName.c_str());
    MapSymbol* tmp;
    //pugi::xml_attribute atr;

    for (auto symbol : mapSymbols.children()) {
      // Перебираем каждый из дочерних узлов mapSymbols
      
      // Тут дальше по атрибутам уже будем определять экземпляром какого класса из иерархии классов является перебираемая запись.
      MapSymbol::Type1 type1 = static_cast<MapSymbol::Type1>(symbol.attribute("type1").as_int());


    }

  }

private:

  pugi::xml_document doc;

  pugi::xml_node landMap, mapSymbols;

  void init() {
    string mapNameAtr;
    cout << "<< Введите название топографической карты :\n>> ";
    cin >> mapNameAtr;

    landMap = doc.append_child("LandMap");
    landMap.append_attribute("name").set_value(mapNameAtr.c_str());

    pugi::xml_node x = landMap.append_child("x");
    x.append_child(pugi::node_pcdata);

    pugi::xml_node y = landMap.append_child("y");
    y.append_child(pugi::node_pcdata);

    mapSymbols = doc.append_child("MapSymbols");
  }

};

int main() {
  // PugiXML соответствует DOM
  // Контейнер сериализации
  pugi::xml_document doc, newDoc;
  // Выполняет парсинг XML документа

  pugi::xml_parse_result result = doc.load_file("x0.xml");

  //cout << "Значение latLong : " << doc.child("LandMap").child("latLong").child("x").child_value() << endl;
  pugi::xml_node node = doc.child("LandMap").child("MapSymbols");

  for (pugi::xml_node symbol : node) {
    cout << "\nАтрибуты {" << endl;
    for (pugi::xml_attribute atr : symbol.attributes()) {
      cout << "  " << atr.name() << " = " << atr.value() << endl;
    }
    cout << "}\n" << endl;

    cout << "Теги {" << endl;
    for (pugi::xml_node child : symbol) {
      cout << "  " << child.name() << " = " << child.child_value() << endl;
    }
    cout << "}\n\n---" << endl;

  }
  // Передаем в конструктор имя узла и создаем узел типа тег или явно указываем тип узла, чтобы создать например текстовый узел (pugi::node_pcdata).
  pugi::xml_node n = newDoc.append_child("Главный Тег");
  pugi::xml_node nc = n.append_child("Его потомок");
  nc.append_child(pugi::node_pcdata).set_value("Просто обычный текст !");

  cout << "Результат операции \" сохранить файл \" : " << newDoc.save_file("x1.xml") << endl;


  //string out = node.find_child_by_attribute("MapSymbol", "depth", "none").child("Description").child_value();

  //cout << "Описание условного знака, об. лес : " << out << endl;

  //string cont = doc.child("LandMap").child("MapSymbols").first_child().child("x").text().get();

  // Получаем список дочерних узлов и значение узла списка.
  // Надо использовать метод text() и конвертировать его в строку или в число
  
  // Элемент внутри тега является его дочерним узлом.
  //cout << doc.child("Project").child("Name").text().as_string() << endl;

  // - [ ] Разобраться, сходу не получается )
  // Закомментить : C-k C-c, раскомментить : C-k C-u;

  //Swamp sw(0, 0, 10, 20, static_cast<SwampState>(item.attribute("state").as_int()), item.attribute("depth").as_double());
  
  //Swamp sw(0, 0, 10, 20, SwampState::unTraversable, 100);

  return 0;
}