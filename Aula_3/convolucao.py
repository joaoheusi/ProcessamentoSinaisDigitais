import numpy as np
import matplotlib.pyplot as plt


x = np.zeros(6)
x[3] = 1
h = np.array([0.25, 0.25, 0.25, 0.25])

y = np.convolve(x, h)

length = len(x) + len(h) - 1

n = np.arange(0, length, 1)

plt.stem(n, y)
plt.show()
