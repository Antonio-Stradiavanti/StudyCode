#pragma once
#include "hierarchy.h"
#include "pugixml.hpp"
/* XML : Справочник */
bool isType2Exist(pugi::xml_attribute atr) {
  return strcmp(atr.name(), "type2") == 0;
}
class XML {
  /*

  Существуют всего 3 класса, представляющих дерево DOM : xml_document, xml_node, xml_attribute.
  создание, удаление, редактирование объектов, загрузку/выгрузку в файл.

  */
public:
  // Получаем из метода класса, производного от MapSymbol
  XML() : document{} {
    // Инициализируем корень
    init();

  }

  void writeLatAndLong(const array<int, 2>& latAndLong) {
    landMap.child("latAndLong").child("lat").first_child().text().set(latAndLong[0]);
    landMap.child("latAndLong").child("lon").first_child().text().set(latAndLong[1]);

  }

  void reset() {
    document.reset();
    init();

  }

  // TEST ?
  // node на самом деле это doc
  void add(pugi::xml_node doc) {
    pugi::xml_node newNode = mapSymbols.append_child("MapSymbol");

    for (auto child : doc.children()) {
      newNode.append_child(child.name()).append_child(pugi::node_pcdata).text().set(child.child_value());
    }

    for (auto atr : doc.attributes()) {
      newNode.append_attribute(atr.name()).set_value(atr.value());
    }

  }

  // Принимает вектор указателей на корень иерархии классов
  /* 1я Сторона сериализации : создаем справочник из файла */
  // TEST ?
  void load(vector < MapSymbol* >& list) {

    // Нужно переместить файл из дерева в справочник

    //writeLatAndLong(store[0]->getLatAndLong());
    string fileName;
    cout << "<< Введите имя файла, содержащего справочник\n>> ";
    cin >> fileName;

    // Содержимое файла у меня теперь в оперативной памяти, в структуре дерево.
    pugi::xml_parse_result res = document.load_file(fileName.c_str());
    // проверим что файл открыт корректно.
    if (!res) {
      cout << "<! Указанный документ не является допустимым XML документом !>\n\n" << res.description() << endl;
      return;
    }

    MapSymbol* tmp;
   
    // Лутаем указатели
    landMap = document.child("LandMap");
    mapSymbols = landMap.child("MapSymbols");

    for (auto node : mapSymbols.children()) {

      int x = node.child("x").first_child().text().as_int();
      int y = node.child("y").first_child().text().as_int();

      // Найдем атрибут type 2
      if (node.find_attribute(isType2Exist)) {
        // То тогда получим болото
        list.push_back(tmp);
        list[list.size() - 1] = new Swamp( 
          x, y, 
          node.attribute("depth").as_double(), 
          node.attribute("heigh").as_double(), 
          static_cast<MapSymbol::State_swamp>(node.attribute("state").as_int()), 
          static_cast<MapSymbol::Struct_swamp>(node.attribute("struct").as_int()) 
        );

        list[list.size() - 1]->setName( 
          node.child("name").child_value()
        );
        list[list.size() - 1]->setDescr(
          node.child("description").child_value()
        );

      } else {
        switch (static_cast<MapSymbol::Type>(node.attribute("type1").as_int())) {
        case MapSymbol::Type::relief:
          list.push_back(tmp);
          list[list.size() - 1] = new Relief(
            x, y,
            node.attribute("heigh").as_double(),
            static_cast<MapSymbol::Spec_relief>(node.attribute("spec1").as_int())
          );

          list[list.size() - 1]->setName(
            node.child("name").child_value()
          );
          list[list.size() - 1]->setDescr(
            node.child("description").child_value()
          );
          break;
        case MapSymbol::Type::water:
          list.push_back(tmp);
          list[list.size() - 1] = new Water(
            x, y,
            node.attribute("depth").as_double(),
            node.attribute("width").as_double(),
            node.attribute("hasBeach").as_bool(),
            static_cast<MapSymbol::Spec_water>(node.attribute("spec1").as_int()),
            static_cast<MapSymbol::Struct_bottom>(node.attribute("struct").as_int())
          );

          list[list.size() - 1]->setName(
            node.child("name").child_value()
          );
          list[list.size() - 1]->setDescr(
            node.child("description").child_value()
          );

          break;
        case MapSymbol::Type::road:
          list.push_back(tmp);
          list[list.size() - 1] = new Road(
            x, y,
            node.attribute("numStripes").as_int(),
            node.attribute("stripWidth").as_int(), 
            node.attribute("roadWidth").as_int(),
            static_cast<MapSymbol::Spec_road>(node.attribute("spec1").as_int()),
            static_cast<MapSymbol::State_road>(node.attribute("state").as_int()),
            static_cast<MapSymbol::Struct_road>(node.attribute("struct").as_int())
          );

          list[list.size() - 1]->setName(
            node.child("name").child_value()
          );
          list[list.size() - 1]->setDescr(
            node.child("description").child_value()
          );

          break;
        default:
          cout << "<! Условный знак не распознан. !>" << endl;
          break;
        }
      }

    }

    list[0]->setLatAndLong(
      landMap.child("latAndLong").child("lat").first_child().text().as_int(),
      landMap.child("latAndLong").child("lon").first_child().text().as_int()
    );

    writeLatAndLong(list[0]->getLatAndLong());

  }
  
  // V
  void save() {

    /* Загрузить в документ из файла */
    string fileName;

    cout << "<< Введите имя файла, в который выполним сериализацию :\n>> ";
    cin >> fileName;

    document.save_file(fileName.c_str());
  }
  
  // TEST ? Можно сказать это предпросмотр загружаемого файла.
  void print() {
    cout << "\n# Предпросмотр полученного документа\n" << endl;
    int i = 0;
    for (auto node : landMap.child("MapSymbols").children()) {
      
      cout << "Широта & долгота = {" << endl;
      cout << "  lat = " << landMap.child("latAndLong").child("lat").child_value() << "\";\n  lon = \"" << landMap.child("latAndLong").child("lon").child_value() << "\";\n}" << endl;

      cout << "\n## " << ++i << "-я Запись\n" << endl;

      for (auto child : node.children()) {
        cout << "Служебные атрибуты = {" << endl;
        for (auto atr : child.attributes()) {
          cout << "  " << atr.name() << " = \"" << atr.value() << "\";" << endl;
        }
        cout << "}\n\nКоординаты = {\n" << "  x = " << child.child("x").child_value() << ";\n  y = " << child.child("y").child_value() << ";\n}" << endl;
        
        cout << "\nНазвание = \"" << child.child("name").child_value() << "\";" << endl;
        cout << "\nОписание = \"" << child.child("description").child_value() << "\";" << endl;
      }
      cout << "\n##\n" << endl;
    }
    cout << "\n#" << endl;
  }

private:

  pugi::xml_document document;

  // Корень дерева
  pugi::xml_node landMap, mapSymbols;

  void init() {
    //string mapNameAtr;
    //cout << "<< Введите название топографической карты :\n>> ";
    //cin >> mapNameAtr;

    landMap = document.append_child("LandMap");
    landMap.append_child("latAndLong");

    pugi::xml_node lat = landMap.child("latAndLong").append_child("lat");
    lat.append_child(pugi::node_pcdata).text().set(0);

    pugi::xml_node lon = landMap.child("latAndLong").append_child("lon");
    lon.append_child(pugi::node_pcdata).text().set(0);

    mapSymbols = landMap.append_child("MapSymbols");
  }

};