import calc
import SDNF
import algebra
import systemboolfunc
import karno
def inp():
    print("Введите уравнение")
    # func -> хранит булеву ф-цию
    func=input()
    res={}
    n=1
    #Удаление лишних пробелов
    func=func.replace(" ","")
    # Словарь
    d={}
    mas=[]
    #Запись переменных
    for c in func:
        if(ord(c) in range(ord("a"),ord("z")+1)or ord(c) in range(ord("A"),ord("Z")+1)):
            d[c]=0
            if c not in mas:
                mas.append(c)
    mas.sort()
    t,res,t=calc.rez(func,res,n)
    rezfunc=[]
    rezfunc=calc.otvet(mas,res.copy(),0,rezfunc)
    # Возвращает несколько объектов из ф-ции, в таком случае в левой части операции присваивание будет кортеж
    return rezfunc,mas
if __name__=="__main__":
    print("""Выберите номер команды:
    1-Получить таблицу истинности
    2-Получить СКНФ СДНФ
    3-Получить Полигоном Жегалкина
    4-Система булевых функций
    5-Минимизация булевых функций""")
    comnum=0
    vvod=0
    while True:
        comnum=int(input())
        if comnum==1:
            print("- отрицание \n* и \n| штрих Шеффера \n! Стрелка пирса \n+ или \n> импликация \n~ эквивалентность \n% сумма по mod 2")
            print("Введите уравнение")
            func=input()
            calc.functofunc(func)
        elif comnum==2:
            print("Ввод уравнения? Y/N")
            vvod=input()
            if vvod=="Y" or vvod=="y":
                vvod=1
            else:
                vvod=0
            if vvod:
                rezfunc,mas=inp()
            else:
                print("Введите переменные")
                s=input()
                mas=[]
                for c in s:
                    if(ord(c) in range(ord("a"),ord("z")+1)or ord(c) in range(ord("A"),ord("Z")+1)):
                        if c not in mas:
                            mas.append(c)
                print("Введите результат функции")
                rezfunc=[]
                rezfunc=list(map(int,input().split()))
            table=[]
            table=algebra.maketable(rezfunc,table,mas)
            print("Выполнять проверку? Y/N")
            check=input()
            if check=="Y" or check=="y":
                check=1
            else:
                check=0
            SDNF.SDNF(table,mas,check)
            SDNF.SKNF(table,mas,check)
        elif comnum==3:
            print("Ввод уравнения? Y/N")
            vvod=input()
            if vvod=="Y" or vvod=="y":
                vvod=1
            else:
                vvod=0
            if vvod:
                rezfunc,mas=inp()
            else:
                print("Введите переменные")
                s=input()
                mas=[]
                for c in s:
                    if(ord(c) in range(ord("a"),ord("z")+1)or ord(c) in range(ord("A"),ord("Z")+1)):
                        if c not in mas:
                            mas.append(c)
                print("Введите полученные значения функции")
                rezfunc=[*map(int,input().split())]
            table=[]
            table=algebra.maketable(rezfunc,table,mas)
            urav=algebra.algebra(rezfunc,mas,table)
            print("Полигоном Жегалкина: ",urav)
        elif comnum==4:
            kol=1
            print("Введите количество функций")
            kol=int(input())
            print("Ввод уравнения? Y/N")
            vvod=input()
            if vvod=="Y" or vvod=="y":
                vvod=1
            else:
                vvod=0
            reztable=[]
            for kolkol in range(kol):
                
                if vvod:
                    rezfunc,mas=inp()
                else:
                    print("Введите переменные")
                    s=input()
                    mas=[]
                    for c in s:
                        if(ord(c) in range(ord("a"),ord("z")+1)or ord(c) in range(ord("A"),ord("Z")+1)):
                            if c not in mas:
                                mas.append(c)
                    print("Введите полученные значения функции")
                    rezfunc=[*map(int,input().split())]
                table=[]
                table=algebra.maketable(rezfunc,table,mas)
                urav=algebra.algebra(rezfunc,mas,table)
                rez=systemboolfunc.rezclass(table,urav)
                reztable.append(rez)
            print("Fun|T0 |T1 |S  |M  |L")
            temptable=reztable
            for kolkol in range(kol):
                for i in range(len(temptable[kolkol])):
                    if temptable[kolkol][i]==0:
                        temptable[kolkol][i]="-"
                    else:
                        temptable[kolkol][i]="+"
                print(kolkol,*temptable[kolkol],sep="  |")
            check=1
            for ii in range(5):
                if reztable[0][ii] and reztable[1][ii] and reztable[2][ii]:
                    check=0
                    break
            if check:
                print("Система булевых функций полная")
            else:
                print("Система булевых функций не полная")
        elif comnum==5:
            print("Ввод уравнения? Y/N")
            vvod=input()
            if vvod=="Y" or vvod=="y":
                vvod=1
            else:
                vvod=0
            if vvod:
                rezfunc,mas=inp()
            else:
                print("Введите переменные")
                s=input()
                # Просто пустой динамический массив
                mas=[]
                for c in s:
                    if(ord(c) in range(ord("a"),ord("z")+1)or ord(c) in range(ord("A"),ord("Z")+1)):
                        if c not in mas:
                            mas.append(c)
                print("Введите результат функции")
                # Вектор результата булевой ф-ции 3х переменных от всех наборов, вводить надо через пробел.
                rezfunc=[]
                # Формирует динамический массив, из введенной пользователем строки, преобразуя каждый отдельный символ, отделенный пробелом от другого в целое число.
                rezfunc=list(map(int,input().split()))
            table=[]
            # Входная таблица формируется особой ф-цией.
            # Выходные данные список списков?
            table=algebra.maketable(rezfunc,table,mas)
            karno.karno(table)