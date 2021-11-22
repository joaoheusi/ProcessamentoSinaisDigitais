import matplotlib.pyplot as plt
import numpy as np
import wave
import sys



def pulse_sign(sample, value,power):
    pulse = np.zeros_like(sample)
    for p,tp in enumerate(sample):
        if tp == value:
            pulse[p] = 1*power
    return pulse

#Array x do comprimento do array lido
x = np.arange(0,25000,1)

#De buffer para Array np.int16
a  = pulse_sign(x,5000,1)

#Valor de k
k = 4

#Plotar gráfico do áudio original
plt.figure( figsize=(20,6))
plt.stem(x, a)
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
plt.stem(x, new_y)
plt.show()


#salvar em um novo arquivo o áudio transformado.
entrada_file = open('unitario.pcm','wb')
saida_file = open('unitario_filtro16.pcm', 'wb')
scaled_entrada = np.int16(a)
scaled = np.int16(new_y)
entrada_file.write(scaled_entrada.tobytes())
saida_file.write(scaled.tobytes())
entrada_file.close()
saida_file.close()