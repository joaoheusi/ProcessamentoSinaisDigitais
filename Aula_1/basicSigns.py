import matplotlib.pyplot as plt
import numpy as np
plt.style.use("dark_background")


def sinus_wave(sample, freq):
    pi = np.pi
    sinus = np.cos(2*pi*sample*freq)
    return sinus


def step_sign(sample, start, finish,power):
    step = np.zeros_like(sample)
    for s,ts in enumerate(sample):
        if ts >= start and ts <= finish:
            step[s] = 1*power
    return step

def pulse_sign(sample, value,power):
    pulse = np.zeros_like(sample)
    for p,tp in enumerate(sample):
        if tp == value:
            pulse[p] = 1*power
    return pulse

def exp_sign(sample,const,a):
    exp = np.zeros_like(sample)
    for e,te in enumerate(sample):
        exp[e]= (const * a)**te
    return exp

if __name__ == "__main__":


    plt.figure(figsize=(12,9))
    x1 = np.arange(0,10,1)
    y1 = pulse_sign(x1,3,1)
    plt.subplot(4,1,1)
    plt.title("Aula 2 - Sinais Discretos Basicos\nImpulso Unitário, Degrau Unitário,Sequencia Sinusoidal, Sequencia Exponencial")
    plt.stem(x1,y1)



    
    x2 = np.arange(0,10,0.001)
    y2 = step_sign(x2,2,np.inf,1)
    plt.subplot(4,1,2)
    plt.plot(x2,y2)


    x3 = np.arange(0,1,1/8000)
    y3 = sinus_wave(x3,100)
    plt.subplot(4,1,3)
    plt.plot(x3,y3)



    x4 = np.arange(0.,30.,0.5)
    y4 = exp_sign(x4,1,0.5)
    #y4_2 = exp_sign(x4,1,-0.5)
    #y4_3 = exp_sign(x4,1,2)
    plt.subplot(4,1,4)
    plt.stem(x4,y4)
    #plt.stem(x4,y4_2)
    #plt.stem(x4,y4_3)

    plt.show()