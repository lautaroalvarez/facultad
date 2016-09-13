import numpy as np
import math, csv



# y0 =	[1 1 -1]

# w1 =	[1 1]
# 		[1 1]
# 		[1 1]

# y1 =	[1 1]

# w2 =	[1]
# 		[1]

# y2 =	[1]




#---------Funcion de activacion Logistica----------
#def funcion_activacion(entrada):
#	beta = 0.1
#	res = entrada
#	for i in xrange(0, len(res)):
#		res[i] = 1 / (1 + math.exp(beta * res[i]))
#	return res

#def derivada_funcion_activacion(entrada):
#	beta = 0.1
#	fentr = funcion_activacion(entrada)
#	res = beta * fentr * (1 + fentr)
#	return res
#--------------------------------------------------
def funcion_activacion(entrada):
	beta = 0.1
	return 1 / (1 + math.exp(-beta * entrada))
def derivada_funcion_activacion(entrada):
	beta = 0.1
	fentr = funcion_activacion(entrada)
	return beta * fentr * (1 - fentr)



def activacion(entrada):
	#---Propaga y calcula las respuestas
	salida = np.zeros((cant_capas+1, 3))
	salida[0] = entrada
	#print "capas"
	#print capas
	for i in xrange(0, cant_capas):
		salida[i+1] = salida[i].dot(capas[i+1].T)
		for j in xrange(0, dimensiones_y[i+1]):
				salida[i+1][j] = funcion_activacion(salida[i+1][j])
	#print "salida"
	#print salida
	return salida

def correccion(y, z):
	#---Calcula y acumula errores dw
	E = z - y[cant_capas]
	e = np.sum(np.power(E,2))
	for i in xrange(cant_capas, 0, -1):
		#print "--------------IIII-----------"
		#print i
		#print "E"
		#print E
		#print "y[i-1]"
		#print y[i-1]
		#print "capas[i].T"
		#print capas[i].T
		auxDer = y[i-1].dot(capas[i].T)
		for j in xrange(0, dimensiones_y[i]):
			auxDer[j] = derivada_funcion_activacion(auxDer[j])
		#print "auxDer"
		#print auxDer
		D = np.multiply(E, auxDer)
		delta_capas[i] = delta_capas[i] + coef_aprendizaje * D.dot(y[i-1])
		#print "delta_capas[i]"
		#print delta_capas[i]
		E = D.dot(capas[i])
	return e

def adaptacion():
	#---Adapta usando los dw y resetea estos dw
	for k in xrange(1, cant_capas+1):
		#print "--k"
		#print k
		#print delta_capas[i]
		for i in xrange(0, dimensiones_capas[k][0]):
			#print "----i"
			#print i
			for j in xrange(0, dimensiones_capas[k][1]):
				#print "------j"
				#print j
				#print "capas[k][i][j]"
				#print capas[k][i][j]
				#print "delta_capas[k]"
				#print delta_capas[k]
				capas[k][i][j] = capas[k][i][j] + delta_capas[k]
		delta_capas[i] = 0
	return

def training(csv_salida):
	cant_rep = 20000
	h = 0
	error = 2
	while h < cant_rep and error > ERR:
		error = 0
		for ei in xrange(0, len(x)):
			y = activacion(x[ei])
			error = error + correccion(y, z[ei])
			adaptacion()
		if h % 3 == 0:
			csv_salida.writerow([h, error])
			print h, error
		h = h + 1
	return error

csv_salida = csv.writer(open("ej1_1.csv", "wb"))

#---ENTRADA
x = np.array([[0, 0, -1], [0, 1, -1], [1, 0, -1], [1, 1, -1]])
z = np.array([[0, 0, 0], [1, 0, 0], [1, 0, 0], [0, 0, 0]])

#---PARAMETROS
coef_aprendizaje = 0.1
cant_capas = 2
ERR = 0.02

capas = np.random.randn(cant_capas+1, 3, 3)
delta_capas = np.zeros((cant_capas+1))
dimensiones_capas = np.array([[0, 0], [2, 3], [1, 2]])

dimensiones_y = np.array([3, 2, 1])


for k in xrange(0, cant_capas+1):
	for i in xrange(dimensiones_capas[k][0], 3):
		for j in xrange(0, 3):
			capas[k][i][j] = 0
	for j in xrange(dimensiones_capas[k][1], 3):
		for i in xrange(0, 3):
			capas[k][i][j] = 0

err = training(csv_salida)

print "-----------------------"
print "---FIN ENTRENAMIENTO---"
print "error:"
print err

cant_errores = 0
for i in xrange(0, len(x)):
	resp = activacion(x[i])
	if ((resp[2][0] - z[i][0])**2 >= ERR):
		cant_errores = cant_errores + 1
if cant_errores == 0:
	print "ENTRENAMIENTO OK!"
else:
	print "ERRORES:"
	print cant_errores