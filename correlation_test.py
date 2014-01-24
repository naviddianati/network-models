import numpy as np
import matplotlib.pyplot as plt
N = 10000
x = np.linspace(0,10,N)
y = np.sin(3*(x+np.random.rand(N)/10))
plt.plot(x,y)
plt.show()



#~ print np.random.rand(1,10000)

print x