import numpy as np
from typing import Any, List


def pcm_to_nparray(pcm_filename: str) -> np.array:
    # Carregar arquivo de entrada
    pcm_file = pcm_filename+".pcm"
    spf = open(pcm_file, 'rb')
    pcmdata = spf.read()
    pcmarray = np.frombuffer(pcmdata, np.int16)
    return pcmarray


def nparray_to_pcm(pcmdata: np.array, filename: str) -> None:
    """
    Creates a new .pcm file from an np.array
    """
    new_file = filename+".pcm"
    output_file = open(new_file, 'wb')
    scaled = np.int16(pcmdata)
    output_file.write(scaled.tobytes())
    output_file.close()
    return None


def coefs_to_list(coefs_filename: str) -> List[Any]:
    coefs_file = coefs_filename+".txt"
    coefs_list = []
    with open(coefs_file, 'r') as f:
        d = f.readlines()
        for i in d:
            coefs_list.append(float(i))
    return coefs_list


# Lê arquivo de entrada
pcm_data = pcm_to_nparray("white_noise_8k")

# Lê arquivo dos coeficientes
coefs_list = coefs_to_list("mm_coefs")
# Cria vetor dos coeficientes fir adaptativo
fir_coefs_list = np.zeros(len(coefs_list))

# Inicializa D
accurate_pcm = []
accurate_pcm_value = 0

# Inicializa Erro
error_pcm = np.zeros(len(pcm_data))


# Inicializa Saída FIR adaptativo
new_pcm = []
new_pcm_value = 0
stepsize = 0.000000005

# Loop Exterior
for i in range(len(pcm_data)):

    # Loop D
    for c in range(len(coefs_list)):
        accurate_pcm_value += coefs_list[c]*pcm_data[i-c]
    accurate_pcm.append(accurate_pcm_value)
    accurate_pcm_value = 0

    # Loop FIR
    for f in range(len(fir_coefs_list)):
        new_pcm_value += fir_coefs_list[f]*pcm_data[i-f]
    new_pcm.append(new_pcm_value)
    new_pcm_value = 0

    # Atribuição do erro
    error_pcm[i] = accurate_pcm[i] - new_pcm[i]
    # Ajuste dos coeficientes FIR
    for coef_i in range(len(fir_coefs_list)):
        if(i-coef_i) >= 0:
            fir_coefs_list[coef_i] = (fir_coefs_list[coef_i]
                                      + (stepsize * error_pcm[i] * pcm_data[i-coef_i]))
    # print(fir_coefs_list)

# Saida do filtro FIR
nparray_to_pcm(new_pcm, "white_noise_8k_out_fir")

# Saida D - média movel
nparray_to_pcm(accurate_pcm, "white_noise_8k_out_mm")
