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
  // Логика игры
  Cell(){
    isClosed = true;
    isFlagged = false;
    isMined = false;
    minesInAdjCells = 0;
  }
};
class Board
{
public:
  // Конструктор создает доску
  Board(){
    isStartT = true; isStartH = true;
    isExit = false;

    flaggedCells = 0;
    oppenedCells = 0;
    minedCells = 0;

    size = 10; 
    
    for (int i = 0; i < size; i++){
      vector<Cell> tmpV; 
      for (int j = 0; j < size; j++){
        Cell tmpC = Cell();
        tmpV.push_back(tmpC);
      }
      board.push_back(tmpV);
    }
  }
  void startGame();
private:
  vector< vector<Cell> > board;
  vector<string> stat;

  int minedCells;
  // Отображаемая информация
  int flaggedCells;
  int oppenedCells;
  int size;
  // Время начала игры (инициализируется в конструкторе)
  bool isStartT; bool isStartH;
  bool isExit;

  chrono::time_point<chrono::system_clock> st;
  chrono::time_point<chrono::system_clock> cur;

  void openCellsRecursive(int x, int y);
  void openCell(int x, int y);
  void flagCell(int x, int y);
  void mineCell(int x, int y);


  void printBoard();
  void handleUserInput();
  
  // События
  void onFail();
  void onWin();

  string makeStat(){
    string lStat = "Продолжительность игры : " + to_string(chrono::duration_cast<chrono::seconds> (cur-st).count()) + "; Число открытых ячеек : " + to_string(oppenedCells) + "; число оставшихся мин : " + to_string((minedCells-1 < 0 ? 0 : minedCells-1));
    return lStat;
  }
  void setNumOfMines(int n); // ?
  string getStatus(int x, int y){
    string res;
    if (board[y][x].isClosed){
      if(board[y][x].isFlagged){
        res="F";
      } else if (board[y][x].isMined){
        if (isExit) res="*";
        else res = "+";
      } else {
        res="+";
      }
    } else {
      res=to_string(board[y][x].minesInAdjCells);
      // Иначе - конец игре.
    }
    return res;
  }

};
 
void Board::printBoard(){
  if (isStartT){
    st = chrono::system_clock::now();
    isStartT = false;
  }
  cur = chrono::system_clock::now();
  string frow = "\nЧисло мин : " + to_string(minedCells-flaggedCells) + "; Число открытых ячеек : " + to_string(oppenedCells) + "; Пройденное время : " + to_string(chrono::duration_cast<chrono::seconds> (cur-st).count()) + " с.\n", zrow = "   ", row; // Создаем пустую строку
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
      row = row + getStatus(j, i) + " ";
      //row = row + (isExit && board[i][j].getPrintStatus() == "*" ? "*" : "+") + " ";
    }
    row = row + "|" + to_string(i) + "\n";
    cout << row; row.clear();
  }
  cout << zrow << endl;
}

void Board::handleUserInput(){
  string inpt, abc = "abcdefghijklmnopqrstuvwxyz";
  string localPrompt = "Для выхода из игры введите E, для вывода справки -> H\n[Введите команду : <Функ.><?xy>]$ ";
  string globalPrompt = "\n! Справка\n\nМножество ф-ций : {\n\tM - установить мину на указанную ячейку,\n\tF - отметить указанную ячейку,\n\tO - открыть указанную ячейку,\n\tE - Показать расположение всех мин и завершить игру,\n\tH - Вывести справку\n}\n+ Координаты ячейки (для команд O, F, и M) -> задаются парой символов :\n\tКоординатой по Ox - символом из : {a-" + string(1, abc[size-1]) + "}\n\tИ\n\tКоординатой по Oу -> {0-9}\n";
  if (isStartH) {
    lb:
    cout << globalPrompt; isStartH = false;
  }
  cout << localPrompt; cin >> inpt;
  // Переходим к регуляркам, нужно проверить : соответствует ли ввод определенному шаблону 
  // Доработать эту регулярку
  if (regex_match(inpt, regex("(^[OFM][a-j][0-9]$)"))){
    if (inpt[0] == 'O') {
      // Вызываем логику игры
      // Надо поставить в соответствие букве цифру
      openCell(abc.find(inpt[1]), inpt[2] - '0');
    } else if (inpt[0] == 'F'){
      // Первый факт. параметр - целое, второй - символ.
      flagCell(abc.find(inpt[1]), inpt[2] - '0');
    } else if (inpt[0] == 'M'){
      mineCell(abc.find(inpt[1]), inpt[2] - '0');
    }
  } else if (regex_match(inpt, regex("(^E$)"))){
    // Показываю все мины и завершаю игру
    onFail();
    cout << "< Завершаем игру, покажем мины..." << endl;
  } else if (regex_match(inpt, regex("(^H$)"))) {
    cout << "< Выведем справку..." << endl;
    goto lb;
  } else {
    cout << "! Команда не распознана" << endl;
  }
}

