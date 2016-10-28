# python random_col n d
# n = cant. nodos, d = densidad (0.0 nodos aislados, 1.0 grafo completo)

from random import uniform
from collections import defaultdict

def generate_random_graph(n, d):
	g = {}
	for v in range(n):
		g[v] = []
		for w in range(v+1, n):
			if uniform(0,1) <= d:
				g[v].append(w)
	return g

def print_header():
	print "c RANDOM PY GRAPH"

def print_graph(g):
	m = sum(map(len, g.itervalues()))
	print "p edge", len(g), m
	for v in g:
		for w in g[v]:
			print "e", v+1, w+1

def generate_and_print(n, d):
	print_header()
	print_graph(generate_random_graph(n, d))

if __name__ == '__main__':
	from sys import argv
	generate_and_print(int(argv[1]), float(argv[2]))
