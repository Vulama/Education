x = input()
state = x.split(",")
x = input()
abc = x.split(",")
x = input()
end = x.split(",")
x = input()
start = x
x = input()
prijelaz={}

while(x):
    curr = x.split(",")[0]
    transferSymbol=x.split(",")[1].split("->")[0]
    nextState=x.split(",",1)[1].split("->")[1]
    if nextState[0] != "#":
        if curr not in prijelaz.keys():
            prijelaz[curr]={}
        prijelaz[curr][transferSymbol]=nextState
    try:
        x = input()
    except Exception:
        break

def funkcijaBFS(start):
    prodeni=[]
    prodeni.append(start)
    i=0
    while i<len(prodeni):
        for j in prijelaz[prodeni[i]].values():
            if j not in prodeni:
                prodeni.append(j)
        i+=1
    return prodeni

dohStanja=funkcijaBFS(start)
state=dohStanja
state.sort()

for i in end.copy():
    if i not in dohStanja:
        end.remove(i)

for i in prijelaz.copy().keys():
    if i not in dohStanja:
        prijelaz.pop(i)

table = []
counter = True
for r in range(len(state)-1):
      row = []
      for c in range(r+1):
            row.append(counter)
      table.append(row)

mIncident={}

#stavljanje x-eva u tablicu
for i in range(len(table)):
    for j in range(i+1):
        t1 = 0
        t2 = 0
        if state[i+1] in end:
            t1=1
        if state[j] in end:
            t2=1
        if t1!=t2:
            table[i][j]=False
        else:
            token=0
            for slovo in abc:
                t1=0
                t2=0
                if prijelaz[state[i + 1]][slovo] in end:
                    t1=1
                if prijelaz[state[j]][slovo] in end:
                    t2=1
                if t1!=t2:
                    token+=1
            if token!=0:
                table[i][j] = False
            else:
                for slovo in abc:
                    if (prijelaz[state[i + 1]][slovo],prijelaz[state[j]][slovo]) not in mIncident:
                        mIncident[prijelaz[state[i + 1]][slovo],prijelaz[state[j]][slovo]]=[]

                    mIncident[prijelaz[state[i + 1]][slovo],prijelaz[state[j]][slovo]].append((state[i+1],state[j]))

#for i in table:
#    print(i)

for i in mIncident.keys():
    try:
        if table[state.index(i[0])-1][state.index(i[1])] == False:
            for j in mIncident[i]:
                table[state.index(j[0])-1][state.index(j[1])] = False
    except Exception:
        pass

#for i in table:
#   print(i)

parovi={}
for i in range(len(table)):
    for j in range(len(table[i])):
        if table[i][j]==True:
            if state[i+1]>state[j] and state[i+1] not in parovi.keys():
                parovi[state[i+1]] = state[j]
            elif state[j] not in parovi.keys():
                parovi[state[j]] = state[i+1]

for i in state.copy():
    if i in parovi.keys():
        state[state.index(i)] = parovi[i]

state=list(set(state))
state.sort()

for i in end.copy():
    if i in parovi.keys():
        end[end.index(i)] = parovi[i]

end=list(set(end))
end.sort()

if start in parovi.keys():
    start=parovi[start]

newPrijelaz={}

#print(parovi)

for i in prijelaz.keys():
    if i in parovi.keys():
        if parovi[i] not in newPrijelaz:
            newPrijelaz[parovi[i]]={}

            for j in prijelaz[i].keys():
                if prijelaz[i][j] in parovi.keys():
                    if j not in newPrijelaz[parovi[i]]:
                        newPrijelaz[parovi[i]][j]=parovi[prijelaz[i][j]]
                else:
                    if j not in newPrijelaz[parovi[i]]:
                        newPrijelaz[parovi[i]][j]=prijelaz[i][j]
    else:
        if i not in newPrijelaz:
            newPrijelaz[i]={}

            for j in prijelaz[i].keys():
                if prijelaz[i][j] in parovi.keys():
                    if j not in newPrijelaz[i]:
                        newPrijelaz[i][j]=parovi[prijelaz[i][j]]
                else:
                    if j not in newPrijelaz[i]:
                        newPrijelaz[i][j]=prijelaz[i][j]

print(",".join(state))
print(",".join(abc))
print(",".join(end))
print(start)


for i in newPrijelaz:
    for j in newPrijelaz[i]:
        print(i + "," + j + "->" + newPrijelaz[i][j])
