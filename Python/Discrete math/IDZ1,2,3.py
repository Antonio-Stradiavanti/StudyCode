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
funcNum = 6
results = [0 for i in range(funcNum)]
RES = [[[], []] for i in range(funcNum)]
temp = ""
# список с шаблонами для соствления элементарных дизъюнкций|конъюнкций в зависимости от значения ф-ции 0 -> эл. дизъюнкция, если значение элемента 0, то он входит в нее сам, иначе -> его отрицание.
ops = [" ⋁ ", " ⋀ "]
sL = [
        [["x", "not x"], ["y", "not y"], ["z", "not z"]], 
        [["not x", "x"], ["not y", "y"], ["not z", "z"]]
     ]
#---
# N1 а)       
print("\nN1\na)\nf: x ⊕ (y → x)\nx\ty\ty → x\tf\n")
for i in (0, 1):
    for j in (0, 1):
        results[0] = sumMod2(i, implication(j, i))
        temp = temp + "(" + sL[results[0]][0][i] + ops[results[0]] + sL[results[0]][1][j] + ")"
        # добавляю к вложенному списку
        RES[0][results[0]].append(temp)
        temp = ""
        print( 
                i, 
                j,
                implication(j, i),
                results[0],
                sep='\t'
             )
print("\nN1 а): Получим:", f"элементарных дизъюнкций: {len(RES[0][0])}", f"элементарных конъюнкций: {len(RES[0][1])}", f"СДНФ: {ops[0].join(RES[0][1])}", f"СКНФ: {ops[1].join(RES[0][0])}", ' ', sep='\n')
# N1 б)
print("\nб)\nf: (x ∼ (not y)) ⊕ ((not x) | y)\nx\ty\tnot x\tnot y\tx ∼ (not y)\t(not x) | y\t\t\tf\n")
for i in (0, 1):
    for j in (0, 1):
        results[1] = sumMod2(equal(i, (not j)), ShaeffersTouch((not i), j))
        temp = temp + "(" + sL[results[1]][0][i] + ops[results[1]] + sL[results[1]][1][j] + ")"
        RES[1][results[1]].append(temp)
        temp = ""
        print(
                i,
                j,
                (not i)*1,
                (not j)*1,
                equal(i, (not j)),
                '\t',
                ShaeffersTouch((not i), j),
                '\t',
                results[1],
                sep='\t'
             )
print("\nN1 б): Получим:", f"элементарных дизъюнкций: {len(RES[1][0])}", f"элементарных конъюнкций: {len(RES[1][1])}", f"СДНФ: {ops[0].join(RES[1][1])}", f"СКНФ: {ops[1].join(RES[1][0])}", ' ', sep='\n')
# N1 в)
print("\nв)\nf: ((not x) ↓ (y and x)) ⊕ ((not y) | x)\nx\ty\tnot x\tnot y\t(y and x)\t(not x) ↓ (y and x)\t(not y) | x\t\t\tf\n")
for i in (0, 1):
    for j in (0, 1):
        results[2] = sumMod2(PierHand((not i), (j and i)), ShaeffersTouch((not j), i))
        temp = temp + "(" + sL[results[2]][0][i] + ops[results[2]] + sL[results[2]][1][j] + ")"
        RES[2][results[2]].append(temp)
        temp = ""
        print(
                i, 
                j,
                (not i)*1,
                (not j)*1,
                (j and i)*1,
                "\t",
                PierHand((not i), (j and i)),
                "\t",
                ShaeffersTouch((not j), i),
                "\t",
                results[2],
                sep='\t'
        )
print("\nN1 в): Получим:", f"элементарных дизъюнкций: {len(RES[2][0])}", f"элементарных конъюнкций: {len(RES[2][1])}", f"СДНФ: {ops[0].join(RES[2][1])}", f"СКНФ: {ops[1].join(RES[2][0])}", ' ', sep='\n')      
#---
# N2 a)         
print("\n\nN2\nf: (x → (y ∼ z))\nа)\nx\ty\tz\t(y ∼ z)\t\t\tf\n")

for i in (0, 1):
    for j in (0, 1):
        for k in (0, 1):
            results[3] = implication(i, equal(j, k))
            temp = temp + "(" + sL[results[3]][0][i] + ops[results[3]] + sL[results[3]][1][j] + ops[results[3]] + sL[results[3]][2][k] + ")"
            RES[3][results[3]].append(temp)
            temp = ""
            print(
                    i, 
                    j, 
                    k,
                    equal(j, k),
                    '\t',
                    results[3],
                    sep='\t'
                )
print("\nN2 a): Получим:", f"элементарных дизъюнкций: {len(RES[3][0])}", f"элементарных конъюнкций: {len(RES[3][1])}", f"СДНФ: {ops[0].join(RES[3][1])}", f"СКНФ: {ops[1].join(RES[3][0])}", ' ', sep='\n') 
# N2 б)      
print("\nб)\nf: (x | ((not z) → y)) or z\nx\ty\tz\tnot z\t(not z) → y\tx | ((not z) → y)\t\t\tf\n")
for i in (0, 1):
    for j in (0, 1):
        for k in (0, 1):
            results[4] = (ShaeffersTouch(i, implication((not k), j)) or k)*1
            temp = temp + "(" + sL[results[4]][0][i] + ops[results[4]] + sL[results[4]][1][j] + ops[results[4]] + sL[results[4]][2][k] + ")"
            RES[4][results[4]].append(temp)
            temp = ""
            print(
                    i, 
                    j, 
                    k, 
                    (not k)*1,
                    implication((not k), j),
                    "\t\t",
                    ShaeffersTouch(i, implication((not k), j)),
                    "\t",
                    results[4],
                    sep='\t'
                )
print("\nN2 б): Получим:", f"элементарных дизъюнкций: {len(RES[4][0])}", f"элементарных конъюнкций: {len(RES[4][1])}", f"СДНФ: {ops[0].join(RES[4][1])}", f"СКНФ: {ops[1].join(RES[4][0])}", ' ', sep='\n')      
# N2 в)
print("\nв)\nf: (x → y) ⊕ (z ↓ ((not z) and (not x)))\nx\ty\tz\tnot z\tnot x\t(x → y)\t\t(not z) and (not x)\tz ↓ ((not z) and (not x))\t\tf\n")
for i in (0, 1):
    for j in (0, 1):
        for k in (0, 1):
            results[5] = sumMod2(implication(i, j), PierHand(k, ((not k) and (not i))*1))
            temp = temp + "(" + sL[results[5]][0][i] + ops[results[5]] + sL[results[5]][1][j] + ops[results[5]] + sL[results[5]][2][k] + ")"
            RES[5][results[5]].append(temp)
            temp = ""
            print(
                    i, 
                    j,
                    k,
                    (not k)*1,
                    (not i)*1,
                    implication(i, j),
                    "\t",
                    ((not k) and (not i))*1,
                    "\t",
                    PierHand(k, ((not k) and (not i))*1),
                    "\t\t",
                    results[5],
                    sep='\t'
                )  
print("\nN2 в): Получим:", f"элементарных дизъюнкций: {len(RES[5][0])}", f"элементарных конъюнкций: {len(RES[5][1])}", f"СДНФ: {ops[0].join(RES[5][1])}", f"СКНФ: {ops[1].join(RES[5][0])}", ' ', sep='\n')      
                
# Проверка             