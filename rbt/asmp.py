import numpy as np
import matplotlib.pyplot as plt

out = open("D:/CLion 2019.2.4/CLionProjects/red-black-tree/cmake-build-debug/result_2.txt", 'r')
array = out.readlines()
x = []
y = []
t = np.arange(0.1, 10**6, 1000)
for A in array:
    A.rstrip()
    tmp = A.split()
    x.append(float(tmp[0]))
    y.append(float(tmp[1]))
out.close()

plt.plot(x, y)
plt.plot(t, t/t)
plt.show()
plt.savefig("result_2.png")
