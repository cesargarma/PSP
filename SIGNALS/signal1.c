#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void funcion();
void noMuere();
void muere();

void main() {
  int fd1[2];
  pipe (fd1);
  pid_t pidPadre = getpid();

  int valorFork = fork();

  signal(SIGINT, noMuere);

  switch(valorFork){
    case -1:
        printf("Algo ha salido mal en el fork!");
        break;

    case 0:
        //Estamos en el hijo
        //signal(SIGINT, noMuere);
        while(1){
          //ENVIAMOS SEÑAl
          sleep(3);
          kill(getppid(), SIGUSR1);
        }
        break;
    default:
        //Estamos en el padre
        signal(SIGUSR1, funcion);
        //signal(SIGINT, noMuere);
        while(1){
            //ESPERANDO SEÑAL
            printf("%s\n", "Esperando...");
            sleep(1);
        }
        funcion();
    }
}


void funcion (){
    printf("Jaja, te interrumpo, soy %d \n", getpid());
}

void noMuere(){
    printf("Pues no me da la gana morirme, por ceirto, soy %d\n", getpid());
    signal(SIGINT, muere);
}

void muere(){
    printf("%s\n", "Bueno, igual si que me muero");
    exit(1);
}
