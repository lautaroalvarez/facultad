#include <iostream>
#include <queue>
#include <string>
using namespace std;

int componente[2001], n, m;
bool vecinos[2001][2001];
const int INF = 1000000000;
string out[2001];

// BFS devuelve si todos los nodos fueron alcanzables desde nodo_inicial o no
bool bfs (int nodo_inicial, bool trasp) {
	bool posible = true;
	for (int i = 0; i < n; i++)
		componente[i] = INF;

	queue<int> cola;
	cola.push(nodo_inicial);
	componente[nodo_inicial] = 0;

	while (!cola.empty()) {
		int t = cola.front();
		cola.pop();

		for (int i = 0; i < n; i++) {
			if ( ((!trasp && vecinos[t][i]) || (trasp && vecinos[i][t])) && componente[i] == INF) {
				componente[i] = 0;
				cola.push(i);
			}
		}
	}

	for (int i = 0; i < n; i++)
		if (componente[i] == INF)
			posible = false;

	return posible;
}

int main () {
	int v, w, p;
	int cant = 0;
	while ((cin >> n >> m) && !(n == 0 && m == 0)) {
		// limpio la matriz de vecinos
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				vecinos[i][j] = false;

		// armo la matriz de adyacencias
		for (int i = 0; i < m; i++) {		
			cin >> v >> w >> p;
			v--; w--;
			vecinos[v][w] = true;
		
			if (p == 2)
				vecinos[w][v] = true;
		}

        if (bfs(0, false) && bfs(0, true)) {
        	out[cant] = "1";
        } else {
        	out[cant] = "0";
        }
        cant++;
	}

	for (int i = 0; i < cant; i++) {
		cout << out[i] << endl;
	}
}
