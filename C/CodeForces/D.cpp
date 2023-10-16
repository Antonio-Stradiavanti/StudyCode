#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int solve(vector<int> &in)
{
  int count = 0;

  // 1я строка
  /*


  // Последовательность (2я строка)
  /*
  for (int i = 0; i < n; ++i) {
    cin >> vec[i];
    if (vec[i] > 2*pow(10, 9)) {
      cout << "-1" << endl ; return;
    }
  } */

  for (int i = in.size() - 2; i >= 0; --i)
  {
    /* 3 8 5 6
           i i+1
    */
    while (in[i] >= in[i + 1])
    {
      // Выполняем единственно-разрешенную операцию, так как она должна быть строго возрастающей
      in[i] /= 2;
      count++;
    }
    // Делить на 0 нельзя && таких входных данных быть не должно
    if (in[i] == 0 && i != 0)
    {
      return -1;
    }
  }
  return count;
}

int main()
{
  // считываем ввод пользователя
  int t;
  cin >> t;
START:
  while (t--)
  {
    int n;
    cin >> n;
    vector<int> v(n);

    for (int i = 0; i < n; i++)
    {
      cin >> v[i];
    }

    int ops = 0;
    for (int i = n - 1; i > 0; i--)
    {
      while (v[i - 1] >= v[i])
      {
        if (!v[i - 1])
        {
          cout << -1 << endl;
          goto START;
        }
        v[i - 1] >>= 1;
        // Побитовый сдвиг вправо : 
        ops++;
      }
    }
    cout << ops << endl;
  }

  /* int N = 0, n = 0, tmpin = 0;
  cin >> n;
  if (n > pow(10, 4)) {
    cout << "-1" << endl; return -1 ;
  }

  vector< vector<int> > in(N);
  vector<int> out(N);

  for (int i = 0; i < N; ++i) {
    cin >> n;
    if (n > 30) {
      out[i] = -1; continue;
    }
    for (int j = 0; j < n; ++j) {
      cin >> tmpin;
      in[i].push_back(tmpin);
    }
    out[i] = solve(in[i]);

  } */

  return 0;
}