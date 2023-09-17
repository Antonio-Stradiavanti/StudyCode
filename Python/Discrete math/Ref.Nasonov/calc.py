import algebra
#Отрицание
def no(val1):
    val1=int(val1)
    return(not val1)
#Коньюнкция
def kon(val1,val2):
    val1=int(val1)
    val2=int(val2)
    return(val1 and val2)
#Дезъюнкция
def dez(val1,val2):
    val1=int(val1)
    val2=int(val2)
    return(val1 or val2)
#Импликация
def impl(val1,val2):
    val1=int(val1)
    val2=int(val2)
    return((not val1) or val2)
#сумма по mod 2
def summod2(val1,val2):
    val1=int(val1)
    val2=int(val2)
    return((val1+val2)%2)
#Эквивалентность
def eqivival(val1,val2):
    val1=int(val1)
    val2=int(val2)
    return(val1==val2)
#Штрих Шеффера
def shtrih(val1,val2):
    val1=int(val1)
    val2=int(val2)
    return(not(val1 and val2))
#Стрелка Пирса
def strel(val1,val2):
    val1=int(val1)
    val2=int(val2)
    return(not(val1 or val2))
def razbor(i,res):
    tol=""
    tor=""
    midind=0
    for toind in range(len(res[str(i)])):
        if res[str(i)][toind] not in['-','(',')','*','|','!','+','>','~','%','^','∧','∨']:
            tol+=res[str(i)][toind]
        else:
            midind=toind
            break
    for toind in range(midind+1,len(res[str(i)])):
        if res[str(i)][toind] not in['-','(',')','*','|','!','+','>','~','%','^','∧','∨']:
            tor+=res[str(i)][toind]
    return tol,tor
res={}
n=1
#Функция для рабиения на действии
def functofunc(func,res={},n=1):
    res={}
    n=1
    #Удаление лишних пробелов
    func=func.replace(" ","")
    d={}
    mas=[]
    #Запись переменных
    for c in func:
        if(ord(c) in range(ord("a"),ord("z")+1)or ord(c) in range(ord("A"),ord("Z")+1)):
            d[c]=0
            if c not in mas:
                mas.append(c)
    mas.sort()
    rez(func,res,n)
    for i in mas:
        res[i]=0
    #print(res)
    otvet_table(mas,res.copy())
# Возвращает результат переданной ф-ции.
def rez(func,res,n,s=0,e=0,scob=0):
    if e==0 and not scob:
        e=len(func)
    i=s
    s1=-1
    e1=-1
    oper=9
    index=-1
    while(e-s)>len(str(n)):
        if s==0 and not scob:
            e=len(func)
        if i>=e:
            if oper==1:
                masindex=[]
                masindex.append(index)
                for delin in range(index+1,len(func)):
                    if func[delin] not in['-','(',')','*','|','!','+','>','~','%','^','∧','∨']:
                        masindex.append(delin)
                    else:
                        break
                #Добавление действия и замена в функции на число действия
                res[str(n)]=""
                for delind in masindex:
                    res[str(n)]+=func[delind]
                newfunc=""
                for kk in range(len(func)):
                    if kk==index:
                        newfunc+=str(n)
                        continue
                    elif kk in masindex:
                        continue
                    newfunc+=func[kk]
                func=newfunc
                e-=len(masindex)
                e+=len(str(n))
                n+=1
            elif oper<9:
                masindex=[]
                for delin in reversed(range(0,index)):
                    if func[delin] not in['-','(',')','*','|','!','+','>','~','%','^','∧','∨']:
                        masindex.append(delin)
                    else:
                        break
                temp=[]
                for delin in reversed(range(len(masindex))):
                    temp.append(masindex[delin])
                masindex=temp
                masindex.append(index)
                for delin in range(index+1,len(func)):
                    if func[delin] not in['-','(',')','*','|','!','+','>','~','%','^','∧','∨']:
                        masindex.append(delin)
                    else:
                        break
                
                res[str(n)]=""
                for delind in masindex:
                    res[str(n)]+=func[delind]
                newfunc=""
                for kk in range(len(func)):
                    if kk==index:
                        newfunc+=str(n)
                        continue
                    elif kk in masindex:
                        continue
                    newfunc+=func[kk]
                func=newfunc
                e-=len(masindex)
                e+=len(str(n))
                n+=1
            i=s
            s1=-1
            e1=-1
            oper=9
            index=-1
            continue
        c=func[i]
        if c=='(':
            s1=i
        elif c==')':
            e1=i
            newfunc=""
            for kk in range(len(func)):
                if kk==s1 or kk==e1:
                    continue
                newfunc+=func[kk]
            func=newfunc
            #Вычисление действий в скобках в первую очередь
            func,res,n=rez(func,res,n,s1,e1-1,1)
            i=s
            s1=-1
            e1=-1
            oper=9
            index=-1
            continue
        elif c=='-'and oper>1:
            oper=1
            index=i
        elif (c=='*'or c=='∧') and oper>2:
            oper=2
            index=i
        elif c=='|' and oper>3:
            oper=3
            index=i
        elif c=='!' and oper>4:
            oper=4
            index=i
        elif (c=='+'or c=='∨')and oper>5:
            oper=5
            index=i
        elif c=='>' and oper>6:
            oper=6
            index=i
        elif c=='~' and oper>7:
            oper=7
            index=i
        elif c=='%' or c=='^'and oper>8:
            oper=8
            index=i
        i+=1       
    return func,res,n

