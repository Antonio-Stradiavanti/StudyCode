#include<set>
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    setlocale(LC_ALL, "ru");
    
    string t = "abcdefg"; // Получим объект (объекты имеют связанные с ними ф-ции) типа string, инициализированный С-строкой.
    

    return 0;
}

/*
deque<int> MergeDeq(deque<int> d1, deque<int> d2)
{
     int choice = 0;
    //sort(d1.begin(), d1.end());
    //sort(d2.begin(), d2.end());

    deque<int> d3;
    cout << "Вставить в начало или в конец?" << endl;
    cin >> choice;
    auto ib1(d1.begin()), ie1(d1.end()), ib2(d2.begin()), ie2(d2.end());
    switch (choice)
    {
    case 1:
        while (ib1 != ie1 && ib2 != ie2)
        {
            if (*ib1 <= *ib2)
            {
                d3.push_back(*ib1);
                ++ib1;
            }
            else
            {
                d3.push_back(*ib2);
                ++ib2;
            }
        }

        d3.insert(d3.end(), ib1, ie1);
        d3.insert(d3.end(), ib2, ie2);

        for (auto& val : d3)
        {
            cout << val << "  ";
        }
        break;
    case 2:
        while (ib1 != ie1 && ib2 != ie2)
        {
            if (*ib1 <= *ib2)
            {
                d3.push_front(*ib1);
                ++ib1;
            }
            else
            {
                d3.push_front(*ib2);
                ++ib2;
            }
        }

        d3.insert(d3.begin(), ib1, ie1);
        d3.insert(d3.begin(), ib2, ie2);

        for (auto& val : d3)
        {
            cout << val << "  ";
        }
        break;
    }
    return d3;
    
}
*/
