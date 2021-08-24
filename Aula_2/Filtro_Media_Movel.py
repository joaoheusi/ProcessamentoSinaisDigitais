import matplotlib.pyplot as plt
import numpy as np
import wave
import sys

#Carregar dados
spf = open('white_noise.pcm', 'rb')
pcmdata = spf.read()

#De buffer para Array np.int16
a = np.frombuffer(pcmdata,np.int16)

#Array x do comprimento do array lido
x = np.arange(len(a))

#Valor de k
k = 32

#Plotar gráfico do áudio original
plt.figure( figsize=(20,6))
plt.plot(x, a)
plt.show()

#transformar array
new_value = 0
new_y = []
for i in range(len(a)):
    for j in range(k):
        if (i-j) >= 0:
            new_value += a[i-j]
    new_value = new_value/k
    new_y.append(new_value)
    new_value = 0

#Plotar gráfico do áudio transformado
plt.figure( figsize=(20,6))
plt.plot(x, new_y)
plt.show()

#salvar em um novo arquivo o áudio transformado.
saida_file = open('white_noise_filtro32.pcm', 'wb')
scaled = np.int16(new_y)
saida_file.write(scaled.tobytes())
saida_file.close()