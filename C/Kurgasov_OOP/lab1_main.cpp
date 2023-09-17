#include<iostream>
#include<vector>
#include<string>
#include<regex>
#include<chrono>

using namespace std;
class Cell{
public:  
  bool isClosed;
  bool isFlagged;
  bool isOppened;
  bool isMined;
  int minesInAdjCells;
public: 
  void setMine();
  void setFlag();
  void setNumOfMines(int n); // ?
  string getPrintStatus(){
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
    
  int minedSells;
  // Отображаемая информация
  int flaggedCells;
  int size;
  // Время начала игры (инициализируется в конструкторе)
  bool isStartTime;
  chrono::time_point<chrono::steady_clock> st;
  chrono::time_point<chrono::steady_clock> cur;

  // Введенная пользователем команда
  string inpt;

  void openCell(int x, int y);
  void flagCell(int x, int y);
  void mineCell(int x, int y);

public:
  bool isExit;
  void printBoard();
  void handleUserInput();
  // Конструктор создает доску
  Board(){
    isStartTime = true;
    size = 10; isExit = false;
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
  if (isStartTime){
    st = chrono::steady_clock::now();
    isStartTime = false;
  }
  cur = chrono::steady_clock::now();
  string frow = "Число мин : " + to_string(minedSells) + ", Пройденное время : " + to_string(chrono::duration_cast<chrono::seconds> (cur-st).count()) + " с.\n", zrow = "   ", row; // Создаем пустую строку
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
      row = row + (isExit && board[i][j].getPrintStatus() == "*" ? "*" : "+") + " ";
    }
    row = row + "|" + to_string(i) + "\n";
    cout << row; row.clear();
  }
  cout << zrow << endl;
}

void Board::handleUserInput(){
  string abc = "abcdefghijklmnopqrstuvwxyz";
  string prompt = "- Введите команду, общий вид : <Ф-ция>_[<Координата x><Координата y>]\n\nМножество ф-ций : {\n\tM - установить мину на указанную ячейку,\n\tF - отметить указанную ячейку,\n\tO - открыть указанную ячейку,\n\tE - Показать расположение всех мин и завершить игру\n}\n+ Координаты ячейки задаются парой символов : координатой по x - символом из : {a-" + string(1, abc[size-1]) + "} И координатой по у - {0-9}\n\n>";
  cout << prompt;
  cin >> inpt;
  // Переходим к регуляркам, нужно проверить : соответствует ли ввод определенному шаблону 
  // Доработать эту регулярку
  if (regex_match(inpt, regex("(^[OFM] [a-j][0-9]$)"))){
    if (inpt[0] == 'O') {
      // Вызываем логику игры
      // Надо поставить в соответствие букве цифру
      openCell(abc.find(inpt[2]), inpt[3]);
    } else if (inpt[0] == 'F'){
      flagCell(abc.find(inpt[2]), inpt[3]);
    } else {
      mineCell(abc.find(inpt[2]), inpt[3]);
    }
  } else if (regex_match(inpt, regex("(^E$)"))){
    // Показываю все мины и завершаю игру
    isExit = true;

  } else {
    cout << "\n< Команда не распознана" << endl;
  }
}

void Board::openCell(int x, int y){
  // Прописать логику
}

void Board::mineCell(int x, int y){
  // Просто сморю минированна ли ячейка ?
  if (board[x][y].isMined){
    cout << "[!] Эта ячейка уже содержит мину." << endl;
  } else {
    board[x][y].isMined = true;
  }
}
void Board::flagCell(int x, int y){
  if (board[x][y].isFlagged){
    board[x][y].isFlagged = false;
  } else {
    board[x][y].isFlagged = true;
  }
}

void startGame(){
  cout << "! Игра Сапер !\nВведите команду, множество команд : {\n\t1 -> Начать новую игру,\n\t2 -> Завершить работу программы\n}" << endl;
  int inpt; bool isExit = false;
  Board inst;
  while (!isExit)
  {
    cin >> inpt; 
    if (inpt == 1){
      inst.printBoard();
      while (!inst.isExit){
        inst.handleUserInput();
        inst.printBoard();
      }
    } else if (inpt == 2) {
      cout << "Работа программы завершена" << endl; isExit = true;
    } else {
      cout << "Команда не распознана" << endl;
    }
  }

}

int main(){
  startGame();
  
  return 0;
}