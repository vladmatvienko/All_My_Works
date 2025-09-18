"""
Безымянная функция
Функции map, filter, reduce
"""

from functools import reduce


def sum_numbers(*args: int) -> int:
    return sum(args)


# print(sum_numbers(1, 2, 3))

def func_3(a: int):
    return a + 3


def my_map(function, iterable_obj):
    result_list = []
    for i in iterable_obj:
        result_list.append(function(i))
    return result_list


tup = [5, 7, 22, 97, 54, 62, 77, 23, 73, 61]
# new_list = list(map(lambda x, y: x + y, [1, 2, 3], tup))
# value = reduce(lambda x, y: x + y, tup)
filter_result = list(filter(lambda x: x > 50, tup))
# print(filter_result)

# map(функция, итерируемый_объект)
# filter(функция, итирируемый объект)
# reduce(функция, итерируемый объект)

d = reduce(lambda x,y: x+y,map(lambda x:x+x,filter(lambda x: (x>=3), (1,2,3,4))))
# print(d)


def input_func(num):
    try:
        num = int(num)
    except ValueError:
        pass
    return num


print(list(map(input_func, '1 23')))
