#pragma once
#include<iostream>
#include<vector>
#include<array>
#include<string>
using namespace std;

/* MapSymbol : корень иерархии классов */
class MapSymbol {
public:

  enum Type1 {
    none, relief, vegCover, water, humanSettlement, road, localObject
  };
  enum Type2_relief {
    none, desert, mountain, volcano, lowLand
  };
  enum Type2_water {
    none, swamp, river
  };
  enum Type2_vegCover {
    none, forest, grove, protectivePlantings
  };
  enum Type2_road {
    none, highRoad, mainRoad, backRoad, federalRoad
  };
  enum State_road {
    perfect, damaged, underСonstruction
  };
  enum State_vegCover {
    burnt, windfall, logged, smallWood
  };
  enum Structure_vegCover {
    greenWood, softWood, mixedWood
  };
  enum Structure_road {
    pebbels, asphalt, cementConcrete
  };
  enum State_swamp {
    drained, traversable, unTraversable, barelyPassable
  };

  // Конструкторы
  MapSymbol() : coords{ 0, 0 }, type1{} {}
  MapSymbol(Type1 type) : coords{ 0, 0 }, type1{ type } {}
  
  // Методы 
  virtual void setDescription() = 0;
  //virtual void input() = 0;

  string getDecsription() {
    return symbolDescr;
  }

  void setLatAndLong(int lat, int lon) {
    latAndLong[0] = lat, latAndLong[1] = lon;
  }
  array<int, 2> getLatAndLong() { return latAndLong; }

  void setCoords(int x, int y) {
    coords[0] = x; coords[1] = y;
  }

  void print() {
    cout << "Координаты : x=" << (/*111 * latAndLong[0] +*/ coords[0]) << ", y=" << (/*111 * latAndLong[1] + */ coords[1]) << "\n\nОписание : " << symbolDescr << endl;
  }

private:
  static array<int, 2> latAndLong;
  array<int, 2> coords;
  
  Type1 type1;

protected:
  string symbolDescr;

  pugi::xml_document doc;
  pugi::xml_node node;

};
array<int, 2> MapSymbol::latAndLong = { 0, 0 };
/* Производные классы от MapSymbol */
// Описывает возвышенность, низменность, наледь.
class Relief : virtual public MapSymbol {
public:

  // Объект рельефа мы не создаем.
  Relief() : type2{}, height{}, altitude{} {}
  Relief(Type2_relief spec, double altitude = 0, double height = 0) : MapSymbol(Type1::relief), height{ height }, altitude{ altitude }, type2{ spec } {}

  void setHeight(double height) { this->height = height; };
  void setAltitude(double altitude) { this->altitude = altitude; }

  double getAltitude() { return altitude; }
  double getHeight() { return height; }

private:
  Type2_relief type2;

  double height;
  double altitude;

};
// Описывает водоем
class Water : virtual public MapSymbol {
public:


  Water() : type2{}, depth{} {}
  Water(Type2_water spec, double depth) : MapSymbol(Type1::water), type2{ spec }, depth{ depth } {}
  // Объект водоема мы не создаем.
  void setDepth(double depth) { this->depth = depth; };
  double getDepth() { return depth; }

private:
  Type2_water type2;
  double depth;
};
// Болото, множественное наследование
class Swamp : public Water, public Relief {
public:

  Swamp() : Water(), Relief(), state{} {}
  Swamp(int lat, int lon, int x, int y, State_swamp state, double depth) : Water(Type2_water::swamp, depth), Relief(Type2_relief::lowLand), state{ state } {
    setLatAndLong(lat, lon);
    setCoords(x, y);

  }
  // Для вызова методов нужно использовать оператор глобального разрешения.
  // Нужно вызвать параметризованные конструкторы рельефа и водоема
  void setDescription() {
    string s = " болото, глубиной d=" + to_string(getDepth()) + "м : ";
    switch (state) {
    case drained:
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
  State_swamp state;

};
class Road : public MapSymbol {
public:
  // - [ ] Написать конструкторы
private:  
  int numStripes;
  int roadWidth;
  int stripWidth;

  Type2_road type2;
  Structure_road str;
  State_road state;
};
class VegCover : public MapSymbol {
public:
  VegCover() : MapSymbol(), type2{Type2_vegCover::none} {}
  VegCover(int lat, int lon, int x, int y, Type2_vegCover type2, Structure_vegCover str, State_vegCover state, int width, double avgThreeHeight, int treesNum) : MapSymbol(Type1::vegCover), type2{ type2 }, str{ str }, state{state}, width{ width }, avgThreeHeight{ avgThreeHeight }, treesNum{ treesNum } {
    setLatAndLong(lat, lon); setCoords(x, y);
  }
  
  void plantNewThrees(int newTreesNum) { treesNum += newTreesNum; }

  void updateState(State_vegCover newState) { state = newState; }

private:
  int width;
  double avgThreeHeight;
  int treesNum;

  Type2_vegCover type2;
  Structure_vegCover str;
  State_vegCover state;
};