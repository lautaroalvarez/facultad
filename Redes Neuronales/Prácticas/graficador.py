import matplotlib.pyplot as plt
import csv
import sys
import numpy as np

#-----Formato esperado
#	1, 1928731823
#	2, 98172389712893
#---------------------

inputFile = sys.argv[1]
outputFile = sys.argv[2]

entrada = csv.reader(open(inputFile, "rb"))

datos = np.empty((0,2))
for row in entrada:
	datos = np.append(datos, np.array([row]), axis=0)

#plt.yscale('log')
plt.plot(datos[:,0], datos[:,1], marker='o', linestyle = ':')
plt.xlabel("Estado")
plt.ylabel("Error")
plt.title("Grafico de convergencia del error")
plt.legend()
plt.savefig(outputFile)