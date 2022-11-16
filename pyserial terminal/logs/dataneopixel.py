import numpy as np
from matplotlib import pyplot as plt

file = open("logs/20221115-2326hrs16sec_serialdata.txt", mode='r')
a = file.readlines()

pixel = '' #22
for i in a:
    if len(i) > 3:
        if i[1] == '2':
            pixel = pixel + i[4:-1]
        



pixel = list(map(int, pixel))


try:
    pixel.remove(2)
except:
    pass



x = np.arange(0,len(pixel))


plt.ylabel("pixel")

plt.plot(x, pixel)

plt.show()
