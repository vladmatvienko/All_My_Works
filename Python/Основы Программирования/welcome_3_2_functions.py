"""
Функции и порядок аргументов
"""

def my_func(*args):
    print(sum(args))


def my_func_kw(**kwargs):
    print(kwargs)


# my_func(1, 2, 3, 4, 5, 6, 7)
# my_func_kw(key1=1, key2=2, key3=3)
# my_func(1, b=2, c=3, d=4)

# - (не)обязательные
# - (не)ключевые

def my_func_all(a, b, *args, **kwargs):
    print(a, b)
    print(args)
    print(kwargs)

my_func_all(1, 23, 1, 3, key1=1, key2=2, s=1, w=2)

def my_func_tricky(a: int | str | list, b: int | str | list) -> None:
    print(a + b)


# my_custom_type = BinaryTree[Node[dict[str,list], list]]

#my_func_tricky('1', '2')
#my_func_tricky([1, 2, 3], [4, 5, 6])
#my_func_tricky(1, 2)
