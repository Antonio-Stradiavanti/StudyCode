from itertools import product
# Вектор результата булевой ф-ции 3х переменных от всех наборов, вводить надо через пробел.
#rezfunc=[1, 0, 1, 0, 1, 0, 1, 1]
# mas -> массив где хранятся переменные булевой ф-ции, s->введенная пользователем строка с переменными
# Проверяй на соответствие размер rezfunc и количество переменных
#s = "x y z" ; mas=[] 
'''
for c in s:
    if(ord(c) in range(ord("a"),ord("z")+1)or ord(c) in range(ord("A"),ord("Z")+1)):
        if c not in mas:
            mas.append(c)
print(mas)
exit()
'''
# Формирует таблицу истинности, ставит в соответствие набору переменных, количество которых определяется в mas значение ф-ции из массива rezfunc
def maketable(rezfunc,table,mas):
    # Получим 8 или 4 пустых списка, в которые будем добавлять набор переменных и соответствующее этому набору значение ф-ции.
    table=[[] for i in range(len(rezfunc))]
    a = []
    for i in range(len(mas)):
        a.append("0")
    print(a)
    # i от 0 до 4 или 8
    for i in range(len(rezfunc)):
        for j in range(len(a)):
            table[i].append(int(a[j]))
        # 0 может быть только на первой итерации
        dob=1
        # идем от 1 или 2 до 0
        for j in reversed(range(len(a))):
            if a[j]=='0' and dob==1:
                a[j]='1'
                break
            else:
                a[j]='0' 
        table[i].append(rezfunc[i])
    return table # Выходные данные -> таблица истинности лдя ф-ции 2х или 3х переменных
# В python все зависит от отступов.
#print(mas)
#table = [] ; table = maketable(rezfunc, table, mas)
#print(table)
# Входные данные в ф-цию karnaugh -> таблица истинности в виде матрицы
def karnaugh(table):
    # Для 2х переменных
    if len(table)==4:
        karnotable=[]
        # Формирую карту Картно Добавляю в 0 элемент массива kanrotable половину значений ф-ции от всякого набора переменных в 1й - другую половину  
        karnotable.append([table[i][-1] for i in range(int(len(table)/2))])
        karnotable.append([table[i][-1] for i in range(int(len(table)/2),len(table))])
        # Вывожу первую строку карты
        print("x\y| 0 | 1 |")
        for i in range(len(karnotable)):
            print(" ",i," ",sep="",end="|")
            for j in karnotable[i]:
                print(" ",j," ",sep="",end="|")
            print()
        DNF2(karnotable)
        pass
    # Для 3х переменных
    else:
        # формируем карту Карно.
        karnotable=[]
        # для первой половины значений x -> 0, для второй -> 1
        karnotable.append([table[i][-1] for i in range(int(len(table)/2))])
        # Обмен 2го и 3го элемента значениями, для соответствия коду Грея
        karnotable[0][2],karnotable[0][3]=karnotable[0][3],karnotable[0][2]
        # Добавляю вторую половину значений ф-ции
        karnotable.append([table[i][-1] for i in range(int(len(table)/2),len(table))])
        # Обмен 2го и 3го элемента значениями, для соответствия коду Грея
        karnotable[1][2],karnotable[1][3]=karnotable[1][3],karnotable[1][2]
        # Вывод карты карно 3х перменных
        print("x\yz|0 0|0 1|1 1|1 0|")
        for i in range(len(karnotable)):
            # Чтобы было ровно посередине.
            print("  ",i," ",sep="",end="|")
            for j in karnotable[i]:
                print(" ",j," ",sep="",end="|")
            print()
        print(karnotable)
        DNF(karnotable)
