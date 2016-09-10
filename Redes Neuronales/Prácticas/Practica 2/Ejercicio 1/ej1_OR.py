import numpy as np

# x -> Entrada
x_entrada = np.array([[-1, -1], [1, -1], [-1, 1], [1, 1]])

# y -> Resultados
y = np.array([-1, 1, 1, 1])

# Cota de error maximo
E = 0.01
# Maxima cantidad de repeticiones
T = 10000
# Velocidad de aprendizaje
v = 0.1

# agregmos el valor -1 a cada fila (para restar el umbral)
x = np.full( (x_entrada.shape[0], x_entrada.shape[1]+1), -1)
x[:,:-1] = x_entrada;

# inicializamos random las unidades de salida
w = 2 * np.random.random_sample(x.shape[1]) - 1

# inicializamos variables
t = 0
e = E + 1

print("Impresion de errores por estado:")
while (e > E) & (t < T) :
	e = 0
	for i in xrange(len(x)):
		# multiplicamos
		res = np.dot(x[i,:], w.T)

		# aplicamos la funcion de activacion
		if res < 0:
			res = -1
		else:
			res = 1

		# calculamos el error
		err = y[i] - res

		# calculamos el valor del aprendizaje
		dw = v * err * x[i,:]

		# aplicamos el aprendizaje
		w = w + dw

		# acumulamos el error
		e += err ** 2

	# multiplicamos la sumatoria de error por 1/2
	e = e / 2
	# aumentamos el valor de repeticion
	t += 1
	print(str(t)+": "+str(e))

errores = 0
for i in xrange(len(x)):
	res = np.dot(x[i,:], w.T)
	if res < 0:
		res = -1
	else:
		res = 1

	if res != y[i]:
		errores += 1
print("Matriz: ")
print(w[:-1])
print("B (umbral): ")
print(w[len(w)-1])
print("errores: "+str(errores))