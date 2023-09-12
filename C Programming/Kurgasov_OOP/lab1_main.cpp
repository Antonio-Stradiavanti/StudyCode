#include<iostream>
#include<vector>
#include<string>
#include<regex>
#include<ctime>

using namespace std;
class Cell{
  bool isClosed;
  bool isFlagged;
  bool isOppened;
  bool isMined;
  int minesInAdjCells;
public: 
  void setMine();
  void setFlag();
  void setNumOfMines(int n); // ?
  string getStatus(){
    string res;
    if (isClosed){
      res="+";
    } else {
      if (isFlagged){
        res="F";
      } else if (isMined) {
        res="*";
      } else {
        res=to_string(minesInAdjCells);
      }
    }
    return res;
  }
  // Логика игры
  Cell(){
    isClosed = true;
    isFlagged = false;
    isOppened = false;
    isMined = false;
    minesInAdjCells = 0;
  }
};
class Board
{
  vector< vector<Cell> > board;
  
  clock_t timer;
  
  int minedSells;
  // Отображаемая информация
  int flaggedCells;
  int timeSiceStart;
  int size;
  // Флаги
  bool isGameOver;
  bool showMined;
  // Введенная пользователем команда
  string inpt;
public:
  // Вывод доски
  void printBoard();
  void openCell(int x, int y);
  // Обработать ввод
  void handleUserInput();
  // Основной интерфейс пользователя.
  void startGame();
  // Конструктор создает доску
  Board(){
    //timer = clock();
    size = 10; showMined = false;
    for (int i = 0; i < size; i++){
      vector<Cell> tmpV; 
      for (int j = 0; j < size; j++){
        Cell tmpC = Cell();
        tmpV.push_back(tmpC);
      }
      board.push_back(tmpV);
    }
  }
  
};
 
void Board::printBoard(){
  string frow;//= "Число мин : " + to_string(minedSells) + ", Пройденное время : " + to_string(timer) + "\n",
  string zrow = "   ", row; // Создаем пустую строку
  string abc = "abcdefghijklmnopqrstuvwxyz";
  int i, j;
  for (i = 0; i < board.size()-1; i++){
    zrow = zrow + abc[i] + " ";
  }
  zrow = zrow + abc[i] + "\n   ";
  for (i = 0; i < board.size()-1; i++){
    zrow += "--";
  }
  zrow += "-";
  // Терерь выводим строки
  cout << frow << zrow << "\n";
  for (i = 0; i < board.size(); i++){
    row = row + to_string(i) + "| ";
    for (j = 0; j < board[i].size(); j++){
      row = row + (showMined && board[i][j].getStatus() == "*" ? "*" : "+") + " ";
    }
    row = row + "|" + to_string(i) + "\n";
    cout << row; row.clear();
  }
  cout << zrow << endl;
}

void Board::handleUserInput(){
  string abc = "abcdefghijklmnopqrstuvwxyz";
  string prompt = "Введите команду, общий вид : <Ф-ция>_[<Координата x><Координата y>]\nМножество ф-ций : {M - установить мину на указанную ячейку, F - отметить указанную ячейку, O - открыть указанную ячейку, E - Показать расположение всех мин и завершить игру}\nКак указать ячейку ? : Координаты ячейки задаются парой символов : координатой по x - символом из множества : {" + abc.substr(0, size) + "} и координатой по у - цифрой от 0 до 9\n\n>";
  cout << prompt;
  cin >> inpt;
  // Переходим к регуляркам, нужно проверить : соответствует ли ввод определенному шаблону 
  if (regex_match(inpt, regex("(^[OFM] [a-j][0-9]$)"))){
    if (inpt[0] == 'O') {
      // Вызываем логику игры
      // Надо поставить в соответствие букве цифру
      openCell(abc.find(inpt[2]), inpt[3]);
    }
  } else if (regex_match(inpt, regex("(^E$)"))){
    // Показываю все мины и завершаю игру
    showMined = true;

  } else {
    cout << "Команда не распознана" << endl;
  }
}

void Board::openCell(int x, int y){

}

int main(){
  Board brd;
  bool cont = true;
  string tmp;
  while (cont) {
    brd.printBoard();
    cout << "Продолжить ? : " << endl;
    cin >> tmp;
    if (tmp == "y" || tmp == "yes"){
      cont = true;
    } else {
      cont = false;
    }
  }
  
  return 0;
}