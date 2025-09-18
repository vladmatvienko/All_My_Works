kol = int(input('Введите кол-во значений в массиве(считая от 1): '))
massive = []
z = 1
while kol>0:
    z = str(z)
    Number = float(input('Введите число №'+z+': '))
    massive.append(Number)
    kol -= 1
    z = int(z)
    z += 1
minn = 100000000000000000000000000000000
for i in range(len(massive)):
    k = massive[i]
    if k<minn:
        minn=k
sigma = int(input('Введите отличие от минимального числа из массива: '))
p = 0
for i in range(len(massive)):
    if massive[i]-sigma==minn:
        p+=1
print('Количество='+str(p))
    

    
