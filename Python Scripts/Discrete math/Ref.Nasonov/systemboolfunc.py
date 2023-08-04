def classM(list=[],table=[],check=1):
    if len(list)==0:
        for i in table:
            list.append(i[-1])
    if len(list)==1:
        return check
    list1=[]
    list2=[]
    for i in range(int(len(list)/2)):
        list1.append(list[i])
    for i in range(int(len(list)/2), len(list)):
        list2.append(list[i])
        if list1[i-int(len(list)/2)]>list2[-1]:
            check=0
    check1=classM(list1,[],check)
    check2=classM(list2,[],check)
    check=min(check1,check2)
    return check
def classT0(table):
    check =1
    if table[0][-1]:
        check=0
    return check
def classT1(table):
    check =1
    if not table[-1][-1]:
        check=0
    return check
def classS(table):
    check=1
    list1=[]
    for i in table:
        list1.append(i[-1])
    list2=list1[::-1]
    for i in range(len(list1)):
        list2[i]=not(list2[i])
        if list1[i]!=list2[i]:
            check=0
    return check
def classL(zhegalkin):
    zhegalkin=zhegalkin.replace("∧","")
    zhegalkin=zhegalkin.replace("⊕","")
    zhegalkin=zhegalkin.split()
    check=1
    for i in zhegalkin:
        if len(i)>1:
            check=0
            break
    return check
def rezclass(table,zhegalkin):
    rez=[]
    rez.append(classT0(table))
    rez.append(classT1(table))
    rez.append(classS(table))
    rez.append(classM([],table))
    rez.append(classL(zhegalkin))
    return rez