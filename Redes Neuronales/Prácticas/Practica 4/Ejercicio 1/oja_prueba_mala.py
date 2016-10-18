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

cant_rep = 1
while cant_rep < 100:
	fact_act = 1 / cant_rep
	for x in entrada:
		y = x.dot(W)
		dW = np.zeros((N,M))

		for j in xrange(0,M):
			xp = np.zeros(N)
			for i in xrange(0,N):
				for k in xrange(0,M):
					xp[i] = y[k] * W[i,k]
				dW[i,j] = fact_act * (x[i] - xp[i]) * y[j]
		W += dW
	cant_rep += 1


