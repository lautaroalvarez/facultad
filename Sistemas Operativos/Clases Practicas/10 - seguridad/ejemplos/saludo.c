#include <stdio.h>

void saludo(void) {
    char nombre[80];

    printf("Ingrese su nombre completo: ");
    gets(nombre);
    printf("Hola, %s!\n", nombre);
}

int main(int argc, char* argv[]) {
    saludo();

    return 0;
}
