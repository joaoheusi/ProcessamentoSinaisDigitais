from pylab import *
import scipy.signal as signal

#Plot frequency and phase response
def mfreqz(b,a=1):
    w,h = signal.freqz(b,a)
    h_dB = 20 * log10 (abs(h))
    figure(figsize=(8, 6), dpi=160)
    subplot(211)
    plot(w/max(w),h_dB)
    ylim(-150, 5)
    ylabel('Magnitude (db)')
    xlabel(r'Normalized Frequency (x$\pi$rad/sample)')
    title(r'Frequency response')
    subplot(212)
    h_Phase = unwrap(arctan2(imag(h),real(h)))
    plot(w/max(w),h_Phase)
    ylabel('Phase (radians)')
    xlabel(r'Normalized Frequency (x$\pi$rad/sample)')
    title(r'Phase response')
    subplots_adjust(hspace=1)
    plt.show()

#Plot step and impulse response
def impz(b,a=1):
    l = len(b)
    impulse = repeat(0.,l); impulse[0] =1.
    x = arange(0,l)
    response = signal.lfilter(b,a,impulse)
    subplot(211)
    stem(x, response)
    ylabel('Amplitude')
    xlabel(r'n (samples)')
    title(r'Impulse response')
    subplot(212)
    step = cumsum(response)
    stem(x, step)
    ylabel('Amplitude')
    xlabel(r'n (samples)')
    title(r'Step response')
    subplots_adjust(hspace=0.5)
    plt.show()


Fs = int(44100)
Fc = int(6000)
BW = int(100)

normal_BW = BW/Fs

M = 4/normal_BW
M = int(M)
lowerh = signal.firwin(
    M,
    6000,
    window='hamming',
    fs=Fs
) 

upperh = signal.firwin(
    M,
    4000,
    window='hamming',
    fs=Fs
) 

upperh_n = np.zeros(upperh.shape)
upperh_n[upperh_n.size//2] = 1 
upperh_n = upperh_n - upperh

new_h = np.convolve(lowerh,upperh_n,mode="same")

with open('PassaFaixa4k_6k.txt','w') as f:
  for i in new_h:
    f.write(str("{:.9f}\n".format(i)))

mfreqz(new_h)