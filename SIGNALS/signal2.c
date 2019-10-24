#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void main() {
  //int fd1[2];
  //pipe (fd1);

  pid_t pidPadre = getpid();
  int valorFork = fork();

  switch(valorFork){
    case -1:
        printf("Algo ha salido mal en el fork!");
        break;

    case 0:
        //Estamos en el hijo 1
        signal(SIGUSR1, );
        kill(getppid(), SIGUSR1);
        break;
    default:
        //Estamos en el padre
        int valorFork2 = fork();
        switch (valorfork2) {
            case -1:
                printf("Algo ha salido mal en el fork!");
                break;
            case 0:
                //Estamos en el segundo hijo
                signal(SIGUSR2, );
                kill(getppid(), SIGUSR2);
                break;
            default:
                //Seguimos en el padre
                signal(SIGUSR1, );
                signal(SIGUSR2, );
                while(1){
                    sleep(1);
                    kill(valorFork, SIGUSR1);
                    kill(valorFork2, SIGUSR2);
                }
        }
    }
}
