#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>  /* pid_t */
#include <sys/wait.h>   /* waitpid */
#include <unistd.h>     /* exit, fork */

int run(char *program_name[], char **program_argv[], unsigned int count) {
    pid_t child[count];
    int num_proc = 0;
    int soyhijo = 0;
    int pipes[count][2];
    char buf[1024];
    //char buf_sal[1024];
    char *newenviron[] = { NULL };
    
    while (num_proc < count && soyhijo == 0) {
        //creo un nuevo pipe
        if (pipe(pipes[num_proc]) < 0) {
            perror("pipe");
        }

        //creo un nuevo proceso
        child[num_proc] = fork();
        if (child[num_proc] == 0) {
            soyhijo = 1;
        } else {
            num_proc++;
        }
    }
    if (soyhijo == 1) {
        printf("Soy el hijo %d\n", num_proc);
        if (num_proc > 0) {
            dup2(0, pipes[num_proc-1][0]);
            if (read(pipes[num_proc-1][0], buf, 1024) < 0) {
                perror("leyendo datos");
            }
        }
        printf("Pude pasar. Soy el hijo %d\n", num_proc);

        dup2(pipes[num_proc][1], 1);
        execve(program_name[num_proc], program_argv[num_proc], newenviron);
        /*if (write(pipes[num_proc][1], buf_sal, sizeof(buf_sal)) < 0) {
            perror("escribiendo datos");
        }*/
    } else {
        printf("Soy el padre\n");
        if (read(pipes[count-1][0], buf, 1024) < 0) {
            perror("leyendo datos");
        }
        printf("Llega: %s\n", buf);
    }

    return 0;
}

int main(int argc, char* argv[]) {
    /* Parsing de "ls -al | wc | awk '{ print $2 }'" */
    char *program_name[] = {
        "/bin/ls",
        "/usr/bin/wc",
        "/usr/bin/awk",
    };

    char *ls_argv[] = {"ls", "-al", NULL};
    char *wc_argv[] = {"wc", NULL};
    char *awk_argv[] = {"awk", "{ print $2 }", NULL};

    char **program_argv[] = {
        ls_argv,
        wc_argv,
        awk_argv,
    };

    unsigned int count = 2;

    int status = run(program_name, program_argv, count);

    printf("[+] Status : %d\n", status);

    return 0;
}
