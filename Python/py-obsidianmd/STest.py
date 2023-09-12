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
# СДНФ, СКНФ
# Сначала конструирую базу, потом оптимизирую 
resuslts = 0
RES = [[], []]
temp = ""
# список с шаблонами для соствления элементарных дизъюнкций|конъюнкций в зависимости от значения ф-ции 0 -> эл. дизъюнкция, если значение элемента 0, то он входит в нее сам, иначе -> его отрицание.
ops = [" ⋁ ", " ⋀ "]
sL = [
        [["x", "not x"], ["y", "not y"], ["z", "not z"]], 
        [["not x", "x"], ["not y", "y"], ["not z", "z"]]
     ]
#---
print("\nf: (x → y) ⊕ (z ↓ ((not z) and (not x)))\nв)\nx\ty\tz\tnot z\tnot x\t(x → y)\t\t(not z) and (not x)\tz ↓ ((not z) and (not x))\t f\n")

for i in (0, 1):
    for j in (0, 1):
        for k in (0, 1):
            res2B = sumMod2(implication(i, j), PierHand(k, ((not k) and (not i))*1))
            temp = temp + "(" + sL[res2B][0][i] + ops[res2B] + sL[res2B][1][j] + ops[res2B] + sL[res2B][2][k] + ")"
            # добавляю в список либо элементарную конъюнкцию, либо элементарную дизъюнкцию
            RES[res2B].append(temp)
            temp = ""
            print(
                    i,
                    "\t",
                    j,
                    "\t",
                    k,
                    "\t",
                    (not k)*1,
                    "\t",
                    (not i)*1,
                    "\t",
                    implication(i, j),
                    "\t\t",
                    ((not k) and (not i))*1,
                    "\t\t\t\t",
                    PierHand(k, ((not k) and (not i))*1),
                    "\t\t\t",
                    res2B
                )
SDNF = ops[0].join(RES[1])
SKNF = ops[1].join(RES[0])
#print("Debug:", RES[0], RES[1], ' ', sep='\n')
print("Получим:", f"элементарных дизъюнкций: {len(RES[0])}", f"элементарных конъюнкций: {len(RES[1])}", f"СДНФ: {SDNF}", f"СКНФ: {SKNF}", ' ', sep='\n')
# осталось сформировать совершенную дизъюнктивную нормальную форму и совершенную конъюнктивную нормальную форму
