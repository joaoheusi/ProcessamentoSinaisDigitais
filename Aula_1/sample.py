import matplotlib.pyplot as plt
import numpy as np
from basicSigns import sinus_wave
plt.style.use("dark_background")



f = 0.7

# ampliacao amostragem
Fa = 30

x1 = np.arange(-10.,10.,0.1)
y1 = sinus_wave(x1,f)

plt.figure(figsize=(12,4))
plt.subplot(2,1,1)
plt.title("Amostrando um sinal senoidal")
plt.plot(x1,y1)

# Amostrando

x2 = np.arange(-1.,1.,1/Fa)
y2 = sinus_wave(x2,f)
plt.subplot(2,1,2)
plt.stem(x2,y2)


plt.show()