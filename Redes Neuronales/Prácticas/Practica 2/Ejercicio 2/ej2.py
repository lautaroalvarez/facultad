import sys, csv
import numpy as np

inputFile = sys.argv[1]

x_entrada = []
y = []
row = []

dataFile = open(inputFile)
for linea, texto in enumerate(dataFile):
	texto = texto.strip()
	if linea % 7 == 5:
		x_entrada.append(row)
		row = []
		for valor in texto:
			row.append(int(valor))
		y.append(row)
		row = []
	elif linea % 7 < 5:
		for valor in texto:
			row.append(int(valor))

x_entrada = np.array(x_entrada)
y = np.array(y)

print(x_entrada.shape)
print(y.shape)


# Cota de error maximo
E = 0.01
# Maxima cantidad de repeticiones
T = 20000
# Velocidad de aprendizaje
v = 0.1

beta = 0.01

# agregmos el valor -1 a cada fila (para restar el umbral)
x = np.full( (x_entrada.shape[0], x_entrada.shape[1]+1), -1)
x[:,:-1] = x_entrada;

# inicializamos random las unidades de salida
w = 2 * np.random.random_sample((x.shape[1], y.shape[1])) - 1

# inicializamos variables
t = 0
e = E + 1


salida = csv.writer(open("ej2.csv", "wb"))

sal_plot = np.empty((0,2));

print("Impresion de errores por estado:")
while (e > E) & (t < T) :
	e = 0
	dw = 0
	for i in xrange(len(x)):
		# multiplicamos
		res = np.dot(x[i,:], w)

		# aplicamos la funcion de activacion
		res = np.tanh(beta * res)

		# calculamos el error
		err = y[i] - res

		# calculamos el valor del aprendizaje
		dw = v * np.dot(np.array([x[i,:]]).T, np.array([err]))

		# aplicamos el aprendizaje
		w = w + dw

		# acumulamos el error
		e += np.sum(err ** 2)

	# multiplicamos la sumatoria de error por 1/2
	e = e / 2
	# aumentamos el valor de repeticion
	t += 1
	print(str(t)+": "+str(e))
	salida.writerow([t, e])
	sal_plot = np.append(sal_plot, np.array([[t,e]]), axis=0);


errores = 0
for i in xrange(len(x)):
	res = np.dot(x[i,:], w)
	res = np.tanh(beta * res)
	print(res)

	if np.sum( (y[i] - res) ** 2) > 0.1:
		errores += 1

print("Matriz: ")
print(w[:-1])
print("B (umbral): ")
print(w[len(w)-1])
print("errores: "+str(errores))