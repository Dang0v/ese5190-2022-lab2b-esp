import numpy as np
from matplotlib import pyplot as plt

file = open("logs/20221115-2326hrs16sec_serialdata.txt", mode='r')
a = file.readlines()

sda = '' #22
scl = '' #23
for i in a:
    if len(i) > 3:
        if i[1] == '2':
            sda = sda + i[4:-1]
        if i[1] == '3':
            scl = scl + i[4:-1]



sda = list(map(int, sda))
scl = list(map(int, scl))

try:
    sda.remove(2)
except:
    pass
try:
    scl.remove(2)
except:
    pass

scl = [i + 2 for i in scl]

x = np.arange(0,len(sda))


plt.ylabel("sda                                         scl")
plt.plot(x, scl)
plt.plot(x, sda)

plt.show()
