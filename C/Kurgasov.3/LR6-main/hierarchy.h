#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include "pugixml.hpp"
using namespace std;
/* TODO Пока не буду создавать сложную иерархию, отработаю сериализацию на локальном примере */
/*

  MapSymbol : корень иерархии классов

  Каждый класс содержит документ состоящий из тега с именем MapSymbol, который мы инициализируем именем, и атрибутами, лишних атрибутов не добавляем, впоследствии по заданым свойствам формируем описание.

*/
class MapSymbol {
public:

  enum class Type {
	none, relief, water, road
  };
  enum class Spec_relief {
	none, lowLand, clift
  };
  enum class Spec_water {
	none, swamp, river, canal
  };

  enum class Spec_road {
	none, highRoad, mainRoad, federalRoad, backRoad
  };

  enum class State_swamp {
	none, drained, traversable, unTraversable
  };

  enum class State_road {
	none, perfect, damaged, underСonstruction
  };

  enum class Struct_bottom {
	none, hard, miry, shelfy
  };

  enum class Struct_road {
	none, pebbles, asphalt, cementConcrete
  };

  enum class Struct_swamp {
	none, herb, moss, reed
  };

  // Конструктор создаем скелет документа
  MapSymbol() : coords{ 0, 0 }//, type1{}, type2{}
  {
	node = doc.append_child("MapSymbol");

	node.append_child("name");
	node.append_child("x");
	node.append_child("y");
	node.append_child("description");

  }


  // Методы 
  virtual void genName() = 0;
  virtual void genDescription() = 0;

  void setName(string name) { this->name = name; }
  void setDescr(string descr) { this->descr = descr; }

  virtual void input() {
	// Заполняем часть свойств
	cout << "<< Введите относительные координаты географического объекта :" << endl;
	// - [ ] Сделай обработку ошибок ввода данных
	cout << ">> x="; cin >> coords[0];
	cout << ">> y="; cin >> coords[1];

	writeCoords();

  }
  void print() {
	cout << "\n---\n\n  - Название топографического объекта : \"" << name << "\" ;\n\n  - Координаты : { " << (111 * latAndLong[0] + coords[0]) << ", " << (111 * latAndLong[1] + coords[1]) << " } ;\n\n  - Описание условного знака : \"" << descr << "\" .\n\n---" << endl;
  }

  string getDecsription() const { return descr; }
  string getName() const { return name; }
  pugi::xml_node getNode() const { return node; }
  array<int, 2> getLatAndLong() const { return latAndLong; }
  array<int, 2> getCoords() const { return coords; }

  void setLatAndLong(int lat, int lon) {
	latAndLong[0] = lat, latAndLong[1] = lon;
  }

  void setCoords(int x, int y) {
	coords[0] = x; coords[1] = y;
	writeCoords();

  }

private:
  // Это нужно для начального узла всего документа
  static array<int, 2> latAndLong;
  array<int, 2> coords;

  void writeCoords() {
	node.child("x").append_child(pugi::node_pcdata).text().set(coords[0]);
	node.child("y").append_child(pugi::node_pcdata).text().set(coords[1]);
  }

protected:

  array<string, 4> typeArr = { "не определен", "рельеф", "водоем", "дорога" };

  string name = "Рассматриваемый условный знак отображает на топографической карте ";
  string descr = "Топографический объект с такими характеристиками на карте схематически показывают ";

  // Для загрузки в XML документ
  pugi::xml_document doc;
  pugi::xml_node node;

};
array<int, 2> MapSymbol::latAndLong = { 0, 0 };
/* Производные классы от MapSymbol */
// Рельеф TODO.
class Relief : virtual public MapSymbol {
public:
  Relief() : MapSymbol(), /*type{ Type::relief },*/ spec{}, heigh{}
  {
	node.append_attribute("type1").set_value(static_cast<int>(Type::relief));
	node.append_attribute("spec1").set_value(0);

	node.append_attribute("heigh").set_value(0);
  }

