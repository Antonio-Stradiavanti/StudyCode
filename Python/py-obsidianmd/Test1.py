from itertools import product

def sumMod2(x, y):
    return 1 if x != y else 0
#-----
def implication(x, y):
    return 0 if x == 1 and y == 0 else 1
#---
def equal(x, y):
    return 1 if x == y else 0
#---
def PierHand(x, y):
    return 1 if x == 0 and y == 0 else 0
#---
def ShaeffersTouch(x, y):
    return 0 if x == 1 and y == 1 else 1
#--- 
n = 8
vn = 3

comb = []
vals = []
valsPascal = [[] for i in range(n)]
keys = []

standard3n = "a0 ⊕  a1⋀x ⊕  a2⋀y ⊕  a3⋀z ⊕  a12⋀x⋀y ⊕  a13⋀x⋀z ⊕  a23⋀y⋀z ⊕  a123⋀x⋀y⋀z"
print("Выведем полином в общем виде для 3х переменных", standard3n, sep='\n', end='\n') 

ops2 = [" ⊕ ", " ⋀ "]
# Доработать, привести к общему виду
vars = [["", "x"], ["", "y"], ["", "z"]]

def boolFunc1(x, y):
    return sumMod2(equal(i, (not j)), ShaeffersTouch((not i), j))

# Каждому значению ф-ции поставим в соответствие коэффициент
for (i, j, k) in product((0, 1), repeat=3):
    comb.append([i, j, k])
    keys.append(f'a{i}{j}{k}')
    vals.append(boolFunc1(i, j))

# Над соседними элементами вектора значений vals выполняется операция сумма по модулю 2

# Заведем список: треугольник Паскаля, добавим в его нулевой элемент вектор значений
ls = n
sizes = [0 for i in range(n)]
for i in range(n):    
    sizes[i] = ls
    ls-=1
# Порядок, Треугольник Паскаля инициализирован
PascalTriangle = [[0 for i in range(sizes[j])] for j in range(n)]
print(PascalTriangle)
PascalTriangle.insert(0, vals)
print(PascalTriangle)
# Выполним операцию: сумма по модулю 2 над каждым из соседних элементов вектора треугольника на уровень выше, результат запишем в вектор на текущем уровне, с каждой итерацией размер вектора уменьшается на 1, пока не дойдет до 1 
# размер каждого из векторов треугольника паскаля 
for i in range(1, n):
    for j in range(sizes[i-1]):
        if (j != sizes[i]):
            PascalTriangle[i][j] = sumMod2(PascalTriangle[i-1][j], PascalTriangle[i-1][j+1])
# перебираю старый вектор, результат зарписываю в новый
print("Получим треугольник Паскаля:", PascalTriangle, sep='\n', end='\n')
# Сформируем словарь коэффициентов i коэффциенту поставим в соответствие нулевой элемент i го вектора треугольника Паскаля
for i in range(n):
    valsPascal[i].append(PascalTriangle[i][0])
    valsPascal[i].append(comb[i]) 
print("Нулевые элементы каждого из векторов треугольника Паскаля:", valsPascal, sep='\n', end='\n')
dict1 = dict(zip(keys, valsPascal))
print("Значения каждого из коэффициентов:", dict1, sep='\n', end='\n')
# Если значение коэффициента != 0, он учавствует в конъюнкции с переменными, значение которых == 1 в том наборе, которому он сопоставлен 
conjunctions = ["" for i in range(n)]
for i in range(n):
    if dict1[keys[i]][0]:
        conjunctions[i] = keys[i]
        for j in range(vn):
            conjunctions[i] += " " + vars[j][dict1[keys[i]][1][j]]
conjunctions = [i for i in conjunctions if len(i) != 0]
conjunctions = [i.split(" ") for i in conjunctions if len(i) != 0]
# Из полученных списков исключить пустые элементы, добавить символ ⋀ к каждой паре
# Добавить к полученным конъюнкциям символ ⊕
# Оптимизировать процесс, включить мозг, выспаться. 
print("Конъюнкции полинома:", conjunctions, sep='\n', end='\n')
        