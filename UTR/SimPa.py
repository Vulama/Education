x = input()
ulaz = x.split("|")

x = input()
state = x.split(",")

x = input()
abc = x.split(",")

x = input()
stanjastog = x.split(",")

x = input()
end = x.split(",")

x = input()
start = x

x = input()
stog = []
m=x

x = input()
prijelaz={}

def reverse(x):
    return x[::-1]

while(x):
    trenstanje = x.split(",")[0]
    ulazniznak=x.split(",")[1]
    znakstoga=x.split(",")[2].split("->")[0]
    novostanje=x.split(",")[2].split("->")[1]
    znakovistoga=reverse(x.split(",")[3])

    if novostanje[0] != "$":
        if trenstanje not in prijelaz.keys():
            prijelaz[trenstanje]={}
        if ulazniznak not in prijelaz[trenstanje].keys():
            prijelaz[trenstanje][ulazniznak]={}
        prijelaz[trenstanje][ulazniznak][znakstoga]=[novostanje,znakovistoga]
    try:
        x = input()
    except Exception:
        break

def skok(tren, ulazni, prijelaz):
    sljedece=None
    try:
        vrh = stog.pop()
        if not vrh:
            if tren in end:
                print("1", end="")
            else:
                print("0", end="")

        try:
            sljedece=prijelaz[tren][ulazni][vrh][0]
            znakovistoga=prijelaz[tren][ulazni][vrh][1]

            try:
                if znakovistoga != "$":
                    for i in znakovistoga:
                        stog.append(i)
                    print(f"{sljedece}#{''.join(reverse(stog))}|", end="")
                else:
                    if stog:
                        print(f"{sljedece}#{''.join(reverse(stog))}|", end="")
                    else:
                        print(f"{sljedece}#$|", end="")

            except Exception:
                if ulazni == "$":
                    stog.append(vrh)
                else:
                    print("fail|0")
                    return None

        except Exception:
            if ulazni == "$":
                stog.append(vrh)
            else:
                print("fail|0")
                return None

    except Exception:
        if ulazni=="$":
            stog.append(vrh)
        print("fail|0")
        return None

    return sljedece


def epsilon(tren, prijelaz):
    temp = tren
    try:
        while "$" in prijelaz[tren].keys():
            try:
                if prijelaz[tren]["$"][stog[-1]]:
                    tren=skok(tren, "$", prijelaz)
                    if tren in end:
                        return tren
            except Exception:
                return tren
        return tren
    except Exception:
        if not tren:
            return temp
        return tren
for u in ulaz:
    stog=[m]
    token = 0
    tren=start
    print(f"{tren}#{stog[-1]}|", end="")
    for i in u.split(","):
        tren = epsilon(tren, prijelaz)
        tren = skok(tren, i, prijelaz)
        if not tren:
            token=1
            break

    if tren not in end and not token:
        tren = epsilon(tren, prijelaz)

    if not token:
        if tren in end:
            print("1")
        else:
            print("0")
