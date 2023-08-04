import calc
import algebra
global check
def SDNF(table,mas,check):
    res=""
    for i,e in enumerate(table):
        if e[-1]==1:
            for j in range(len(e)-1):
                if j==0:
                    res+="("
                if e[j]==0:
                    res+="-"+str(mas[j])
                else:
                    res+=str(mas[j])
                if j+2==len(e):
                    res+=")"
                else:
                    res+="∧"
            for l in range(i+1,len(table)):
                if table[l][-1]==1:
                    res+="∨"
                    break
    print("СДНФ: "+res)
    if check and res!="":
        calc.functofunc(res)
        
def SKNF(table,mas,check):
    res=""
    for i,e in enumerate(table):
        if e[-1]==0:            
            for j in range(len(e)-1):
                if j==0:
                    res+="("
                if e[j]==1:
                    res+="-"+str(mas[j])
                else:
                    res+=str(mas[j])
                if j+2==len(e):
                    res+=")"
                else:
                    res+="∨"
            for l in range(i+1,len(table)):
                if table[l][-1]==0:
                    res+="∧"
                    break
    print("СКНФ: "+res)
    if check and res!="":
        calc.functofunc(res)
if __name__=='__main__':
    print("Введите переменные")
    s=input()
    mas=[]
    d={}
    for c in s:
        if(ord(c) in range(ord("a"),ord("z")+1)or ord(c) in range(ord("A"),ord("Z")+1)):
            if c not in mas:
                mas.append(c)
    print("Введите результат функции")
    rezfunc=[]
    table=[]
    rezfunc=list(map(int,input().split()))
    table=algebra.maketable(rezfunc,table,mas)
    print("Выполнять проверку? Y/N")
    check=input()
    if check=="Y" or check=="y":
        check=1
    else:
        check=0
    SDNF(table)
    SKNF(table)