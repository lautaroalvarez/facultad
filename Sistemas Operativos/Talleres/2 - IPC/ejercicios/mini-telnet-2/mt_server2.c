#include "mt.h"

int main(int argc, char* argv[]) {
    int                 sock;
    struct sockaddr_in  name;
    char                buf[MAX_MSG_LENGTH];
    int					conexion;
    struct sockaddr_in  remote;
    int					hijo;
    int					pipe_padre[2];
    int					size_msg;
    FILE *fp;

    /* Crear pipe de comunicación con el padre */
    pipe(pipe_padre);

    /* Crear socket sobre el que se lee: dominio INET, protocolo TCP (SOCK_STREAM). */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("abriendo socket");
        exit(1);
    }

    /* Crear nombre, usamos INADDR_ANY para indicar que cualquiera puede enviar aquí. */
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = INADDR_ANY;
    name.sin_port = htons(PORT);

    if (bind(sock, (void*) &name, sizeof(name))) {
        perror("binding datagram socket");
        exit(1);
    }

    /* Escuchar en el socket y permitir 5 conexiones en espera. */
    if (listen(sock, 5) == -1) {
        perror("escuchando");
        exit(1);
    }

    for (;;) {
	    int t = sizeof(remote);
    	/* Aceptar una conexión entrante. */
	    if ((conexion = accept(sock, (struct sockaddr*) &remote, (socklen_t*) &t)) == -1) {
	        perror("aceptando la conexión entrante");
	        exit(1);
	    }
		hijo = fork();
		if (hijo == 0) {
			break;
		}
    }

    //codigo del hijo
    close(pipe_padre[0]);
    /* Recibimos mensajes hasta que alguno sea el que marca el final. */
    for (;;) {
        memset(buf, 0, MAX_MSG_LENGTH);
    	size_msg = recv(conexion, buf, MAX_MSG_LENGTH, 0);
        if (size_msg < 0) { 
        	perror("recibiendo");
        	exit(1);
        }

        if (strncmp(buf, END_STRING, MAX_MSG_LENGTH) == 0)
            break;
        printf("Comando: %s", buf);

		/* Open the command for reading. */
		fp = popen(buf, "r");
		if (fp == NULL) {
			printf("Failed to run command\n" );
			exit(1);
		}

		/* Read the output a line at a time - output it. */
		while (fgets(buf, sizeof(buf)-1, fp) != NULL) {
			printf("%s", buf);
			int t = sizeof(remote);
			sendto(conexion, buf, MAX_MSG_LENGTH, 0, (struct sockaddr*) &remote, (socklen_t) t);
		}
		/* close */
		pclose(fp);
        
        //system(buf);
    }

    close(pipe_padre[1]);
    /* Cerrar socket de recepción. */
    //close(sock);

    return 0;
}
