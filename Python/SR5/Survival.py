des = int(input('Введите число которое мы преобразуем: '))
ss = int(input('Введите целевую систему счисления: '))
otvet = ''
while des>0:
    otvet += ' '+str(des%ss)
    des //= ss
otvet = otvet[::-1] 
print(otvet)

    
