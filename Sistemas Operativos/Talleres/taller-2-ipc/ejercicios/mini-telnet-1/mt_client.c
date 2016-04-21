#include "mt.h"

int main(int argc, char* argv[]) {
	struct in_addr			ip;
    int						socket_fd;
    char                	buf[MAX_MSG_LENGTH];
    struct sockaddr_in		direccion;


	if (argc == 1) {
		printf("Debe ingresar la ip del servidor.\n");
		return 1;
	}

	//guardamos ip
	if (inet_aton(argv[1], &ip) == 0) {
		perror("IP inválida.");
		exit(1);
	}
    
    //crea servidor
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("creando socket");
        exit(1);
    }

    //setea direccion
    direccion.sin_family = AF_INET;
    direccion.sin_port = htons(PORT);
    direccion.sin_addr = ip;

    //se conecta
	if (connect(socket_fd, (struct sockaddr*)&direccion, sizeof(direccion)) == -1) {
		perror("Error al iniciar la connexión.");
		exit(1);
	}

	//envia lo escrito
    while(printf("> "), fgets(buf, MAX_MSG_LENGTH, stdin), !feof(stdin)) {
    	if (strcmp(buf,END_STRING) == 0) {
    		break;
    	}
        if (send(socket_fd, buf, strlen(buf), 0) == -1) {
            perror("enviando");
            exit(1);
        }
    }

	close(socket_fd);

    return 0;
}
