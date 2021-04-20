x = input()
ulaz = x.split("|")
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
    nextState=x.split(",",1)[1].split("->")[1].split(",")
    if nextState[0] != "#":
        if curr not in prijelaz.keys():
            prijelaz[curr]={}
        prijelaz[curr][transferSymbol]=nextState
    try:
        x = input()
    except Exception:
        break


def skok(curr, prijelaz, znak):
    izlaz=[]
    for i in curr:
        if i in prijelaz.keys():
            if znak in prijelaz[i].keys():
                for j in prijelaz[i][znak]:
                    if j not in izlaz:
                        izlaz.append(j)
    return izlaz


def epsilon(curr, prijelaz:dict):
    for c in curr:
        if c in prijelaz.keys():
            if "$" in prijelaz[c].keys():
                for i in prijelaz[c]["$"]:
                    if i not in curr:
                        curr.append(i)
    return curr

def prokletiNiz(niz):
    if not niz:
        print(f"#", end="")
    for i in niz:
        if i == niz[0]:
            print(f"{i}", end="")
        else:
            print(f",{i}", end="")

for u in ulaz:
    curr=[start]
    curr=epsilon(curr,prijelaz)
    curr.sort()
    prokletiNiz(curr)

    for i in u.split(","):
        curr=skok(curr,prijelaz,i)
        curr=epsilon(curr,prijelaz)
        curr.sort()
        print(f"|", end="")
        prokletiNiz(curr)
    print()