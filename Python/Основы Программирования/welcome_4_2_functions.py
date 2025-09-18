"""
Функции и порядок аргументов
"""

def func_name():
    print('ok')


# func_name()
# - Параметры в определении функции
# - func_args(a, b)


def func_args(a: int | list, b: int | list) -> tuple | str:
    return a.append(b), a if isinstance(a, list) and isinstance(b, int) else "Unsupported argument choice"


# print(func_args([1, 2], 3))
# print(func_args())

def func_args_v2(num_a, *, num_b, num_c=1):
    print(num_a, num_b, num_c)


# func_args_v2(1, num_b=2, num_c=3)
# func_args_v2(num_a=1, num_b=2, num_c=3)
# func_args_v2(3, num_c=3, num_b=2)

def func_unpack(*args):
    print(sum(args))


# func_unpack(1, 2, 3, 4)

def func_unpack_v2(a, v, *args, **kwargs):

    print(a, v, *args)
    print(kwargs.keys())


# func_unpack_v2(1, 2, 3, 4, 5, key1=3, key2=4, key3=5)
# my_awesome_func = func_unpack_v2
# my_awesome_func(1, 2, 3, 4, 5, key1=3, key2=4, key3=5)

# my_list = [1, 2, 3]
# print(my_append(4))
# print(my_list)

