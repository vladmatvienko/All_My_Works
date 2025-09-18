from random import randint
kol = int(input('Введите кол-во значений в массиве(считая от 1): '))
massive = []
q = kol
z = 1
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
print(massive)
maxx = -10000000000000000000000000
for i in range(len(massive)):
    k = massive[i]
    if k>maxx:
        maxx=k
        d = i
for i in range(len(massive)):
    if massive[i]==maxx:
        for j in range(i+1,q):
            massive.pop(j)
            massive.insert(j, 0)
print(massive)
            





        
    