# Что возвращает -> формирует карту Карно и передает ее ф-циям на минимизацию. 
#karnaugh(table)
# Для 3х переменных
# Пример входных данных : правильная конфигурация, состоящая из индексов в соответсвующем карте карно массиве координат coord [[0,0], [0,1], [0,2],[0,3]]
# Ставит в соответствие индексам элементов в правильной конфигурации, набор переменных
def perem(coordmas):
    coords=[]
    for i in coordmas:
        if i[0]==0:
            if i[1]==0:
                coords.append([0,0,0])
            elif i[1]==1:
                coords.append([0,0,1])
            elif i[1]==2:
                coords.append([0,1,1])
            elif i[1]==3:
                coords.append([0,1,0])
        else:
            if i[1]==0:
                coords.append([1,0,0])
            elif i[1]==1:
                coords.append([1,0,1])
            elif i[1]==2:
                coords.append([1,1,1])
            elif i[1]==3:
                coords.append([1,1,0])
    x,y,z=coords[0]
    #?
    for i in range(1,len(coords)):
        if x!=coords[i][0] and x!=-1:
            x=-1
        if y!=coords[i][1] and y!=-1:
            y=-1
        if z!=coords[i][2] and z!=-1:
            z=-1
    return[x,y,z]
#print(perem([[0, 1], [0, 2]]))
# Тоже самое только Для 2х переменных

def perem2(coordmas):
    coords=[]
    for i in coordmas:
        if i[0]==0:
            if i[1]==0:
                coords.append([0,0])
            elif i[1]==1:
                coords.append([0,1])
        else:
            if i[1]==0:
                coords.append([1,0])
            elif i[1]==1:
                coords.append([1,1])
    x,y=coords[0]
    for i in range(1,len(coords)):
        if x!=coords[i][0] and x!=-1:
            x=-1
        if y!=coords[i][1] and y!=-1:
            y=-1
    return[x,y]

