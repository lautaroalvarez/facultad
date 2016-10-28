#include "coloreo.h"
#include "greedy.h"
#include "local.h"
#include <iostream>

int main(int argc, char const *argv[])
{
	grafo g = crear_grafo();
	auto c = greedy_LFS(g);
	cout << c.chi()<<endl;
	/*
	for (int i = 0; i < 10; ++i) {
		mejorar_unir(c);
		cout << c.chi() << endl;
	}
	*/
	for (int i = 0; i < 10; i++) {
		mejorar_onenode(c);
		cout << c.chi() << endl;
	}
	return 0;
}