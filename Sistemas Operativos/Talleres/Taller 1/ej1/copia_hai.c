#include <unistd.h>
#include <stdio.h>

void sigint() {
	return;
}

void sigurg() {
	return;
}

int main(int argc, char* argv[]) {
	char *asd[] = { };
	
	printf("%s\n", argv[1]);

	execve("/usr/local/sbin/ls",asd,NULL);
	execve("/usr/local/bin/ls",asd,NULL);
	execve("/usr/sbin/ls",asd,NULL);
	execve("/usr/bin/ls",asd,NULL);
	execve("/sbin/ls",asd,NULL);
	execve("/bin/ls",asd,NULL);
	execve("ls",asd,NULL);

	return 0;
}
