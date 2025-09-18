"""
Операторы
Условия: if-while-match
"""

a = 2
a += 1
# a = a + 1

'''
if b := 5 == a:
    print('ok')
elif a == 3:
    print(' a is 3')
else:
    print('not ok')
# finally:
    # print('is not')
'''
'''
match a: 
    case 3:
        print('ok')
    case 3:
        print('ok ok?')
    case _:
        print('not ok')
'''

a = [1, 2, 3, 4, 5]
b = [6, 7, 8]

counter = 5
while counter:
    counter -= 1
    print('ok')

# for i in a:
    # print(f'Value {i}')
