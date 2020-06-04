import numpy as np
import matplotlib.pyplot as plt


x = np.linspace(0, 20, 100)


plt.plot(x, np.sin(x), 'purple') #Los argumentos como 'o' o 's' o 'o g' afectan al color de la gráfica mostrada
#plt.ylim(-0.5,0.5)  #Argumentos para definir la altura del gráfico
plt.show()