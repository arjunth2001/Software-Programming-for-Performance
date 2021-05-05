import numpy as np
V = 1693
E = 100000
list = [i for i in range(1, V+1)]
print(V, end=" ")
print(E)
for _ in range(E):
    x = np.random.choice(list)
    y = np.random.choice(list)
    w = np.random.randint(1, 100001)
    print(x, end=" ")
    print(y, end=" ")
    print(w)
