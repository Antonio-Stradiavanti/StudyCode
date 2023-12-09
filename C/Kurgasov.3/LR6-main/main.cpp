#include "hierarchy.h"
#include "xml_catalog.h"
//using namespace pugi;
/* 

  Задание : Отработать механизм с потоками ввода и вывода на примере xml файла, а не изучать географию, нужна только приблизительная модель справочника условных знаков, только родительский и дочерние узлы, в роли справочника будет выступать xml файл.

  Реализовать ведение справочников для предметной области "условные знаки"
  Необходимо : 3 уровня в иерархии классов с множественным наследованием, операции : добавление, редактирование, удаление записей.

  Операции сериализации выполняем с классом XML (он аггрегирует данные)

*/

void printHelp() {
  cout << "\nМножество команд : {\n  1 -> Завершить работу программы\n  2 -> Добавить запись\n  3 -> Удалить запись\n  4 -> Редактировать запись\n  5 -> Выгрузить справочник в XML файл\n  6 -> Загрузить справочник из XML файла\n  7 -> Предпросмотр XML документа\n  8 -> Вывести справочник\n  9 -> Вывести справку\n}\n" << endl;
}
void menu() {

  vector < MapSymbol* > list;
  MapSymbol* tmp = nullptr;
  
  XML xml;

  int c, t, x, y;
  array<int, 2> tmpArr, latAndLonArr;

  cout << "\n***\n\nСправочник для предметной области \"Условные знаки\"" << endl;
  printHelp();

  while (true) {
    cout << "[Главное меню] Введите команду :\n>> "; cin >> c;

    switch (c) {
    case 1:
      cout << "<< Завершение работы ... " << endl;
      return;

      break;
    case 2:
      cout << "<< Выберите доступный тип топографического объекта : { 1 -> скала, 2 -> водоем, 3 -> болото, 4 -> дорога  }\n>> ";
      cin >> t;

      switch (t) {
      case 1:
        list.push_back(tmp);
        list[list.size() - 1] = new Relief{};
        break;
      case 2:
        list.push_back(tmp);
        list[list.size() - 1] = new Water{};
        break;
      case 3:
        list.push_back(tmp);
        list[list.size() - 1] = new Swamp{};
        break;
      case 4:
        list.push_back(tmp);
        list[list.size() - 1] = new Road{};
        break;
      default:
        cout << "<! Введен некорректный тип топографического объекта, отбой операции !>" << endl;
        continue;
        break;
      }

      list[list.size() - 1]->input();

      break;
    case 3:
      cout << "<< Введите координаты топографического объекта, который желаете удалить из справочника :" << endl;
      cout << ">> x=";
      cin >> x;
      cout << ">> y=";
      cin >> y;

      for (int i = 0; i < list.size(); ++i) {
        tmpArr = list[i]->getCoords();
        if (x == tmpArr[0] && y == tmpArr[1]) {
          list.erase(list.begin() + i);
          break;
        }
      }
      break;
    case 4:
      cout << "<< Введите координаты топографического объекта, данные которого желаете редактировать :" << endl;
      cout << ">> x=";
      cin >> x;
      cout << ">> y=";
      cin >> y;

      latAndLonArr = list[0]->getLatAndLong();
      x -= latAndLonArr[0] * 111; y -= latAndLonArr[1] * 111;

      for (int i = 0; i < list.size(); ++i) {
        tmpArr = list[i]->getCoords();
        if (x == tmpArr[0] && y == tmpArr[1]) {
          cout << "V Искомая запись найдена, введите новые значения :" << endl;
          list[i]->input();
          break;
        }
      }

      break;
    case 5:
      for (int i = 0; i < list.size(); ++i) {
        xml.add(list[i]->getNode());
      }
      xml.save();
      break;
    case 6:
      for (int i = 0; i < list.size(); ++i) {
        delete list[i];
      }
      list.clear();
      xml.load(list);
      break;
    case 7:
      xml.print();
      break;
    case 8:
      if (!list.size()) {
        cout << "<< Ваш справочник пуст есть" << endl;
        continue;
      }
      for (int i = 0; i < list.size(); ++i) {
        list[i]->print();
      }
      break;
    case 9:
      printHelp();
      break;
    default:
      cout << "<! Команда не распознана. !>" << endl;
      break;
    }

  }

}

bool fa(pugi::xml_attribute atr) {
  return strcmp(atr.name(), "type2") == 0;
}

int main() {
  
  // Тесты и эксперименты
  

  // PugiXML соответствует DOM
  // Контейнер сериализации
  //pugi::xml_document doc, newDoc;
  // Выполняет парсинг XML документа

  //pugi::xml_parse_result result = doc.load_file("x0.xml");

  //cout << "Значение latLong : " << doc.child("LandMap").child("latLong").child("x").child_value() << endl;
  /*pugi::xml_node node = doc.child("LandMap").child("MapSymbols");

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

  }*/
  // Передаем в конструктор имя узла и создаем узел типа тег или явно указываем тип узла, чтобы создать например текстовый узел (pugi::node_pcdata).
  //pugi::xml_node n = newDoc.append_child("Главный Тег");
  //pugi::xml_node nc = n.append_child("Его потомок");
  //nc.append_child(pugi::node_pcdata).set_value("Просто обычный текст !");

  //cout << "Результат операции \" сохранить файл \" : " << newDoc.save_file("x1.xml") << endl;

  //Menu menu;

  //menu.start();

  menu();


  return 0;
}