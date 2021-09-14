import matplotlib.pyplot as plt
import numpy as np
import wave
import sys

#Carregar dados
spf = open('two_sins.pcm', 'rb')
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


#coefs array
data = []

with open('Coefs_PB_1k.dat', 'r') as f:
    d = f.readlines()
    for i in d:
        data.append(float(i)) 

print (data)
#transformar array
new_value = 0
new_y = []

for i in range(len(a)):
    for c in range(len(data)):
        new_value += data[c] * a[i-c]
    new_y.append(new_value)
    new_value =0 

print(new_y)
#Plotar gráfico do áudio transformado


#salvar em um novo arquivo o áudio transformado.
saida_file = open('two_sins_saida.pcm', 'wb')
scaled = np.int16(new_y)
saida_file.write(scaled.tobytes())
saida_file.close()