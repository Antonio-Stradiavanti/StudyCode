def pars_2(a):
    p = ['a0', 'a2', 'a1', 'a12']
    d_1 = {'a0': '1', 'a2': 'y', 'a1': 'x', 'a12': '(x&y)'}
    d = dict()
    b = ''
    l = 4
    index = [0]
    index[0] = a[0]
    for j in range(len(a)):
        result = []
        for i in range(len(a) - 1):
            result.append(a[i] ^ a[i + 1])
        if result:
            index.append(result[0])
        a = result
        # print(result)
    #print(index)
    for i in range(l):
        d[p[i]] = index[i]
    for i in d.keys():
        if d.get(i) == 1:
            b += d_1.get(i) + '^'
            # print(i, d_1.get(i))
    b = b[:-1]
    print('Полином Жегалкина\nP(x, y) = ', b)
    print('Проверка\nx | y | F(x, y)')
    print('–––––––––––––––')
    for x in range(2):
        for y in range(2):
            print(x, '|', y, '|   ', eval(b))


def pars_3(a):
    p = ['a0', 'a3', 'a2', 'a23', 'a1', 'a13', 'a12', 'a123']
    d_1 = {'a0': '1', 'a3': 'z', 'a2': 'y', 'a23': '(y&z)', 'a1': 'x', 'a13': '(x&z)', 'a12': '(x&y)',
           'a123': '(x&y&z)'}
    d = dict()
    b = ''
    l = 8
    index = [0]
    index[0] = a[0]
    for j in range(len(a)):
        result = []
        for i in range(len(a) - 1):
            result.append(a[i] ^ a[i + 1])
        if result:
            index.append(result[0])
        a = result
        #print(result)
    #print(index)
    for i in range(l):
        d[p[i]] = index[i]
    for i in d.keys():
        if d.get(i) == 1:
            b += d_1.get(i) + '^'
            # print(i, d_1.get(i))
    b = b[:-1]
    print('Полином Жегалкина\nP(x, y, z) = ', b)
    print('Проверка\nx | y | z | F(x, y, z)')
    print('–––––––––––––––––––––––')
    for x in range(2):
        for y in range(2):
            for z in range(2):
                print(x, '|', y, '|', z, '|     ', eval(b))


while True:
    result = []
    a = input('Введите номер логического выражения от 1 до 6 \n').lower()
    match a:
        case '1':
            print('x | y | F(x, y)')
            print('–––––––––––––––')
            for x in range(2):
                for y in range(2):
                    F = (x and y) is x
                    if F:
                        print(x, '|', y, '| ', '  1')
                        result.append(1)
                    else:
                        print(x, '|', y, '| ', '  0')
                        result.append(0)
            pars_2(result)
        case '2':
            print('x | y | F(x, y)')
            print('–––––––––––––––')
            for x in range(2):
                for y in range(2):
                    F = not (x or (y ^ (not x and y)))
                    if F:
                        print(x, '|', y, '| ', '  1')
                        result.append(1)
                    else:
                        print(x, '|', y, '| ', '  0')
                        result.append(0)
            pars_2(result)
        case '3':
            print('x | y | F(x, y)')
            print('–––––––––––––––')
            for x in range(2):
                for y in range(2):
                    F = (y or not (not x or (not((not x or y) and y)))) and (not y or not x or (not (not x or y) and y))
                    if F:
                        print(x, '|', y, '| ', '  1')
                        result.append(1)
                    else:
                        print(x, '|', y, '| ', '  0')
                        result.append(0)
            pars_2(result)
        case '4':
            print('x | y | z | F(x, y, z)')
            print('––––––––––––––––––––––')
            for x in range(2):
                for y in range(2):
                    for z in range(2):
                        F = (z or not(not(x or y))) and (not z or not(x or y))
                        if F:
                            print(x, '|', y, '|', z, '| ', '    1')
                            result.append(1)
                        else:
                            print(x, '|', y, '|', z, '| ', '    0')
                            result.append(0)
            pars_3(result)
        case '5':
            print('x | y | z | F(x, y, z)')
            print('––––––––––––––––––––––')
            for x in range(2):
                for y in range(2):
                    for z in range(2):
                        F = (not (x and z)) or (not(y or z)) or (not(not y or not z))
                        if F:
                            print(x, '|', y, '|', z, '| ', '    1')
                            result.append(1)
                        else:
                            print(x, '|', y, '|', z, '| ', '    0')
                            result.append(0)
            pars_3(result)
        case '6':
            print('x | y | z | F(x, y, z)')
            print('––––––––––––––––––––––')
            for x in range(2):
                for y in range(2):
                    for z in range(2):
                        F = not y or (((x or (not(z ^ y))) and (not x or (z ^ y))) or (not x))
                        if F:
                            print(x, '|', y, '|', z, '| ', '    1')
                            result.append(1)
                        else:
                            print(x, '|', y, '|', z, '| ', '    0')
                            result.append(0)
            pars_3(result)
        case 'стоп':
            break
        case _:
            print('Неправильный номер операции')
            break