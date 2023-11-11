#include<iostream>
#include<algorithm>

using namespace std;
int main () {
    // 10 -> размер массива символов
    char t0[10] = "abcdefgho";
    char* t1 = new char[10];
    copy(t0, t0+10, t1);
    cout << t1 << endl;
}
