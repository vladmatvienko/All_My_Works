"""
Операторы
Условия: if-while-match
"""

# ==
# is
a = 1002
b = 500 + 501
# print(a == b)
# print(a is b)

# print(f'First {a},\nSecond {b},\nThird {c}')

'''
if a == b:
    print('ok')
elif a < b:
    print('lower')
elif a > b:
    print('greater')
else:
    print('not ok')
'''

'''
match a:
    case 1000:
        print('ok')
    case 1002:
        print('greater')
    case 1002:
        print('greater')
    case _:
        print('not ok')
'''

a = [122, 234, 345, 454]

# for index, value in enumerate(a):
    # print(f'Index: {index}, Value: {value}')

# counter = 0
# while counter < len(a):
    # print(f'Index: {counter}, Value {a[counter]}')
    # counter += 1