#Функция для подстановки чисел и вычисления результата
def otvet_table(mas,res,el=0):
    if el>=len(mas):
        for i in range(len(res)-len(mas),len(res)):
            print(mas[i-len(res)+len(mas)],'|',res[str(mas[i-len(res)+len(mas)])],'|',end=" ")
        for i in range(1,len(res)+1-len(mas)):
            urav=res[str(i)]
            print(urav,'|',end=" ")
            if '-'in res[str(i)]:
                to=""
                for toind in range(1,len(res[str(i)])):
                    to+=res[str(i)][toind]
                res[str(i)]=no(res[to])
            elif '*' in res[str(i)]or '∧' in res[str(i)]:
                tol,tor=razbor(i,res)
                res[str(i)]=kon(res[tol],res[tor])
            elif '|'in res[str(i)]:
                tol,tor=razbor(i,res)
                res[str(i)]=shtrih(res[tol],res[tor])
            elif '!'in res[str(i)]:
                tol,tor=razbor(i,res)
                res[str(i)]=strel(res[tol],res[tor])
            elif '+'in res[str(i)]or '∨'in res[str(i)]:
                tol,tor=razbor(i,res)
                res[str(i)]=dez(res[tol],res[tor])
            elif '>'in res[str(i)]:
                tol,tor=razbor(i,res)
                res[str(i)]=impl(res[tol],res[tor])
            elif '~'in res[str(i)]:
                tol,tor=razbor(i,res)
                res[str(i)]=eqivival(res[tol],res[tor])
            elif '%'in res[str(i)] or '^'in res[str(i)]:
                tol,tor=razbor(i,res)
                res[str(i)]=summod2(res[tol],res[tor])
            print(int(res[str(i)]),'|',end=" ")
            if i+1==len(res)+1-len(mas):
                print()
        return
    for res[mas[el]] in range(2):
        otvet_table(mas,res.copy(),el+1)

#Функция для подстановки чисел и вычисления результата
def otvet(mas,res,el=0,rezfunc=[]):
    if el>=len(mas):
        for i in range(1,len(res)+1-len(mas)):
            urav=res[str(i)]
            if '-'in res[str(i)]:
                to=""
                for toind in range(1,len(res[str(i)])):
                    to+=res[str(i)][toind]
                res[str(i)]=no(res[to])
            elif '*' in res[str(i)]or '∧' in res[str(i)]:
                tol,tor=razbor(i,res)
                res[str(i)]=kon(res[tol],res[tor])
            elif '|'in res[str(i)]:
                tol,tor=razbor(i,res)
                res[str(i)]=shtrih(res[tol],res[tor])
            elif '!'in res[str(i)]:
                tol,tor=razbor(i,res)
                res[str(i)]=strel(res[tol],res[tor])
            elif '+'in res[str(i)]or '∨'in res[str(i)]:
                tol,tor=razbor(i,res)
                res[str(i)]=dez(res[tol],res[tor])
            elif '>'in res[str(i)]:
                tol,tor=razbor(i,res)
                res[str(i)]=impl(res[tol],res[tor])
            elif '~'in res[str(i)]:
                tol,tor=razbor(i,res)
                res[str(i)]=eqivival(res[tol],res[tor])
            elif '%'in res[str(i)] or '^'in res[str(i)]:
                tol,tor=razbor(i,res)
                res[str(i)]=summod2(res[tol],res[tor])
            if i+1==len(res)+1-len(mas):
                rezfunc.append(int(res[str(i)]))
        return rezfunc
    for res[mas[el]] in range(2):
        rezfunc=otvet(mas,res.copy(),el+1,rezfunc)
    return rezfunc

if __name__=='__main__':
    print("- отрицание \n* и \n| штрих Шеффера \n! Стрелка пирса \n+ или \n> импликация \n~ эквивалентность \n% сумма по mod 2")
    #Ввод любой логической функции 
    while True:       
        func=input()
        functofunc(func,res,n)