  // Для наследования
  Relief(double heigh, Spec_relief spec = Spec_relief::lowLand) : MapSymbol(), /*type{ Type::relief },*/ spec{ spec }, heigh{ heigh }
  {
	xml_init(heigh, spec);

  }

  Relief(int x, int y, double heigh, Spec_relief spec) : MapSymbol(), spec{ spec }, heigh{ heigh }
  {

	xml_init(heigh, spec);

	setCoords(x, y);

	genName();
	genDescription();

  }

  void setheigh(double heigh) {
	this->heigh = heigh;
	node.attribute("heigh").set_value(heigh);
  };
  double getheigh() { return heigh; }

  void genName() {
	name += "рельеф типа : " + specReliefArr[static_cast<int>(spec)] + ", расположенный на высоте " + to_string(heigh) + "м. относительно уровня моря.";

	node.child("name").append_child(pugi::node_pcdata).text().set(name.c_str());


  }

  void genDescription() {
	switch (spec) {
	case Spec_relief::none:
	  descr += "с помощью горизонталей, оранжевого цвета, на которых наносят бергштрихи";
	  break;
	default:
	  descr += "с помощью треугольника с двумя вершинами, символизирующего скалу, после которого указывают высоту скалы в метрах";
	  break;
	}

	node.child("description").append_child(pugi::node_pcdata).text().set(descr.c_str());


  }

  void input() {
	MapSymbol::input();

	int i;
	cout << "<< Укажите тип рельефа : { 1 -> " << specReliefArr[1] << ", 2 -> " << specReliefArr[2] << " }\n>> ";
	cin >> i;
	if (i < 0 || i > 2) i = 0;

	node.attribute("spec1").set_value(i);
	spec = static_cast<Spec_relief>(i);

	cout << "<< Введите высоту рельефа в метрах :\n>> h=";
	cin >> heigh;

	node.attribute("heigh").set_value(heigh);

	genName();
	genDescription();

  }

private:

  void xml_init(double heigh, Spec_relief spec) {
	node.append_attribute("type1").set_value(static_cast<int>(Type::relief));
	node.append_attribute("spec1").set_value(static_cast<int>(spec));

	node.append_attribute("heigh").set_value(heigh);
  }

  //Type type;
  Spec_relief spec;

protected:
  double heigh;
  array<string, 3> specReliefArr = { "не определен", "низменность", "скала" };

};
// Водоем V
class Water : virtual public MapSymbol {
public:

  Water() : MapSymbol(), /*type{Type::water},*/ spec{}, str{}, width{}, depth{}, hasBeach{}
  {

	node.append_attribute("type1").set_value(static_cast<int>(Type::water));
	node.append_attribute("spec1").set_value(0);
	node.append_attribute("struct").set_value(0);

	node.append_attribute("depth").set_value(0.0);
	node.append_attribute("hasBeach").set_value(0);
	node.append_attribute("width").set_value(0.0);

  }

  // Для наследования
  Water(double depth, Spec_water spec = Spec_water::swamp) : MapSymbol(), /*type{ Type::water },*/ spec{ spec }, depth{ depth }, hasBeach{ false }, str{}, width{}
  {

	node.append_attribute("type2").set_value(static_cast<int>(Type::water));
	node.append_attribute("spec2").set_value(static_cast<int>(spec));

	node.append_attribute("depth").set_value(depth);


  }

  Water(int x, int y, double depth, double width, bool hasBeach, Spec_water spec, Struct_bottom str) : MapSymbol(), /*type{Type::water}, */ spec{ spec }, str{ str }, depth{ depth }, hasBeach{ hasBeach }, width{ width }
  {
	node.append_attribute("type1").set_value(static_cast<int>(Type::water));
	node.append_attribute("spec1").set_value(static_cast<int>(spec));
	node.append_attribute("struct").set_value(static_cast<int>(str));

	node.append_attribute("depth").set_value(depth);
	node.append_attribute("width").set_value(width);
	node.append_attribute("hasBeach").set_value(hasBeach);

	setCoords(x, y);

	genName();
	genDescription();

  }

