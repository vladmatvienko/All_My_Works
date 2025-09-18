"""
Безымянная функция
Функции map, filter, reduce
"""

from functools import reduce


# map
def func(x):
    return x + x

#my_list = [(1, 3), (2, 4), (5, 3), (6, 8)]
# print(list(map(lambda x, y: (x+y, x-y), my_list, my_list2)))

# filter
#print(list(filter(lambda x: x[0] <= x[1], my_list)))

# reduce
my_list2 = [[1], [2, 3]]
print(reduce(lambda x, y: x + y, my_list2, my_list2))
