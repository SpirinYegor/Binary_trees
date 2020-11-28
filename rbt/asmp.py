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

plt.plot(x, y,  label=r'$\dfrac{T_{s}}{T_{rbt}}$')
plt.plot(t, t/t, label=r'$y=1$')
plt.legend(loc='best', fontsize=12)
plt.grid(True)
# plt.savefig("result.png")
plt.savefig("result_2.png")
# plt.title("Отношение времён вставки для set и rbt")
plt.title("Отношение времён удаления для set и rbt")
plt.show()

