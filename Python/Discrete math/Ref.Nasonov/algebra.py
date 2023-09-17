def algebra(rezfunc,mas,table):
    temprezfunc=rezfunc.copy()
    for i in range(len(rezfunc)):
        rezfunc=temprezfunc.copy()
        for j in range(i,len(rezfunc)-1):
            temprezfunc[j+1]=(rezfunc[j]+rezfunc[j+1])%2
    rez=[]
    if(temprezfunc[0]==1):
        rez.append('1')
        rez.append("⊕ ")
    for i in range(1,len(temprezfunc)):
        if temprezfunc[i]:
            for j in range(len(table[i])-1):
                if table[i][j]==1:
                    rez.append(mas[j])
                    rez.append('∧')
            rez.pop()
            rez.append("⊕ ")
    if len(rez)!=0:
        rez.pop()
    urav=""
    for i in rez:
        urav+=str(i)
    if(len(urav)==0):
        return '0'
    return urav

# На вход подается список значении ф-ции (func)
def maketable(rezfunc,table,mas):
    table=[[] for i in range(len(rezfunc))]
    a=["0","b"]
    for i in range(len(mas)):
        a.append("0")
    for i in range(len(rezfunc)):
        for j in range(2,len(a)):
            table[i].append(int(a[j]))
        dob=1
        for j in reversed(range(2,len(a))):
            if a[j]=='0' and dob==1:
                a[j]='1'
                break
            else:
                a[j]='0' 
        table[i].append(rezfunc[i])
    return table
       
if __name__=='__main__':
    print("Введите переменные")
    s=input()
    mas=[]
    for c in s:
        if(ord(c) in range(ord("a"),ord("z")+1)or ord(c) in range(ord("A"),ord("Z")+1)):
            if c not in mas:
                mas.append(c)
    func=[*map(int,input().split())]
    table=[]
    maketable(func,table,mas)
    urav=algebra(func,mas,table)
    print(urav)