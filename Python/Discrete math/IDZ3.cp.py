
#TODO Если таблица истинности полинома Жегалкина не совпадает с таблицей истинности иходной ф-ции: вывести сообщение об ошибке

#TODO Добавить к обозначениям в полиноме Жегалкина комментарии: ^ = ⊕, & = and

note1 = "\n[NOTE!] Оператор ^ в данном случае символ логической операции сумма по модулю два (⊕);\n        Оператор & в данном случае символ логической операции конъюнкция (∧)"

def pars_2(a):
    a1 = a ; a2 = []
    # вектор неопределенных коэффициентов ; Максимальное количество коэффициентов
    p = ['a0', 'a2', 'a1', 'a12'] ; l = 4
    # вектор всевозможных элементарных конъюнкций полинома Жегалкина
    d_1 = {'a0': '1', 'a2': 'y', 'a1': 'x', 'a12': '(x&y)'}
    d = dict()
    # Строка, которую я передаю в ф-цию eval
    b = '' 
    # Вектор значений неопределенных коэффициентов, нулевых элементов каждой из строк треугольника Паскаля.
    index = [0] ; index[0] = a[0]
    # Треугольник Паскаля. Распаковываю список а, вывожу его элементы через пробел в стандартном потоке вывода
    print('1 строка треугольника Паскаля', *a)
    for j in range(len(a) - 1):
        result = []
        # Выполняется операция сумма по модулю 2 для j го вектора
        for i in range(len(a) - 1):
            result.append(a[i] ^ a[i + 1])
        # Добавляю в вектор элементы если он не пустой        
        if result:
            index.append(result[0])
        a = result
        # Динамически определяем количество символов в строке
        print(j + 2,'строка треугольника Паскаля', ' ' * j, *result)
    
    print('Коэффициенты полинома Жегалкина:', *index)
    for i in range(l):
        # p[i] -> ключ, по которому я получаю доступ к коэффициенту
        d[p[i]] = index[i]
    
    print('Переменные при коэффициентах')
    for i in d.keys():
        if d.get(i) == 1:
            b += d_1.get(i) + '^'
            print(i, d_1.get(i))
    b = b[:-1]
    print(f'{note1}\n\n[Полином Жегалкина:] P(x, y) = {b}\n')
    # Вывожу таблицу истинности для полинома Жегалкина
    print('Проверка\nx | y | F(x, y)')
    print('–––––––––––––––')
    for x in range(2):
        for y in range(2):
            a2.append(eval(b, {"x":x, "y":y}))
            print(f'{x} | {y} | {eval(b, {"x":x, "y":y})} |')
    if a1 != a2:
        print("\nТаблицы истинности не совпадают!") 
    else: print("\nТаблицы истинности совпадают!")

def pars_3(a):
    a1 = a ; a2 = []
    p = ['a0', 'a3', 'a2', 'a23', 'a1', 'a13', 'a12', 'a123']
    d_1 = {'a0': '1', 'a3': 'z', 'a2': 'y', 'a23': '(y&z)', 'a1': 'x', 'a13': '(x&z)', 'a12': '(x&y)',
           'a123': '(x&y&z)'}
    d = dict()
    b = ''
    l = 8
    index = [0]
    index[0] = a[0]
    print('1 строка треугольника Паскаля', *a)
    for j in range(len(a) - 1):
        result = []
        for i in range(len(a) - 1):
            result.append(a[i] ^ a[i + 1])
        if result:
            index.append(result[0])
        a = result
        print(j + 2,'строка треугольника Паскаля', ' ' * j, *result)
    print('Коэффициенты полинома Жегалкина:', *index)
    for i in range(l):
        d[p[i]] = index[i]
    #print(d)
    print('Переменные при коэффициентах')
    for i in d.keys():
        if d.get(i) == 1:
            b += d_1.get(i) + '^'
            print(i, d_1.get(i))
    b = b[:-1]
    print(f'{note1}\n\n[Полином Жегалкина:] P(x, y, z) = {b}\n')
    print('Проверка\nx | y | z | F(x, y, z)')
    print('–––––––––––––––––––––––')
    for x in range(2):
        for y in range(2):
            for z in range(2):
                a2.append(eval(b, {"x":x, "y":y, "z":z}))
                print(f'{x} | {y} | {z} |\t{eval(b, {"x":x, "y":y, "z":z})}')
    if a1 != a2:
        print("\nТаблицы истинности не совпадают!") 
    else: print("\nТаблицы истинности совпадают!")