void Board::openCellsRecursive(int x, int y){
  //cout << "Тут потеря" << endl;
  // Тут будет условие выхода из рекурсии.
  // Рекурсивно будем вызывать если число мин окрест - 0
  board[y][x].isClosed = false;
  oppenedCells++;
      
  // Просто считаю число мин в смежных ячейках и увеличиваю его на 1.
  int i, j;
  for ((y == 9 ? i = 0 : i = -1); (y == 0 ? i <= 0 : i <= 1); i++){
    for ((x == 9 ? j = 0 : j = -1); (x == 0 ? j <= 0 : j <= 1); j++){
      if (board[y-i][x-j].isClosed && board[y-i][x-j].isMined) board[y][x].minesInAdjCells++;
    }
  }
  // Если так случилось, что в смежный ячейках нет ни одной мины, то я рекурсивно открываю все смежные НЕ открытые ячейки
  if (!board[y][x].minesInAdjCells){
    for ((y == 9 ? i = 0 : i = -1); (y == 0 ? i <= 0 : i <= 1); i++){
      for ((x == 9 ? j = 0 : j = -1); (x == 0 ? j <= 0 : j <= 1); j++){
        // Проблема с рекурсией, нет нормального условия выхода.
        if (board[y-i][x-j].isClosed) openCellsRecursive(x-j, y-i);
      }
    }
  } else if (board[y][x].minesInAdjCells || oppenedCells + minedCells + flaggedCells == 100) {
    // В противном случае завершаю работу подпрограммы.
    return;
  }
}
void Board::openCell(int x, int y){
  cout << "< Откроем мину с координатами (" << x << ", " << y << ")" << endl;
  // Прописать логику
  // если ячейка содержит мину то игра окончена
  if (board[y][x].isClosed){
    if (board[y][x].isMined) {
      onFail();
    } else if (board[y][x].isFlagged){
      cout << "! Снимите метку прежде чем открыть ячейку" << endl; 
    } else {
      openCellsRecursive(x, y);
    }
  } else {
    cout << "! Ячейка уже открыта" << endl;
  }  
}

void Board::mineCell(int x, int y){
  // Просто сморю минированна ли ячейка ?
  if (board[y][x].isClosed && board[y][x].isMined){
    cout << "! Эта ячейка уже содержит мину." << endl;
  } else if (board[y][x].isClosed && !board[y][x].isMined){
    cout << "< Установим мину на ячейку (" << x << ", " << y << ")" << endl;
    board[y][x].isMined = true; minedCells++;
  } else {
    cout << "! Ячейка уже открыта" << endl;
  }
}
void Board::flagCell(int x, int y){
  if (board[y][x].isClosed && board[y][x].isFlagged){
    cout << "< Отметим потенциальное расположение мины в ячейке с координатами (" << x << ", " << y << ")" << endl;
    board[y][x].isFlagged = false; flaggedCells--;
  } else if (board[y][x].isClosed && !board[y][x].isFlagged) {
    board[y][x].isFlagged = true; flaggedCells++;
  } else {
    cout << "! Ячейка уже открыта" << endl;
  }
}
void Board::onFail(){
  cout << "): Игра завершена, вы проиграли; сохраненяем статистику, покажем оставшиеся мины...\n< " << makeStat() << endl;
  stat.push_back(makeStat()); 

  cur = chrono::system_clock::now();
  isExit = true;
}
void Board::onWin(){
  cout << ":) Поздравляем, вы выиграли ! Сохраняем статистику...";
  stat.push_back(makeStat()); 

  cur = chrono::system_clock::now();
}

void Board::startGame(){
  cout << "! Игра Сапер !";
  string prompt = "\nВведите команду, множество команд : {\n\t1 - Начать новую игру,\n\t2 - Вывести статистику игр,\n\t3 - Завершить работу программы\n}";
  int inpt, i = 0;
  bool isExitApp = false;
  while (!isExitApp)
  {
    cout << prompt << endl;
    cin >> inpt; 
    switch (inpt) {
    case 1:
      printBoard();
      while (!isExit){
        if (oppenedCells + minedCells == 100){
          onWin(); break;
        } else {
          handleUserInput();
          printBoard();
        }
      }
      break;
    case 2:
      cout << "! Недавно вы провели " << stat.size() << " игр !" << endl;
      for (vector<string>::const_iterator it = stat.begin(); it != stat.end(); it++, i++){
        cout << "Игра №" << i << " - " << *it << endl;
      }
      break;
    case 3:
      cout << "< Работа программы завершена" << endl; isExitApp = true;
      break;
    default:
      cout << "! Команда не распознана" << endl;
      break;
    }
  }
}

int main(){
  Board minesweeper;
  minesweeper.startGame();
  return 0;
}