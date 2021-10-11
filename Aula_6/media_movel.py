import numpy as np
import matplotlib.pyplot as plt

FS = 8000
W = np.arange(np.pi / 1000, np.pi, np.pi / 1000)


def Resp_Freq(W, L):
    yAxis = (abs(1/L * ((np.sin((W * L) / 2)) / np.sin(W / 2))))
    return yAxis

plt.subplot(4, 1, 1)
plt.plot(W, Resp_Freq(W, 4))

plt.subplot(4, 1, 2)
plt.plot(W, Resp_Freq(W, 8))

plt.subplot(4, 1, 3)
plt.plot(W, Resp_Freq(W, 16))

plt.subplot(4, 1, 4)
plt.plot(W, Resp_Freq(W, 32))
plt.show()