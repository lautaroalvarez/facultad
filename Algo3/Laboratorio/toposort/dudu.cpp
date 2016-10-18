#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct nodo {
	bool marcado;
	int ingrade;

	vector<int> hijos;
};

int main() {
	int T;
	int N;
	int M;
	cin >> T;
	string out[T];

	for (int i = 0; i < T; ++i) {
		cin >> N >> M;
		nodo nodos[N+1];
		
		for (int j = 1; j <= N; j++) {
			nodos[j].marcado = false;
			nodos[j].ingrade = 0;
		}

		for (int j = 0; j < M; j++) {
			int a, b;
			cin >> a >> b;
			nodos[b].ingrade++;
			nodos[a].hijos.push_back(b);
		}

		int cant = 0;
		bool hay_ciclo = false;
		while (!hay_ciclo && cant < N) {
			int min = 0;
			int j = 1;
			while (min == 0 && j <= N) {
				if (!nodos[j].marcado && nodos[j].ingrade == 0) {
					min = j;
				}
				j++;
			}
			if (min == 0) {
				hay_ciclo = true;
			} else {
				nodos[min].marcado = true;
				for (int k = 0; k < nodos[min].hijos.size(); k++) {
					nodos[nodos[min].hijos.at(k)].ingrade--;
				}
				cant++;
			}
		}

		if (hay_ciclo) {
			out[i] = "SIM";
		} else {
			out[i] = "NAO";
		}
	}

	for (int i = 0; i < T; i++) {
		cout << out[i] << endl;
	}

	return 0;
}