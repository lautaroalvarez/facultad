#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int status;
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
			printf("Termina Bart.\n");
			return 0;
		} else {
			pid_t hija = fork();
			if (hija == -1) {
				printf("Hubo un error al intentar hacer fork.\n");
			} else if (hija == 0) {
				printf("Soy la hija Lisa.\n");
				printf("Termina Lisa.\n");
				return 0;
			} else {
				pid_t hija2 = fork();
				if (hija2 == -1) {
					printf("Hubo un error al intentar hacer fork.\n");
				} else if (hija2 == 0) {
					printf("Soy la hija Maggie.\n");
					printf("Termina Maggie.\n");
					return 0;
				} else {
					waitpid(hijo, &status, 0);
					waitpid(hija, &status, 0);
					waitpid(hija2, &status, 0);
					printf("Termina Homer.\n");
					return 0;
				}
			}
		}
	} else {
		waitpid(padre, &status, 0);
		printf("Termina Abraham.\n");
	}
	return 0;
}