import numpy as np

N = 6
M = 4

#--arma el A loco
A = np.random.random_sample(N)

#--inventa una entrada que cumpla el enunciado
entrada = np.empty((N,N))
for i in xrange(0,N):
	entrada[i,:] = np.random.uniform(-A[i], A[i], (1,N))

#--defino una W inicial random 
W = np.random.random_sample((N,M))
dW = np.zeros((N,M))

cant_rep = 1
fact_act = 0.5
while cant_rep < 10:
	for x in entrada:
		fact_act -= fact_act / 2

		y = x.dot(W)

		dW[:] = np.zeros((N,M))
		for i in xrange(0,N):
			for j in xrange(0,M):
				xp = y.dot(W.T)
				dW[i,j] = fact_act * np.array(x[i] - xp[i]).dot(y[j])
		
		W[:] = W + dW
		print "---"+str(cant_rep)
		print W

	cant_rep += 1







#	fact_act = 1 / cant_rep

	#--activacion
#	for x in entrada:
#		yp = np.zeros(M)
#		for i in xrange(0,M):
#			yp[i] = np.linalg.norm(x.T - W[:,i])
#		y = (yp == np.amin(yp))*1

	#--correccion
#	jg = np.nonzero(y)
#	print jg
	#D = np.zeros((N,M))
