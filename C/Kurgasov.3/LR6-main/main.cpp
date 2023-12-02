#include<iostream>
#include<vector>
#include<string>
#include"pugixml.hpp"
using namespace std;
//using namespace pugi;
/* 

  Задание : Отработать механизм с потоками ввода и вывода на примере xml файла, а не изучать географию, нужна только приблизительная модель справочника условных знаков, только родительский и дочерние узлы, в роли справочника будет выступать xml файл.

  Реализовать ведение справочников для предметной области "условные знаки"
  Необходимо : 3 уровня в иерархии классов с множественным наследованием, операции : добавление, редактирование, удаление записей.

  - [ ] Нужно разобраться с структурой XML справочника, понять : какие мне нужны свойства для каждого из классов чтобы его идентифицировать.

*/
/* Перечисляемый тип, описывает множество условных знаков */

enum VegCoverType {
  forest
};
enum HumanSettlementType {
  city, village
};

/* MapSymbol : корень иерархии классов */ 
class MapSymbol {
public: 

  enum Type {
    relief, vegCover, water, humanSettlement, road, localObject
  };

  // Конструкторы
  MapSymbol() : latAndLong{0, 0}, coords{ 0, 0 }, type {} {}

  MapSymbol(Type type) : latAndLong{ 0, 0 }, coords{ 0, 0 }, type{ type } {}
  // Задает описание 
  virtual void setDescription() = 0;
  //virtual void input() = 0;

  string getDecsription() {
    return symbolDescr;
  }

  void setLatAndLong(int lat, int lon) {
    latAndLong[0] = lat, latAndLong[1] = lon;
  }
  void setCoords(int x, int y) {
    coords[0] = x; coords[1] = y;
  }

  void print() {
    cout << "Координаты : x=" << (/*111 * latAndLong[0] +*/ coords[0]) << ", y=" << (/*111 * latAndLong[1] + */ coords[1] ) << "\n\nОписание : " << symbolDescr << endl;
  }

private:
  int latAndLong[2];
  int coords[2];
  Type type;

protected:  
  string symbolDescr;

  pugi::xml_document doc;
  pugi::xml_node node;

};
/* Производные классы от MapSymbol */
// Описывает возвышенность, низменность, наледь.
class Relief : virtual public MapSymbol {
public:

  enum ReliefType {
    desert, mountain, volcano, lowLand
  };

  // Объект рельефа мы не создаем.
  Relief() : spec{}, height{}, altitude{} {}
  Relief(ReliefType spec, double altitude=0, double height=0) : MapSymbol(Type::relief), height{height}, altitude{altitude}, spec{spec} {}

  void setHeight(double height) { this->height = height; };
  void setAltitude(double altitude) { this->altitude = altitude; }

  double getAltitude() { return altitude; }
  double getHeight() { return height; }

private:
  ReliefType spec;
  
  double height;
  double altitude;

};
// Описывает водоем
class Water : virtual public MapSymbol {
public:

  enum WaterType {
    swamp, river
  };

  Water() : spec{}, depth{} {}
  Water(WaterType spec, double depth) : MapSymbol(Type::water), spec{spec}, depth{depth} {}
  // Объект водоема мы не создаем.
  void setDepth(double depth) { this->depth = depth; };
  double getDepth() { return depth; }

private:
  WaterType spec;
  double depth;
};
// Болото, множественное наследование
class Swamp : public Water, public Relief {
public:

  enum SwampState {
    drained, traversable, unTraversable, barelyPassable
  };

  Swamp() : Water(), Relief(), state{} {}
  Swamp(int lat, int lon, int x, int y, SwampState state, double depth) : Water(WaterType::swamp, depth), Relief(ReliefType::lowLand), state{state} {
    setLatAndLong(lat, lon);
    setCoords(x, y);

  }
    // Для вызова методов нужно использовать оператор глобального разрешения.
    // Нужно вызвать параметризованные конструкторы рельефа и водоема
  void setDescription() {
    string s = " болото, глубиной d=" + to_string(getDepth()) + "м : ";
    switch (state) {
    case drained :
      symbolDescr = "Осущенное" + s + "Несколько голубых горизонтальных волнистых линий, расположенных на небольшом расстоянии друг от друга и направленных сверху вниз, перечеркнутых прямой линией, что указывает на то что болото осушено";
      break;
    case traversable:
      symbolDescr = "Проходимое" + s + "Несколько голубых дискретных горизонтальных волнистых линий, расположенных на небольшом расстоянии друг от друга и направленных сверху вниз, пространство между ними заполняют серым цветом, что указывает на то что болото проходимо";
      break;
    default: 
      symbolDescr = "Непроходимое и труднопроходимое" + s + "Несколько голубых горизонтальных волнистых линий, расположенных на небольшом расстоянии друг от друга и направленных сверху вниз, символизирующих рябь на поверхности болота из-за стоячей воды, между линиями указывают растительный покров болота : трава, мох, тростник и т.п.";
      break;
    }
  }
  void drainSwamp() {
    if (state != drained) 
      state = drained;
  }

private:
  SwampState state;

};

/* XML : Справочник */
class XML {
  /*
  
  Существуют всего 3 класса, представляющих дерево DOM : xml_document, xml_node, xml_attribute.

  создание, удаление, редактирование объектов, загрузку/выгрузку в файл.
  
  */
public: 
  pugi::xml_document doc;


private:
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