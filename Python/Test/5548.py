from random import randint
kol = int(input('Введите кол-во значений в массиве 1 (считая от 1): '))
massive = []
z = 1
p = []
l = str(input('Генерируем случайно? (Да(y)/Нет(n) '))
if l == 'n':
    while kol>0:
        z = str(z)
        Number = float(input('Введите число №'+z+': '))
        massive.append(Number)
        kol -= 1
        z = int(z)
        z += 1
if l == 'y':
    while kol>0:
        massive.append(randint(-100000000000,10000000000000000))
        kol -= 1
kol1 = int(input('Введите кол-во значений в массиве 2 (считая от 1): '))
massive1 = []
z1 = 1
l1 = str(input('Генерируем случайно? (Да(y)/Нет(n) '))
if l1 == 'n':
    while kol1>0:
        z1 = str(z1)
        Number1 = float(input('Введите число №'+z1+': '))
        massive1.append(Number1)
        kol1 -= 1
        z1 = int(z1)
        z1 += 1
if l1 == 'y':
    while kol1>0:
        massive1.append(randint(-100000000000,10000000000000000))
        kol1 -= 1
print(massive, massive1)
w = ''
for i in range(len(massive)):
    for f in range(len(massive1)):
        if massive[i]==massive1[f]:
            p.append(massive[i])
print (list(set(p)))
