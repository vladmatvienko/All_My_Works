A = str(input('Введите имя: '))
B = str(input('Введите фамилию: '))
C = int(input('Введите год: '))
print(A+'_'+B+'_'+str(C))
A,B = B,A
C = C+60
print(A+'_'+B+'_'+str(C))
