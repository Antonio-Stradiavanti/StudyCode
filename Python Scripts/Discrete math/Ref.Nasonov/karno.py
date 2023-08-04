import algebra
import maincalc
# Аргумент - таблица
def karno(table):
    # Для 2х переменных
    if len(table)==4:
        karnotable=[]
        karnotable.append([table[i][-1] for i in range(int(len(table)/2))])
        karnotable.append([table[i][-1] for i in range(int(len(table)/2),len(table))])
        print("x y| 0 | 1 |")
        for i in range(len(karnotable)):
            print(" ",i," ",sep="",end="|")
            for j in karnotable[i]:
                print(" ",j," ",sep="",end="|")
            print()
        DNF2(karnotable)
        pass
    # Для 3х переменных
    else:
        karnotable=[]
        karnotable.append([table[i][-1] for i in range(int(len(table)/2))])
        karnotable[0][2],karnotable[0][3]=karnotable[0][3],karnotable[0][2]
        karnotable.append([table[i][-1] for i in range(int(len(table)/2),len(table))])
        karnotable[1][2],karnotable[1][3]=karnotable[1][3],karnotable[1][2]
        print("xyz|0 0|0 1|1 1|1 0|")
        for i in range(len(karnotable)):
            print(" ",i," ",sep="",end="|")
            for j in karnotable[i]:
                print(" ",j," ",sep="",end="|")
            print()
        #print(karnotable)
        DNF(karnotable)
def perem(coordmas):
    coords=[]
    for i in coordmas:
        if i[0]==0:
            if i[1]==0:
                coords.append([0,0,0])
            elif i[1]==1:
                coords.append([0,0,1])
            elif i[1]==2:
                coords.append([0,1,1])
            elif i[1]==3:
                coords.append([0,1,0])
        else:
            if i[1]==0:
                coords.append([1,0,0])
            elif i[1]==1:
                coords.append([1,0,1])
            elif i[1]==2:
                coords.append([1,1,1])
            elif i[1]==3:
                coords.append([1,1,0])
    x,y,z=coords[0]
    for i in range(1,len(coords)):
        if x!=coords[i][0] and x!=-1:
            x=-1
        if y!=coords[i][1] and y!=-1:
            y=-1
        if z!=coords[i][2] and z!=-1:
            z=-1
    return[x,y,z]
def perem2(coordmas):
    coords=[]
    for i in coordmas:
        if i[0]==0:
            if i[1]==0:
                coords.append([0,0])
            elif i[1]==1:
                coords.append([0,1])
        else:
            if i[1]==0:
                coords.append([1,0])
            elif i[1]==1:
                coords.append([1,1])
    x,y=coords[0]
    for i in range(1,len(coords)):
        if x!=coords[i][0] and x!=-1:
            x=-1
        if y!=coords[i][1] and y!=-1:
            y=-1
    return[x,y]
