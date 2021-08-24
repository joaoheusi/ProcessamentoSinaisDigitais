import matplotlib.pyplot as plt
import numpy as np
import wave
import sys

#Carregar dados
spf = open('amostra_eco.pcm', 'rb')
pcmdata = spf.read()

#De buffer para Array np.int16
a = np.frombuffer(pcmdata,np.int16)

#Array x do comprimento do array lido
x = np.arange(len(a))

#Valor de k

#Plotar gráfico do áudio original
plt.figure( figsize=(20,6))
plt.plot(x, a)
plt.show()

atraso = 500
#transformar array
new_value = 0
new_y = []
for i in range(len(a)):
    if (i-2*atraso) >= 0:
        new_value += 0.5*a[i] + 0.3*a[1-1*atraso] + 0.2*a[i-2*atraso] 
    if (i-1*atraso) >= 0:
        new_value += 0.5*a[i] + 0.3*a[1-1*atraso]
    else:
        new_value = 0.5*a[i]
    
    new_y.append(new_value)
    new_value = 0

#Plotar gráfico do áudio transformado
plt.figure( figsize=(20,6))
plt.plot(x, new_y)
plt.show()

#salvar em um novo arquivo o áudio transformado.
saida_file = open('amostra_eco_com_eco.pcm', 'wb')
scaled = np.int16(new_y)
saida_file.write(scaled.tobytes())
saida_file.close()