  void input() {
	MapSymbol::input();

	int i;
	cout << "<< Укажите тип водоема : { 1 -> " << specWaterArr[2] << ", 2 -> " << specWaterArr[3] << " }\n>> ";
	cin >> i;
	if (i < 1 || i > 2) i = 0;

	node.attribute("type1").set_value(static_cast<int>(Type::water));

	node.attribute("spec1").set_value(i);
	spec = static_cast<Spec_water>(i);

	cout << "<< Укажите характер грунта дна : { 1 -> " << structBottomArr[1] << ", 2 -> " << structBottomArr[2] << ", 3 -> " << structBottomArr[3] << " }\n>> ";
	cin >> i;
	if (i < 1 || i > 2) i = 0;
	node.attribute("struct").set_value(i);
	str = static_cast<Struct_bottom>(i);

	cout << "<< Введите глубину водоема в метрах :\n>> d=";
	cin >> depth;
	node.attribute("depth").set_value(depth);

	cout << "<< Введите ширину водоема в метрах :\n>> w=";
	cin >> width;
	node.attribute("width").set_value(width);

	genName();
	genDescription();

  }

  void setDepth(double depth) {
	this->depth = depth;
	node.attribute("depth").set_value(depth);
  };
  double getDepth() { return depth; }

  void genName() {
	name += "водоем типа : " + specWaterArr[static_cast<int>(spec)] + ", с грунтом дна, который можно охарактеризовать как : " + structBottomArr[static_cast<int>(str)] + "; его глубина и ширина составляют " + to_string(depth) + "м. и " + to_string(width) + "м. соответственно.";

	node.child("name").append_child(pugi::node_pcdata).text().set(name.c_str());

  }

  void genDescription() {
	descr += "с помощью кривой синего цвета, отражающей береговую линию, ограниченную ей поверхность закрашивают синим цветом более светлого оттенка и указывают шрифтом того же цвета что и кривая такие характеристики как : глубина, ширина и характер грунта дна.";

	node.child("description").append_child(pugi::node_pcdata).text().set(descr.c_str());

  }

private:
  bool hasBeach;
  double width;

  Spec_water spec;
  Struct_bottom str;

  array< string, 4 > structBottomArr = { "не определена", "твердый", "вязкий", "каменистый" };

  //Type type;

protected:
  double depth;
  array< string, 4> specWaterArr = { "не определен", "болото", "река", "озеро" };

};
// Болото, множественное наследование V
class Swamp : public Water, public Relief {
public:

  /* Нужно по человечески переписать конструктор по умолчанию */

  Swamp() : MapSymbol{}, state{}, str{}
  {
	node.append_attribute("type1").set_value(static_cast<int>(Type::relief));
	node.append_attribute("type2").set_value(static_cast<int>(Type::water));

	node.append_attribute("spec1").set_value(static_cast<int>(Spec_relief::lowLand));
	node.append_attribute("spec2").set_value(static_cast<int>(Spec_water::swamp));

	node.append_attribute("state").set_value(0);
	node.append_attribute("struct").set_value(0);

	node.append_attribute("depth").set_value(0);
	node.append_attribute("heigh").set_value(0);

  }
  Swamp(int x, int y, double depth, double heigh, State_swamp state, Struct_swamp str) : Water(depth, Spec_water::swamp), Relief(heigh, Spec_relief::lowLand), state{ state }, str{ str }
  {

	node.append_attribute("state").set_value(static_cast<int>(state));
	node.append_attribute("struct").set_value(static_cast<int>(str));

	setCoords(x, y);

	genName();
	genDescription();

  }
  // Для вызова методов нужно использовать оператор глобального разрешения.
  // Нужно вызвать параметризованные конструкторы рельефа и водоема

