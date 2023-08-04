# протестируем:
# шаблонов форм у меня долно быть ровно столько, сколько и формул
""" RES = [[[] , []] for i in range (4)]
RES[0][0].append("t")
RES[0][1].append("k")
RES[1][1].append("kk")
a = RES[0][0][0]
b = RES[0][1][0]
d = RES[0][1]
print(RES) """
# создаю ф-цию вывода СКНФ, СДНФ
funcNum = 1
resuslts = [0 for i in range(funcNum)]
varsTuple2 = (0, 0)
def expresion1(varsTuple2):
    sumMod2(varsTuple2[0], implication(varsTuple2[1], varsTuple2[0]))
# Дописать..., так чтобы ф-ция могла работать с выражением от произвольного количества переменных
def SDKNF(funcNum, varNum, expresion):
    # генерирую кортеж переменных
    varsTuple = tuple((0 for i in range(varNum)))
    for varsTuple in product((0, 1), repeat=varNum):
        results[funcNum] = expresion()
    
    