def DNF2(karnotable):
    used=[]
    coord=[]
    for i in range(len(karnotable)):
        for j in range(len(karnotable[i])):
            coord.append([i,j])
    check=1
    dnf=""
    knf=""
    while(check):
        check=0
        for count,i in enumerate(coord):
            coordmas=[]
            if i not in used:
                if karnotable[i[0]][(i[1]+1)%2]==karnotable[i[0]][i[1]]  and karnotable[(i[0]+1)%2][(i[1]+1)%2]==karnotable[i[0]][i[1]]  and karnotable[(i[0]+1)%2][i[1]]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([i[0],(i[1]+1)%2])
                    used.append([(i[0]+1)%2,(i[1]+1)%2])
                    used.append([(i[0]+1)%2,i[1]])
                    coordmas.append(i)
                    coordmas.append([i[0],(i[1]+1)%2])
                    coordmas.append([(i[0]+1)%2,(i[1]+1)%2])
                    coordmas.append([(i[0]+1)%2,i[1]])
                    if karnotable[i[0]][i[1]]:
                        dnf="1"
                        knf="1"
                    else:
                        dnf="0"
                        knf="0"
                    pass
                elif karnotable[i[0]][(i[1]+1)%2]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([i[0],(i[1]+1)%2])
                    coordmas.append(i)
                    coordmas.append([i[0],(i[1]+1)%2])
                    x,y=perem2(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="-x"
                            else:
                                dnf+="x"
                            if y!=-1:
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="-y"
                            else:
                                dnf+="y"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="-x"
                            else:
                                knf+="x"
                            if y!=-1:
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="-y"
                            else:
                                knf+="y"
                        knf+=")∧"
                    pass
                elif karnotable[(i[0]+1)%2][i[1]]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([(i[0]+1)%2,i[1]])
                    coordmas.append(i)
                    coordmas.append([(i[0]+1)%2,i[1]])
                    x,y=perem2(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="-x"
                            else:
                                dnf+="x"
                            if y!=-1:
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="-y"
                            else:
                                dnf+="y"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="-x"
                            else:
                                knf+="x"
                            if y!=-1:
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="-y"
                            else:
                                knf+="y"
                        knf+=")∧"
                    pass
                else:
                    used.append(i)
                    coordmas.append(i)
                    x,y=perem2(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="-x"
                            else:
                                dnf+="x"
                            if y!=-1:
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="-y"
                            else:
                                dnf+="y"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="-x"
                            else:
                                knf+="x"
                            if y!=-1:
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="-y"
                            else:
                                knf+="y"
                        knf+=")∧"
                    pass
    newdnf=""
    for i in range(len(dnf)-1):
        newdnf+=dnf[i]
    newknf=""
    for i in range(len(knf)-1):
        newknf+=knf[i]
    print("ДНФ:", newdnf)
    print("КНФ:", newknf)
    pass
def DNF(karnotable):
    used=[]
    coord=[]
    for i in range(len(karnotable)):
        for j in range(len(karnotable[i])):
            coord.append([i,j])
    #print(coord)
    check=1
    dnf=""
    knf=""
    while(check):
        check=0
        for count,i in enumerate(coord):
            coordmas=[]
            if i not in used:
                check=1
                if karnotable[i[0]][(i[1]+1)%4]==karnotable[i[0]][i[1]] and karnotable[i[0]][(i[1]+2)%4]==karnotable[i[0]][i[1]] and karnotable[i[0]][(i[1]+3)%4]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([i[0],(i[1]+1)%4])
                    used.append([i[0],(i[1]+2)%4])
                    used.append([i[0],(i[1]+3)%4])
                    coordmas.append(i)
                    coordmas.append([i[0],(i[1]+1)%4])
                    coordmas.append([i[0],(i[1]+2)%4])
                    coordmas.append([i[0],(i[1]+3)%4])
                    x,y,z=perem(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="-x"
                            else:
                                dnf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="-y"
                            else:
                                dnf+="y"
                            if y!=-1 and z!=-1:
                                dnf+="∧"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                dnf+="-z"
                            else:
                                dnf+="z"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="-x"
                            else:
                                knf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="-y"
                            else:
                                knf+="y"
                            if y!=-1 and z!=-1:
                                knf+="∨"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                knf+="-z"
                            else:
                                knf+="z"
                        knf+=")∧"
                    pass
                elif karnotable[i[0]-1][i[1]-1]==karnotable[i[0]][i[1]] and karnotable[i[0]-1][i[1]]==karnotable[i[0]][i[1]] and karnotable[i[0]][i[1]-1]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([(i[0]+1)%2,(i[1]+3)%4])
                    used.append([(i[0]+1)%2,(i[1])%4])
                    used.append([(i[0])%2,(i[1]+3)%4])
                    coordmas.append(i)
                    coordmas.append([(i[0]+1)%2,(i[1]+3)%4])
                    coordmas.append([(i[0]+1)%2,(i[1])%4])
                    coordmas.append([(i[0])%2,(i[1]+3)%4])
                    x,y,z=perem(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="-x"
                            else:
                                dnf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="-y"
                            else:
                                dnf+="y"
                            if y!=-1 and z!=-1:
                                dnf+="∧"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                dnf+="-z"
                            else:
                                dnf+="z"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="-x"
                            else:
                                knf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="-y"
                            else:
                                knf+="y"
                            if y!=-1 and z!=-1:
                                knf+="∨"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                knf+="-z"
                            else:
                                knf+="z"
                        knf+=")∧"
                    pass
                elif karnotable[i[0]-1][(i[1]+1)%4]==karnotable[i[0]][i[1]] and karnotable[i[0]-1][i[1]]==karnotable[i[0]][i[1]] and karnotable[i[0]][(i[1]+1)%4]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([(i[0]+1)%2,(i[1]+1)%4])
                    used.append([(i[0]+1)%2,(i[1])%4])
                    used.append([(i[0])%2,(i[1]+1)%4])
                    coordmas.append(i)
                    coordmas.append([(i[0]+1)%2,(i[1]+1)%4])
                    coordmas.append([(i[0]+1)%2,(i[1])%4])
                    coordmas.append([(i[0])%2,(i[1]+1)%4])
                    x,y,z=perem(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="-x"
                            else:
                                dnf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="-y"
                            else:
                                dnf+="y"
                            if y!=-1 and z!=-1:
                                dnf+="∧"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                dnf+="-z"
                            else:
                                dnf+="z"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="-x"
                            else:
                                knf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="-y"
                            else:
                                knf+="y"
                            if y!=-1 and z!=-1:
                                knf+="∨"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                knf+="-z"
                            else:
                                knf+="z"
                        knf+=")∧"
                    pass
                elif karnotable[(i[0]+1)%2][i[1]-1]==karnotable[i[0]][i[1]] and karnotable[i[0]][i[1]-1]==karnotable[i[0]][i[1]] and karnotable[(i[0]+1)%2][i[1]]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([(i[0]+1)%2,(i[1]+3)%4])
                    used.append([(i[0])%2,(i[1]+3)%4])
                    used.append([(i[0]+1)%2,(i[1])%4])
                    coordmas.append(i)
                    coordmas.append([(i[0]+1)%2,(i[1]+3)%4])
                    coordmas.append([(i[0])%2,(i[1]+3)%4])
                    coordmas.append([(i[0]+1)%2,(i[1])%4])
                    x,y,z=perem(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="-x"
                            else:
                                dnf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="-y"
                            else:
                                dnf+="y"
                            if y!=-1 and z!=-1:
                                dnf+="∧"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                dnf+="-z"
                            else:
                                dnf+="z"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="-x"
                            else:
                                knf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="-y"
                            else:
                                knf+="y"
                            if y!=-1 and z!=-1:
                                knf+="∨"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                knf+="-z"
                            else:
                                knf+="z"
                        knf+=")∧"
                    pass
                elif karnotable[i[0]][i[1]-1]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([(i[0])%2,(i[1]+3)%4])
                    coordmas.append(i)
                    coordmas.append([(i[0])%2,(i[1]+3)%4])
                    x,y,z=perem(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="-x"
                            else:
                                dnf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="-y"
                            else:
                                dnf+="y"
                            if y!=-1 and z!=-1:
                                dnf+="∧"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                dnf+="-z"
                            else:
                                dnf+="z"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="-x"
                            else:
                                knf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="-y"
                            else:
                                knf+="y"
                            if y!=-1 and z!=-1:
                                knf+="∨"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                knf+="-z"
                            else:
                                knf+="z"
                        knf+=")∧"
                    pass
                elif karnotable[i[0]][(i[1]+1)%4]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([(i[0])%2,(i[1]+1)%4])
                    coordmas.append(i)
                    coordmas.append([(i[0])%2,(i[1]+1)%4])
                    x,y,z=perem(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="-x"
                            else:
                                dnf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="-y"
                            else:
                                dnf+="y"
                            if y!=-1 and z!=-1:
                                dnf+="∧"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                dnf+="-z"
                            else:
                                dnf+="z"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="-x"
                            else:
                                knf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="-y"
                            else:
                                knf+="y"
                            if y!=-1 and z!=-1:
                                knf+="∨"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                knf+="-z"
                            else:
                                knf+="z"
                        knf+=")∧"
                    pass
                elif karnotable[(i[0]+1)%2][i[1]]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([(i[0]+1)%2,(i[1])%4])
                    coordmas.append(i)
                    coordmas.append([(i[0]+1)%2,(i[1])%4])
                    x,y,z=perem(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="-x"
                            else:
                                dnf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="-y"
                            else:
                                dnf+="y"
                            if y!=-1 and z!=-1:
                                dnf+="∧"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                dnf+="-z"
                            else:
                                dnf+="z"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="-x"
                            else:
                                knf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="-y"
                            else:
                                knf+="y"
                            if y!=-1 and z!=-1:
                                knf+="∨"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                knf+="-z"
                            else:
                                knf+="z"
                        knf+=")∧"
                    pass
                elif karnotable[i[0]-1][i[1]]==karnotable[i[0]][i[1]]:
                    used.append(i)
                    used.append([(i[0]+1)%2,(i[1])%4])
                    coordmas.append(i)
                    coordmas.append([(i[0]+1)%2,(i[1])%4])
                    x,y,z=perem(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="-x"
                            else:
                                dnf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="-y"
                            else:
                                dnf+="y"
                            if y!=-1 and z!=-1:
                                dnf+="∧"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                dnf+="-z"
                            else:
                                dnf+="z"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="-x"
                            else:
                                knf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="-y"
                            else:
                                knf+="y"
                            if y!=-1 and z!=-1:
                                knf+="∨"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                knf+="-z"
                            else:
                                knf+="z"
                        knf+=")∧"
                    pass
                else:
                    used.append(i)
                    coordmas.append(i)
                    x,y,z=perem(coordmas)
                    if karnotable[i[0]][i[1]]:
                        dnf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                dnf+="-x"
                            else:
                                dnf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                dnf+="∧"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                dnf+="-y"
                            else:
                                dnf+="y"
                            if y!=-1 and z!=-1:
                                dnf+="∧"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                dnf+="-z"
                            else:
                                dnf+="z"
                        dnf+=")∨"
                    else:
                        knf+="("
                        if x!=-1:
                            if x!=karnotable[i[0]][i[1]]:
                                knf+="-x"
                            else:
                                knf+="x"
                            if x!=-1 and(y!=-1 or z!=-1):
                                knf+="∨"
                        if y!=-1:
                            if y!=karnotable[i[0]][i[1]]:
                                knf+="-y"
                            else:
                                knf+="y"
                            if y!=-1 and z!=-1:
                                knf+="∨"
                        if z!=-1:
                            if z!=karnotable[i[0]][i[1]]:
                                knf+="-z"
                            else:
                                knf+="z"
                        knf+=")∧"
                    pass
    newdnf=""
    for i in range(len(dnf)-1):
        newdnf+=dnf[i]
    newknf=""
    for i in range(len(knf)-1):
        newknf+=knf[i]
    print("ДНФ:", newdnf)
    print("КНФ:", newknf)
if __name__=="__main__":
    print("Ввод уравнения? Y/N")
    vvod=input()
    if vvod=="Y" or vvod=="y":
        vvod=1
    else:
        vvod=0
    if vvod:
        rezfunc,mas=maincalc.inp()
    else:
        print("Введите переменные")
        s=input()
        mas=[]
        for c in s:
            if(ord(c) in range(ord("a"),ord("z")+1)or ord(c) in range(ord("A"),ord("Z")+1)):
                if c not in mas:
                    mas.append(c)
        print("Введите результат функции")
        rezfunc=[]
        rezfunc=list(map(int,input().split()))
    table=[]
    table=algebra.maketable(rezfunc,table,mas)
    karno(table)