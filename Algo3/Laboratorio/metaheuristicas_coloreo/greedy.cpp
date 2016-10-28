
#include "coloreo.h"
#include "greedy.h"
#include <iostream>
#include <algorithm>

coloreo greedy_secuencial_1aN(grafo& g) {
	coloreo c(g, -1);
	vector<int> nodos(g.n());
	iota(nodos.begin(), nodos.end(), 0);
	c.colorear_secuencial(nodos);
	return c;
}

coloreo greedy_random(grafo& g) {
	vector<int> nodos(g.n());
	iota(nodos.begin(), nodos.end(), 0);
	random_shuffle(nodos.begin(), nodos.end());
	coloreo c(g, -1);
	c.colorear_secuencial(nodos);
	return c;
}

coloreo greedy_LFS(grafo& g) {
	coloreo c(g, -1);
	vector<int> nodos = g.nodes_by_degree();
	c.colorear_secuencial(nodos);
	return c;
}
