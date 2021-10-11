import numpy as np
import matplotlib.pyplot as plt
from matplotlib import patches

xAxis = [1, 0, -1]
yAxis = [1, -1, 0]

ax = plt.subplot(111)
uc = patches.Circle((0, 0), radius=1, fill=False, color='black', ls='dashed')
ax.add_patch(uc)

Zeros = np.roots(xAxis)
Poles = np.roots(yAxis)

t1 = plt.plot(Zeros.real, Zeros.imag, 'go', ms=10)
plt.setp(t1, markersize=10.0, markeredgewidth=1.0, markeredgecolor='k', markerfacecolor='g')

t2 = plt.plot(Poles.real, Poles.imag, 'rx', ms=10)
plt.setp(t2, markersize=12.0, markeredgewidth=3.0, markeredgecolor='r', markerfacecolor='r')

ax.spines['left'].set_position('center')
ax.spines['bottom'].set_position('center')
ax.spines['right'].set_visible(False)
ax.spines['top'].set_visible(False)

r = 1.2
plt.axis('scaled')
plt.axis([-r, r, -r, r])
ticks = [-1, -.75, -.5, -.25, 0,.25,.5, .75,1]
plt.xticks(ticks)
plt.yticks(ticks)

plt.show()

