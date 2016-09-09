#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int altura[1000000];
int padre[1000000];

void init(int n) {
	for (int i = 0; i < n; i++) {
		altura[i] = 1;
		padre[i] = i;
	}
}

int find(int x) {
	// completar
	if (padre[x] != x) {
		padre[x] = find(padre[x]);
	}
	return padre[x];
}

void uni(int x, int y) {
	// union es una palabra reservada en C++, por eso usamos "uni"
	// completar

	x = find(x);
	y = find(y);
	int aux = 0;
	if (altura[x] > altura[y]) {
		aux = x;
		x = y;
		y = aux;
	} else if (altura[x] == altura[y]) {
		altura[y]++;
	}

	padre[x] = y;

}

struct arista {
	int inicio;
	int fin;
	int costo;
	
	bool operator<(const arista a) const
	{
		if (costo != a.costo)
			return costo > a.costo;
		if (inicio != a.inicio)
			return inicio > a.inicio;
		return fin > a.fin;
	}
};

int main() {
	int V, E;
	cin >> V >> E;
	init (V);
	vector<arista> aristas;
	long long costoTotal = 0;
	for (int i = 0; i < E; i++) {
		arista a;
		cin >> a.inicio >> a.fin >> a.costo;
		costoTotal += a.costo;
		aristas.push_back(a);
	}
	
	sort(aristas.begin(), aristas.end()); // ordeno las aristas por peso de mayor a menor
	int camaraMasCara = -1;
	for (int i = 0; i < E; i++) {
		arista a = aristas[i];
		if (find(a.inicio) != find(a.fin)) {
			costoTotal -= a.costo;
			uni(a.inicio, a.fin);
		} 
		else if (camaraMasCara == -1) {
			camaraMasCara = a.costo;
		}
	}
	
	cout << costoTotal << " " << camaraMasCara << endl;
}