'''
- eval(выражение) - позволяет вычислять произвольные выражения из входных данных на основе строк. Чтобы вычислить выражение на основе строки ф-ция выполняет следующие шаги:
    - Парсинг выражения
    - Перевод выражения на машинный язык
    - Вычислить как выражение Python
    - Возвратить результат вычислений

- ^ Оператор XOR в python - аналог суммы по модулю 2 в дискретной математике.

- Стрелка Пирса заменяется на отрицание над логическим ИЛИ

- Штрих Шеффера заменяется на отрицание над логическим И

- Оператор is в python возвращает true если оба оператора указывают на один и тот же объект в памяти.

- Импликация `x => y` в python заменяется на `not(x) or y`
'''

isexit = "N"
while isexit == "N":
    # вектор значений ф-ции, передается в ф-ции pars_2, pars_3, которые реализуют построение полинома Жегалкина методом треугольника Паскаля
    result = []
    ch = input('Введите номер логического выражения от 1 до 6 \n').lower()
    # Оператор match Добавлен в версии 3.10
    # N1 а)  
    if ch == '1':
        print("\nN1\na)\nf: x ⊕ (y → x)\n")
        print('x | y | F(x, y)')
        print('–––––––––––––––')
        for x in range(2):
            for y in range(2):
                F = x ^ (not(y) or x)
                if F:
                    print(x, '|', y, '| ', '  1')
                    result.append(1)
                else:
                    print(x, '|', y, '| ', '  0')
                    result.append(0)
        pars_2(result)
    elif ch == '2':
        # N1 б)
        print("\nб)\nf: (x ∼ (not y)) ⊕ ((not x) | y)\n")
        print('x | y | F(x, y)')
        print('–––––––––––––––')
        for x in range(2):
            for y in range(2):
                F = (x is not(y)) ^ (not(not(x) and y))
                if F:
                    print(x, '|', y, '| ', '  1')
                    result.append(1)
                else:
                    print(x, '|', y, '| ', '  0')
                    result.append(0)
        pars_2(result)
    elif ch == '3':
        # N1 в)
        print("\nв)\nf: ((not x) ↓ (y and x)) ⊕ ((not y) | x)\n")
        print('x | y | F(x, y)')
        print('–––––––––––––––')
        for x in range(2):
            for y in range(2):
                F = ( not(not(x) or (y and x)) ^ (not(not(y) and x)) )
                if F:
                    print(x, '|', y, '| ', '  1')
                    result.append(1)
                else:
                    print(x, '|', y, '| ', '  0')
                    result.append(0)
        pars_2(result)
    elif ch == '4':
        # N2 a) 
        print("\nN2\na)\nf: (x → (y ∼ z))")
        print('x | y | z | F(x, y, z)')
        print('––––––––––––––––––––––')
        for x in range(2):
            for y in range(2):
                for z in range(2):
                    F = (not(x) or (y is z))
                    if F:
                        print(x, '|', y, '|', z, '| ', '    1')
                        result.append(1)
                    else:
                        print(x, '|', y, '|', z, '| ', '    0')
                        result.append(0)
        pars_3(result)
    elif ch == '5':
        # N2 б) 
        print("\nб)\nf: (x | ((not z) → y)) or z\n")
        print('x | y | z | F(x, y, z)')
        print('––––––––––––––––––––––')
        for x in range(2):
            for y in range(2):
                for z in range(2):
                    F = (not(x and (z or y))) or z
                    if F:
                        print(x, '|', y, '|', z, '| ', '    1')
                        result.append(1)
                    else:
                        print(x, '|', y, '|', z, '| ', '    0')
                        result.append(0)
        pars_3(result)
    elif ch == '6':
        # N2 в)
        print("\nв)\nf: (x → y) ⊕ (z ↓ ((not z) and (not x)))\n")
        print('x | y | z | F(x, y, z)')
        print('––––––––––––––––––––––')
        for x in range(2):
            for y in range(2):
                for z in range(2):
                    F = (not(x) or y) ^ (not(z or ( not(z) and not(x))))
                    if F:
                        print(x, '|', y, '|', z, '| ', '    1')
                        result.append(1)
                    else:
                        print(x, '|', y, '|', z, '| ', '    0')
                        result.append(0)
        pars_3(result)
    else:
        print('Неправильный номер операции')
    isexit = input("Exit? [Y/N]\n")