#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void main() {
  int fd1[2];
  pipe (fd1);
  pid_t pidPadre = getpid();

  int valorFork = fork();

  switch(valorFork){
    case -1:
        printf("Algo ha salido mal en el fork!");
        break;

    case 0:
        //Estamos en el hijo

        break;
    default:
        //Estamos en el padre
        while(1){
          printf("%s\n", "Esperando...");
          sleep(1);
        }
    }
}
