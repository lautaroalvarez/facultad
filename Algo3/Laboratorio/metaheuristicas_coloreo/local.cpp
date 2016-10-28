
#include "coloreo.h"
#include <algorithm>
#include "greedy.h"
#include "local.h"

using namespace std;

void mejorar_unir(coloreo& c);
void mejorar_onenode(coloreo& c);
void mejorar_onenode2(coloreo& c);
bool eliminar_conflictos(coloreo& c, int color_libre, int width, int cant_colores);

void mejorar_unir(coloreo& c) {
	if (c.chi() > 2) {	
		coloreo copia(c);
		auto clases = copia.clases();
		sort(clases.begin(), clases.end(), 
			[&](pair<int, vector<int> > c1, pair<int, vector<int> > c2) {
				return c1.second.size() < c2.second.size();
			}
		);
		// pinto los de la clase que menos tiene con el color de la segunda que menos tiene.
		int i = 0;
		bool salir = false;
		int min_col = -1;
		while (i < clases.size() && !salir) {
			if (min_col < 0) {
				min_col = clases[i].second.size();
			}
			if (min_col < clases[i].second.size()) {
				salir = true;
			} else {
				int color_libre = clases[i].first;
				copia.asignar_color(clases[i].second, clases[i+1].first);
				if (eliminar_conflictos(copia, color_libre, copia.n, clases.size())) {
					// recoloreo para que queden colores consecutivos desde 0
					copia.recolorear_consecutivos();
					//FEO!
					c.color = copia.color;
				}
				i++;
			}
			i++;
		}
	}
}

void mejorar_onenode(coloreo& c) {
	coloreo copia(c);
	for (int nodo: c.g.nodes_by_degree()) {
		c.color[nodo] = c.min_color_disponible(nodo);
		if (eliminar_conflictos(copia, color_libre, copia.n, colores_totales)) {
			continue;
		} else {
			copia.color[v] = color_libre;
		}
	}

	copia.recolorear_consecutivos();
	if (copia.chi() < colores_totales) {
		cout << "soy un genio" << endl;
		c.color = copia.color;
	} 
} 
void mejorar_onenode2(coloreo& c) {
	coloreo copia(c);
	int colores_totales = copia.chi();
	for (int v = 0; v < copia.n; ++v) {
		for (int nuevo_color = 0 ; nuevo_color < colores_totales; ++nuevo_color) {
			int color_libre = copia.color[v];
			copia.color[v] = nuevo_color;
			if (eliminar_conflictos(copia, color_libre, copia.n, colores_totales)) {
				continue;
			} else {
				copia.color[v] = color_libre;
			}
		}
	}
	copia.recolorear_consecutivos();
	if (copia.chi() < colores_totales) {
		cout << "soy un genio" << endl;
		c.color = copia.color;
	} 
} 


bool eliminar_conflictos(coloreo& c, int color_libre, int max_intentos, int cant_colores) {
	int intentos = 0;
	auto conflictos = c.nodos_conflictivos();
	int cant_conflictos = conflictos.size();
	while (cant_conflictos > 0 && intentos < max_intentos) {
		// para cada nodo parte de un conflicto: v
		for (auto v : conflictos) {
			int conflictos_v = c.nodos_conflictivos(v).size();
			// si sigue teniendo conflictos
			if (conflictos_v> 0) { 
				// para cada color que le puedo poner a v,
				// pruebo cual es el que mas me reduce la cantidad de conflictos
				for (int nuevo_color = 0; nuevo_color < cant_colores; nuevo_color++) {
					if (nuevo_color != color_libre && nuevo_color != c.color[v]) {
						int color_anterior = c.color[v];
						c.color[v] = nuevo_color;
						int conflictos_ahora = c.nodos_conflictivos(v).size();
						if (conflictos_ahora < conflictos_v) {
							// me lo quedo
							conflictos_ahora = conflictos_v;
						} else {
							// revierto
							c.color[v] = color_anterior;
						}
					}
				}
			}
		}
		conflictos = c.nodos_conflictivos();
		cant_conflictos = conflictos.size();
		intentos++;
	}
	return cant_conflictos == 0;
}
