M = 100000000
b = [1, 5, 6, 7, 4, 9, 3, 7]
n = 0
for i in range(len(b)):
    if b[i]>M:
        M=b[i]
        n = i
for i in range(len(b)):
    if i>n:
        b[i]=0
print(b)
