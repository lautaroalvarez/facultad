#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void sigint_hijo() {
	printf("sigurg del hijo\n");
}
void sigint_padre() {
	printf("sigurg del padre\n");
}

void sigurg() {
	return;
}

int main(int argc, char* argv[]) {
	char *asd[1];
	asd[0] = argv[1];


	pid_t child = fork();
	if (child == -1) { perror("ERROR fork"); return 1; }
	if (child == 0) {
		/* Sólo se ejecuta en el Hijo */
		struct sigaction sa_padre;
		sa_padre.sa_flags = SA_RESTORER|SA_RESTART;
		sigemptyset(&sa_padre.sa_mask);
		sa_padre.sa_sigaction = sigint_padre;

		if (sigaction(SIGURG, &sa_padre, NULL) == -1)
			perror("error en sigaction sigint padre");
		//execvp(argv[1], argv+1);
		/* Si vuelve de exec() hubo un error */
		//perror("ERROR child exec(...)"); exit(1);
	} else {
		/* Sólo se ejecuta en el Padre */
		struct sigaction sa_hijo;
		sa_hijo.sa_flags = SA_RESTORER|SA_RESTART;
		sigemptyset(&sa_hijo.sa_mask);
		sa_hijo.sa_sigaction = sigint_hijo;
		
		if (sigaction(SIGINT, &sa_hijo, NULL) == -1)
			perror("error en sigaction sigint hijo");
		//while(1) {
		//if (wait(&status) < 0) { perror("waitpid"); break; }
		//	if (WIFEXITED(status)) break; /* Proceso terminado */
		//}
	}


	execve("/usr/local/sbin/ls",asd, argv);
	execve("/usr/local/bin/ls",asd, argv);
	execve("/usr/sbin/ls",asd, argv);
	execve("/usr/bin/ls",asd, argv);
	execve("/sbin/ls",asd, argv);
	execve("/bin/ls",asd, argv);
	execve("ls",asd, argv);

	return 0;
}