  void input() {
	// Написать независимый ввод.

	MapSymbol::input();

	int i;
	cout << "<< Укажите состояние болота : { 1 -> " << stateSwampArr[1] << ", 2 ->" << stateSwampArr[2] << ", 3 ->" << stateSwampArr[3] << " }\n>> ";
	cin >> i;
	if (i < 0 || i > 3) i = 0;
	node.attribute("state").set_value(i);
	state = static_cast<State_swamp>(i);

	if (state != State_swamp::drained) {
	  cout << "<< Укажите тип растительного покрова болота : { 1 -> " << structSwampArr[1] << ", 2 -> " << structSwampArr[2] << ", 3 -> " << structSwampArr[3] << " }\n>> ";
	  cin >> i;
	  if (i < 0 || i > 3) i = 0;
	  node.attribute("struct").set_value(i);

	  str = static_cast<Struct_swamp>(i);
	}

	cout << "<< Введите глубину болота :\n>> ";
	cin >> depth;
	node.attribute("depth").set_value(depth);

	cout << "<< Введите высоту, на которой расположено болото относительно уровня моря :\n>> ";
	cin >> heigh;
	node.attribute("heigh").set_value(heigh);

	genName();
	genDescription();

  }

  void drainSwamp() {
	if (state != State_swamp::drained)
	  state = State_swamp::drained;

	node.attribute("state").set_value(static_cast<int>(state));
  }

  void genName() {
	name += stateSwampArr[static_cast<int>(state)] + " болото, глубина и высота над уровнем моря которого составляют " + to_string(depth) + "м. и " + to_string(heigh) + "м. соответственно.";

	node.child("name").append_child(pugi::node_pcdata).text().set(name.c_str());

  }

  void genDescription() {
	switch (state) {
	case State_swamp::drained:
	  descr += "прямоугольника, заполненного светлым оттенком зеленого цвета (также как моховую или лишайниковую растительность)";
	  break;
	case State_swamp::traversable:
	  descr += "прерывающихся линий уровня, голубого цвета, символизирующих рябь на поверхности болота из-за стоячей воды, пространство между ними заполняют светлым оттенком зеленого цвета, между линиями схематически изображают растительный покров болота : " + structSwampArr[static_cast<int>(str)];;
	  break;
	default:
	  descr += "непрерывных линий уровня, голубого цвета, символизирующих рябь на поверхности болота из-за стоячей воды, пространство между ними заполняют светлым оттенком зеленого цвета, между линиями схематически изображают растительный покров болота : " + structSwampArr[static_cast<int>(str)];
	  break;
	}

	node.child("description").append_child(pugi::node_pcdata).text().set(descr.c_str());

  }

private:
  State_swamp state;
  Struct_swamp str;

  array< string, 4 > structSwampArr = { "не опрелен", "травянистый", "моховой", "тростниковый" };
  array< string, 4> stateSwampArr = { "не определено", "проходимое", "труднопроходимое", "непроходимое" };


};
// Дорога
class Road : public MapSymbol {
public:
  Road() : MapSymbol(), spec{}, str{}, state{}, numStripes{}, roadWidth{}, stripWidth{}
  {

	node.append_attribute("type1").set_value(static_cast<int>(Type::road));
	node.append_attribute("spec1").set_value(0);

	node.append_attribute("state").set_value(0);
	node.append_attribute("struct").set_value(0);

	node.append_attribute("numStripes").set_value(0);
	node.append_attribute("roadWidth").set_value(0);
	node.append_attribute("stripWidth").set_value(0);

  }

