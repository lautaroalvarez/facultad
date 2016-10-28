#ifndef COLOR_LOCAL
#define COLOR_LOCAL
#include "coloreo.h"

using namespace std;

void mejorar_unir(coloreo& c);
void mejorar_onenode(coloreo& c);
void mejorar_onenode2(coloreo& c);
bool eliminar_conflictos(coloreo& c, int color_libre, int width, int cant_colores);

#endif
