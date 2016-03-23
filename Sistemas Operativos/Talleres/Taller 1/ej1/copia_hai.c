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

	execve('/usr/local/sbin/',argv[1],asd,asd);
	execve('/usr/local/bin/',argv[1],asd,asd);
	execve('/usr/sbin/',argv[1],asd,asd);
	execve('/usr/bin/',argv[1],asd,asd);
	execve('/sbin/',argv[1],asd,asd);
	execve('/bin/',argv[1],asd,asd);
	execve(argv[1],asd,asd);

	return 0;
}