def DNF2(karnotable):
    used=[]
    coord=[]
    for i in range(len(karnotable)):
        for j in range(len(karnotable[i])):
            coord.append([i,j])
    check=1
    dnf=""
    knf=""
    while(check):
        check=0
        for count,i in enumerate(coord):
            coordmas=[]
            if i not in used:
                if karnotable[i[0]][(i[1]+1)%2]==karnotable[i[0]][i[1]]  and karnotable[(i[0]+1)%2][(i[1]+1)%2]==karnotable[i[0]][i[1]]  and karnotable[(i[0]+1)%2][i[1]]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([i[0],(i[1]+1)%2])
                    used.append([(i[0]+1)%2,(i[1]+1)%2])
                    used.append([(i[0]+1)%2,i[1]])
                    coordmas.append(i)
                    coordmas.append([i[0],(i[1]+1)%2])
                    coordmas.append([(i[0]+1)%2,(i[1]+1)%2])
                    coordmas.append([(i[0]+1)%2,i[1]])
                    if karnotable[i[0]][i[1]]:
                        dnf="1"
                        knf="1"
                    else:
                        dnf="0"
                        knf="0"
                    pass
                elif karnotable[i[0]][(i[1]+1)%2]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([i[0],(i[1]+1)%2])
                    coordmas.append(i)
                    coordmas.append([i[0],(i[1]+1)%2])
                    x,y=perem2(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="!x"
                            else:
                                dnf+="x"
                            if y!=-1:
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="!y"
                            else:
                                dnf+="y"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="!x"
                            else:
                                knf+="x"
                            if y!=-1:
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="!y"
                            else:
                                knf+="y"
                        knf+=")∧"
                    pass
                elif karnotable[(i[0]+1)%2][i[1]]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([(i[0]+1)%2,i[1]])
                    coordmas.append(i)
                    coordmas.append([(i[0]+1)%2,i[1]])
                    x,y=perem2(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="!x"
                            else:
                                dnf+="x"
                            if y!=-1:
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="!y"
                            else:
                                dnf+="y"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="!x"
                            else:
                                knf+="x"
                            if y!=-1:
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="!y"
                            else:
                                knf+="y"
                        knf+=")∧"
                    pass
                else:
                    used.append(i)
                    coordmas.append(i)
                    x,y=perem2(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="!x"
                            else:
                                dnf+="x"
                            if y!=-1:
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="!y"
                            else:
                                dnf+="y"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="!x"
                            else:
                                knf+="x"
                            if y!=-1:
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="!y"
                            else:
                                knf+="y"
                        knf+=")∧"
                    pass
    newdnf=""
    for i in range(len(dnf)-1):
        newdnf+=dnf[i]
    newknf=""
    for i in range(len(knf)-1):
        newknf+=knf[i]
    print("ДНФ:", newdnf)
    print("КНФ:", newknf)
    pass

# Для 3х переменных
# - перед переменной означает отрицание
def DNF(karnotable):
    # Маркируем использованные ячейки
    used=[]
    coord=[]
    # Получаю массив координат
    # [[0,0], [0,1], [0,2], [0,3], [1,0], [1,1], [1,2], [1,3]]
    for i in range(len(karnotable)):
        for j in range(len(karnotable[i])):
            coord.append([i,j])
    #print(coord)
    check=1
    # Это строки их нужно сформировать
    dnf=""
    knf=""
    while(check):
        # Условие выхода из цикла
        check=0
        # enumerate -> ставит в соответствие индексу значение, таким образом перебираем сформированный массив от и до
        for _,i in enumerate(coord):
            # текущая правильная конфигурация
            coordmas=[]
            if i not in used:
                check=1
                # Проверка на возможность сформировать правильную конфигурацию высотой 1 и шириной 4
                if karnotable[i[0]][(i[1]+1)%4]==karnotable[i[0]][i[1]] and karnotable[i[0]][(i[1]+2)%4]==karnotable[i[0]][i[1]] and karnotable[i[0]][(i[1]+3)%4]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([i[0],(i[1]+1)%4])
                    used.append([i[0],(i[1]+2)%4])
                    used.append([i[0],(i[1]+3)%4])
                    coordmas.append(i)
                    coordmas.append([i[0],(i[1]+1)%4])
                    coordmas.append([i[0],(i[1]+2)%4])
                    coordmas.append([i[0],(i[1]+3)%4])
                    # ?
                    x,y,z=perem(coordmas)
                    #[0, -1, -1]
                    # Рассматриваю случаи в правильной конфигурации 0 или когда в правильной конфигурации 1, добавляю упрощенную эл. конъюнкцию/дизъюнкцию в днф или кнф соответственно 
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="!x"
                            else:
                                dnf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="!y"
                            else:
                                dnf+="y"
                            if y!=-1 and z!=-1:
                                dnf+="∧"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                dnf+="!z"
                            else:
                                dnf+="z"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="!x"
                            else:
                                knf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="!y"
                            else:
                                knf+="y"
                            if y!=-1 and z!=-1:
                                knf+="∨"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                knf+="!z"
                            else:
                                knf+="z"
                        knf+=")∧"
                    pass
                elif karnotable[i[0]-1][i[1]-1]==karnotable[i[0]][i[1]] and karnotable[i[0]-1][i[1]]==karnotable[i[0]][i[1]] and karnotable[i[0]][i[1]-1]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([(i[0]+1)%2,(i[1]+3)%4])
                    used.append([(i[0]+1)%2,(i[1])%4])
                    used.append([(i[0])%2,(i[1]+3)%4])
                    coordmas.append(i)
                    coordmas.append([(i[0]+1)%2,(i[1]+3)%4])
                    coordmas.append([(i[0]+1)%2,(i[1])%4])
                    coordmas.append([(i[0])%2,(i[1]+3)%4])
                    x,y,z=perem(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="!x"
                            else:
                                dnf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="!y"
                            else:
                                dnf+="y"
                            if y!=-1 and z!=-1:
                                dnf+="∧"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                dnf+="!z"
                            else:
                                dnf+="z"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="!x"
                            else:
                                knf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="!y"
                            else:
                                knf+="y"
                            if y!=-1 and z!=-1:
                                knf+="∨"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                knf+="!z"
                            else:
                                knf+="z"
                        knf+=")∧"
                    pass
                elif karnotable[i[0]-1][(i[1]+1)%4]==karnotable[i[0]][i[1]] and karnotable[i[0]-1][i[1]]==karnotable[i[0]][i[1]] and karnotable[i[0]][(i[1]+1)%4]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([(i[0]+1)%2,(i[1]+1)%4])
                    used.append([(i[0]+1)%2,(i[1])%4])
                    used.append([(i[0])%2,(i[1]+1)%4])
                    coordmas.append(i)
                    coordmas.append([(i[0]+1)%2,(i[1]+1)%4])
                    coordmas.append([(i[0]+1)%2,(i[1])%4])
                    coordmas.append([(i[0])%2,(i[1]+1)%4])
                    x,y,z=perem(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="!x"
                            else:
                                dnf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="!y"
                            else:
                                dnf+="y"
                            if y!=-1 and z!=-1:
                                dnf+="∧"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                dnf+="!z"
                            else:
                                dnf+="z"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="!x"
                            else:
                                knf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="!y"
                            else:
                                knf+="y"
                            if y!=-1 and z!=-1:
                                knf+="∨"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                knf+="!z"
                            else:
                                knf+="z"
                        knf+=")∧"
                    pass
                elif karnotable[(i[0]+1)%2][i[1]-1]==karnotable[i[0]][i[1]] and karnotable[i[0]][i[1]-1]==karnotable[i[0]][i[1]] and karnotable[(i[0]+1)%2][i[1]]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([(i[0]+1)%2,(i[1]+3)%4])
                    used.append([(i[0])%2,(i[1]+3)%4])
                    used.append([(i[0]+1)%2,(i[1])%4])
                    coordmas.append(i)
                    coordmas.append([(i[0]+1)%2,(i[1]+3)%4])
                    coordmas.append([(i[0])%2,(i[1]+3)%4])
                    coordmas.append([(i[0]+1)%2,(i[1])%4])
                    x,y,z=perem(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="!x"
                            else:
                                dnf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="!y"
                            else:
                                dnf+="y"
                            if y!=-1 and z!=-1:
                                dnf+="∧"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                dnf+="!z"
                            else:
                                dnf+="z"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="!x"
                            else:
                                knf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="!y"
                            else:
                                knf+="y"
                            if y!=-1 and z!=-1:
                                knf+="∨"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                knf+="!z"
                            else:
                                knf+="z"
                        knf+=")∧"
                    pass
                elif karnotable[i[0]][i[1]-1]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([(i[0])%2,(i[1]+3)%4])
                    coordmas.append(i)
                    coordmas.append([(i[0])%2,(i[1]+3)%4])
                    x,y,z=perem(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="!x"
                            else:
                                dnf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="!y"
                            else:
                                dnf+="y"
                            if y!=-1 and z!=-1:
                                dnf+="∧"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                dnf+="!z"
                            else:
                                dnf+="z"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="!x"
                            else:
                                knf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="!y"
                            else:
                                knf+="y"
                            if y!=-1 and z!=-1:
                                knf+="∨"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                knf+="!z"
                            else:
                                knf+="z"
                        knf+=")∧"
                    pass
                elif karnotable[i[0]][(i[1]+1)%4]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([(i[0])%2,(i[1]+1)%4])
                    coordmas.append(i)
                    coordmas.append([(i[0])%2,(i[1]+1)%4])
                    x,y,z=perem(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="!x"
                            else:
                                dnf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="!y"
                            else:
                                dnf+="y"
                            if y!=-1 and z!=-1:
                                dnf+="∧"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                dnf+="!z"
                            else:
                                dnf+="z"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="!x"
                            else:
                                knf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="!y"
                            else:
                                knf+="y"
                            if y!=-1 and z!=-1:
                                knf+="∨"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                knf+="!z"
                            else:
                                knf+="z"
                        knf+=")∧"
                    pass
                elif karnotable[(i[0]+1)%2][i[1]]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([(i[0]+1)%2,(i[1])%4])
                    coordmas.append(i)
                    coordmas.append([(i[0]+1)%2,(i[1])%4])
                    x,y,z=perem(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="!x"
                            else:
                                dnf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="!y"
                            else:
                                dnf+="y"
                            if y!=-1 and z!=-1:
                                dnf+="∧"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                dnf+="!z"
                            else:
                                dnf+="z"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="!x"
                            else:
                                knf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="!y"
                            else:
                                knf+="y"
                            if y!=-1 and z!=-1:
                                knf+="∨"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                knf+="!z"
                            else:
                                knf+="z"
                        knf+=")∧"
                    pass
                elif karnotable[i[0]-1][i[1]]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([(i[0]+1)%2,(i[1])%4])
                    coordmas.append(i)
                    coordmas.append([(i[0]+1)%2,(i[1])%4])
                    x,y,z=perem(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="!x"
                            else:
                                dnf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="!y"
                            else:
                                dnf+="y"
                            if y!=-1 and z!=-1:
                                dnf+="∧"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                dnf+="!z"
                            else:
                                dnf+="z"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="!x"
                            else:
                                knf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="!y"
                            else:
                                knf+="y"
                            if y!=-1 and z!=-1:
                                knf+="∨"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                knf+="!z"
                            else:
                                knf+="z"
                        knf+=")∧"
                    pass
                else:
                    used.append(i)
                    coordmas.append(i)
                    x,y,z=perem(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="!x"
                            else:
                                dnf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="!y"
                            else:
                                dnf+="y"
                            if y!=-1 and z!=-1:
                                dnf+="∧"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                dnf+="!z"
                            else:
                                dnf+="z"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="!x"
                            else:
                                knf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="!y"
                            else:
                                knf+="y"
                            if y!=-1 and z!=-1:
                                knf+="∨"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                knf+="!z"
                            else:
                                knf+="z"
                        knf+=")∧"
                    pass
    newdnf=""
    for i in range(len(dnf)-1):
        newdnf+=dnf[i]
    newknf=""
    for i in range(len(knf)-1):
        newknf+=knf[i]
    print("ДНФ:", newdnf)
    print("КНФ:", newknf)

# Блок main()
rezfunc = []; mas = []; table = []
f2 = [[] for i in range(3)] ; f3 = [[] for i in range(3)] 

for x, y in product((0, 1), (0,1)):
    f2[0].append(x ^ (not(y) or x))
    f2[1].append(1 * ((x is not(y)) ^ (not(not(x) and y))))
    f2[2].append(1 * (not(not(x) or (y and x)) ^ (not(not(y) and x))))
    
for x, y, z in product((0,1), (0,1), (0,1)):
    f3[0].append(1 * (not(x) or (y is z)))
    f3[1].append(1 * ((not(x and (z or y))) or z))
    f3[2].append(1 * ((not(x) or y) ^ (not(z or ( not(z) and not(x))))))
c = 0; c1 = 0
print(f"{f2}\n\n{f3}\n")
while(1):
    print("--- Меню ---\n0 -> Выход из программы\n1 -> Минимизация булевых ф-ций 2х переменных\n2 -> Минимизация булевых ф-ций 3х переменных\n---")
    c = int(input("> "))
    if c == 0:
        print("[случай 0] : Завершение работы\n---\n")
        break;
    elif c == 1:
        mas = ['x', 'y']
        print("[случай 1] : Минимизация ф-ций 2х переменных по методу Мориса Карно.\n[NOTE] : [!] Означает логическую операцию отрицание.\n---\nВыберите ф-цию:\n\t1 -> x ⊕ (y → x)\n\t2 -> (x ∼ (not y)) ⊕ ((not x) | y)\n\t3 -> ((not x) ↓ (y and x)) ⊕ ((not y) | x)\n\t---")
        c1 = int(input("> "))
        if c1 == 1:
            table = [] ; rezfunc = f2[0]
            table = maketable(rezfunc, table, mas)
            karnaugh(table)
        elif c1 == 2:
            table = [] ; rezfunc = f2[1]
            table = maketable(rezfunc, table, mas)
            karnaugh(table)
        elif c1 == 3:
            table = [] ; rezfunc = f2[2]
            table = maketable(rezfunc, table, mas)
            karnaugh(table)
        else:
            print("[случай 1 -> выбор ф-ции] : Нет такой ф-ции.\n")
    elif c == 2:
        mas = ['x', 'y', 'z']
        print("[случай 2] : Минимизация ф-ций 3х переменныхпо методу Мориса Карно.\n[NOTE] : [!] Означает логическую операцию отрицание.\n---\nВыберите ф-цию:\n\t1 -> (x → (y ∼ z))\n\t2 -> (x | ((not z) → y)) or z\n\t3 -> (x → y) ⊕ (z ↓ ((not z) and (not x)))\n\t---")
        c1 = int(input("> "))
        if c1 == 1:
            table = [] ; rezfunc = f3[0]
            table = maketable(rezfunc, table, mas)
            karnaugh(table)
        elif c1 == 2:
            table = [] ; rezfunc = f3[1]
            table = maketable(rezfunc, table, mas)
            karnaugh(table)
        elif c1 == 3:
            table = [] ; rezfunc = f3[2]
            table = maketable(rezfunc, table, mas)
            karnaugh(table)
        else:
            print("[случай 2 -> выбор ф-ции] : Нет такой ф-ции.\n")
    else: print("[По-умолчанию] : Нет такой команды\n---\n")
