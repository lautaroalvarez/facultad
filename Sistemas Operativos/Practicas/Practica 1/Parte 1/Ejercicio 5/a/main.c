#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	printf("Soy el abuelo Abraham.\n");
	pid_t padre = fork();
	if (padre == -1) {
		printf("Hubo un error al intentar hacer fork.\n");
	} else if (padre == 0) {
		printf("Soy el padre Homer\n");
		pid_t hijo = fork();
		if (hijo == -1) {
			printf("Hubo un error al intentar hacer fork.\n");
		} else if (hijo == 0) {
			printf("Soy el hijo Bart\n");
		} else {
			pid_t hija = fork();
			if (hija == -1) {
				printf("Hubo un error al intentar hacer fork.\n");
			} else if (hija == 0) {
				printf("Soy la hija Lisa\n");
			} else {
				pid_t hija2 = fork();
				if (hija2 == -1) {
					printf("Hubo un error al intentar hacer fork.\n");
				} else if (hija2 == 0) {
					printf("Soy la hija Maggie\n");
				}
			}
		}
	}
	return 0;
}