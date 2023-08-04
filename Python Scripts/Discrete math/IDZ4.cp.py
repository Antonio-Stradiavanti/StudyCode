from itertools import product
# Добавить векторы значений ф-ций от наборов переменных
f2 = [[] for i in range(3)] ; f3 = [[] for i in range(3)] 
a = [] # Вектор значений некоторой ф-ции

for x, y in product((0, 1), (0,1)):
    f2[0].append(x ^ (not(y) or x))
    f2[1].append(1 * ((x is not(y)) ^ (not(not(x) and y))))
    f2[2].append(1 * (not(not(x) or (y and x)) ^ (not(not(y) and x))))
    
for x, y, z in product((0,1), (0,1), (0,1)):
    f3[0].append(1 * (not(x) or (y is z)))
    f3[1].append(1 * ((not(x and (z or y))) or z))
    f3[2].append(1 * ((not(x) or y) ^ (not(z or ( not(z) and not(x))))))

print(*f2) ; print(*f3)

# Полиномы Жегалкина:
def pars_2(a):
    p = ['a0', 'a2', 'a1', 'a12']
    d_1 = {'a0': '1', 'a2': 'y', 'a1': 'x', 'a12': '(x&y)'}
    d = dict()
    b = ''
    length = len(a)
    index = [0]
    index[0] = a[0]
    for i in range(len(a) - 1):
        result = []
        for j in range(len(a) - 1):
            result.append(a[j] ^ a[j + 1])
        if result:
            index.append(result[0])
        a = result
    for i in range(length):
        d[p[i]] = index[i]
    for i in d.keys():
        if d.get(i) == 1:
            b += d_1.get(i) + '^'
    b = b[:-1]
    # Доп проверка на соответствие классу линейных ф-ций
    if '&' in b:
        return False
    else:
        return True
def pars_3(a):
    p = ['a0', 'a3', 'a2', 'a23', 'a1', 'a13', 'a12', 'a123']
    d_1 = {'a0': '1', 'a3': 'z', 'a2': 'y', 'a23': '(y&z)', 'a1': 'x', 'a13': '(x&z)', 'a12': '(x&y)',
           'a123': '(x&y&z)'}
    d = dict()
    b = ''
    length = len(a)
    index = [0]
    index[0] = a[0]
    for i in range(len(a) - 1):
        result = []
        for j in range(len(a) - 1):
            result.append(a[j] ^ a[j + 1])
        if result:
            index.append(result[0])
        a = result
    for i in range(length):
        d[p[i]] = index[i]
    for i in d.keys():
        if d.get(i) == 1:
            b += d_1.get(i) + '^'
    b = b[:-1]
    if '&' in b:
        return False
    else:
        return True
# Классы ф-ций
accessory_list = [] # accessory - приложение. Глобальная переменная
boolFuncClasses = ['T0(a)', 'T1(a)', 'L(a)', 'M(a)', 'S(a)']
def T0(a):
    if a[0] == 0:
        accessory_list.append('+')
    else:
        accessory_list.append('-')
def T1(a):
    if a[-1] == 1:
        accessory_list.append('+')
    else:
        accessory_list.append('-')
def S(a):
    # Инвертируются значения ф-ции и изменяется порядок следования элементов списка
    reversed_list = [int(not i) for i in a][::-1]
    if a == reversed_list:
        accessory_list.append('+')
    else:
        accessory_list.append('-')
def L(a):
    # Ф-ция принадлежит этому классу если многочлен Жегалкина задан в виде: P(x_1, ... , x_n) = 1 ^ x_1 ^ x_2 ^ ... ^ x_n
    if len(a) == 4:
        if pars_2(a):
            accessory_list.append('+')
        else:
            accessory_list.append('-')
    else:
        if pars_3(a):
            accessory_list.append('+')
        else:
            accessory_list.append('-')
def M(a):
    # Если для всех наборов переменных выполняется условие предшествования, то ф-ция является монотонной
    b = (0,1)
    f2 = [str(i)+str(j) for i in b for j in b]
    f3 = [str(i)+str(j)+str(z) for i in b for j in b for z in b]
    # f2, f3 -> векторы всевозможных наборов переменных, представленных в виде строк
    flag = True
    if len(a) == 4:
        # ф-ция 2х переменных
        for i in range(4):
            for j in range(i + 1, 4):
                # Условие предшествования должно выполняться для каждого элемента набора переменных
                if f2[i][0] <= f2[j][0] and f2[i][-1] <= f2[j][-1]:
                    # Если выполняется условие предшествования для набора переменных, смотрю выполнение условия предшествования для значений ф-ции на этом наборе.
                    if a[i] <= a[j]:
                        # Перехожу на следующую итерацию цикла
                        continue
                    else:
                        # Если хотя бы для одного набора условие предшествования не выполняется, то ф-ция не является монотонной
                        flag = False
                        break
    else:
        # ф-ция 3х перменных
        for i in range(8):
            for j in range(i + 1, 8):
                if f3[i][0] <= f3[j][0] and f3[i][1] <= f3[j][1] and f3[i][-1] <= f3[j][-1]:
                    if a[i] <= a[j]:
                        continue
                    else:
                        flag = False
                        break
    if flag:
        accessory_list.append('+')
    else:
        accessory_list.append('-')
# Главная часть программы
final = [[], [], []]
systems = ['f2', 'f3']
switch = int(input('Выберите систему функций:\n1 - система ф-ций из 2-х переменных\n2 - система ф-ций из 3-х переменных\n'))
if switch == 1 or switch == 2:
    print('  T0|T1|L|M|S')
    # k - переменная цикла
    for k in range(3):
        accessory_list.clear()
        # f2, f3 -> системы из 3х ф-ций, выбираю векторы значений 0, 1 или 2 ф-ции из 1й или 2й системы.
        a = eval(systems[switch - 1])[k]
        for i in range(5):
            # Последовательно проверяю каждую ф-цию на принадлежность каждому из классов, использование eval позволяет снизить количество использованных условных операторов.
            eval(boolFuncClasses[i])
        # Добавляю целый столбец в таблицу для 1, 2, 3 ф-ций
        final[k].extend(accessory_list)
        # Нумерация ф-ций в таблице
        if switch == 1:
            print('f' + str(k + 1), *accessory_list)
        else:
            print('f' + str(k + 4), *accessory_list)
    count = 0
    # Если в каждом столбце таблицы есть хотябы один -, то система полная
    for k in range(5):
        if final[0][k] == '-' or final[1][k] == '-' or final[2][k] == '-':
            count += 1
            continue
    print(f'Теорема Поста: Система называется полной <=> в каждом столбце таблицы есть хотя бы один минус\nКоличество столбцов в которых есть хотя бы один минус: {count}')
    if count == 5:
        print('=> Система полная')
    else:
        print('=> Система не полная')
else:
    print("Выбран некоректный номер системы булевых ф-ций")