import numpy as np
arr = [1000, 1000]
print(len(arr)-1)
for i in range(0, len(arr)-1):
    print(arr[i], end=" ")
    print(arr[i+1])
    for j in range(arr[i]):
        for k in range(arr[i+1]):
            print(np.random.randint(-10, 11), end=" ")
        print()