  Road(int x, int y, int numStripes, int stripWidth, int roadWidth, Spec_road spec, State_road state, Struct_road str) : MapSymbol(), spec{ spec }, str{ str }, state{ state }, numStripes{ numStripes }, stripWidth{ stripWidth }, roadWidth{ roadWidth }
  {

	node.attribute("type1").set_value(static_cast<int>(Type::road));
	node.attribute("spec1").set_value(static_cast<int>(spec));

	node.append_attribute("state").set_value(static_cast<int>(state));
	node.append_attribute("struct").set_value(static_cast<int>(str));

	node.append_attribute("numStripes").set_value(numStripes);
	node.append_attribute("stripWidth").set_value(stripWidth);

	node.append_attribute("roadWidth").set_value(roadWidth);

	setCoords(x, y);

	genName();
	genDescription();

  }

  void input() {
	MapSymbol::input();

	int i;

	cout << "<< Укажите тип дороги : { 1 -> " << specRoadArr[1] << ", 2 -> " << specRoadArr[2] << ", 3 -> " << specRoadArr[3] << ", 4 -> " << specRoadArr[4] << " }\n>> ";
	cin >> i;
	if (i < 1 || i > 4) i = 0;
	spec = static_cast<Spec_road>(i);
	node.attribute("spec1").set_value(i);

	cout << "<< Опишите состояние дорожного покрытия : { 1 -> " << stateRoadArr[1] << ", 2 -> " << stateRoadArr[2] << ", 3 -> " << stateRoadArr[3] << " }\n>> ";
	cin >> i;
	if (i < 1 || i > 3) i = 0;
	state = static_cast<State_road>(i);
	node.attribute("state").set_value(i);

	cout << "<< Укажите материал дорожного покрытия : { 1 -> " << structRoadArr[1] << ", 2 -> " << structRoadArr[2] << ", 3 -> " << structRoadArr[3] << " }\n>> ";
	cin >> i;
	if (i < 1 || i > 3) i = 0;
	str = static_cast<Struct_road>(i);
	node.attribute("struct").set_value(i);

	cout << "<< Введите количество полос :\n>> "; cin >> numStripes;
	node.attribute("numStripes").set_value(numStripes);

	cout << "<< Введите ширину одной полосы в метрах :\n>>"; cin >> stripWidth;
	node.attribute("stripWidth").set_value(stripWidth);

	cout << "<< Введите ширину покрытой части в метрах :\n>>"; cin >> roadWidth;
	node.attribute("roadWidth").set_value(roadWidth);

	genName();
	genDescription();

  }

  void genName() {
	name += "дорожное покрытие, типа " + specRoadArr[static_cast<int>(spec)] + "из материала : " + structRoadArr[static_cast<int>(str)] + ", шириной : " + to_string(roadWidth) + ", с количеством полос : " + to_string(numStripes) + ", каждая из которых имеет ширину : " + to_string(stripWidth) + "; Его состояния очениватся как " + stateRoadArr[static_cast<int>(state)] + ".";

	node.child("name").append_child(pugi::node_pcdata).text().set(name.c_str());
  }

  void genDescription() {
	switch (spec) {
	case Spec_road::backRoad:
	  descr += "с помощью 2х параллельных линий серого цвета, между которыми указывают ширину проезжей части в метрах.";
	  break;
	default:
	  descr += "с помощью коричневого прямоугольника шириной, соответствующей протяженности дороги в масштабе карты, прямоугольник разделяют линиями, символизирующими полосы.";
	  break;
	}

	node.child("description").append_child(pugi::node_pcdata).text().set(descr.c_str());

  }

private:
  int numStripes;
  int stripWidth;
  int roadWidth;

  array< string, 5> specRoadArr = { "не определен", "шоссе", "магистраль", "автострада", "грунтовая дорога" };
  array< string, 4> stateRoadArr = { "не определено", "отличное", "поврежденное", "на ремонте" };
  array< string, 4> structRoadArr = { "не определено", "щебень", "альфальт", "цементобетон" };

  Spec_road spec;
  State_road state;
  Struct_road str;
};
