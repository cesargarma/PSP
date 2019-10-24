#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void main (){
    int fd1[2];
    pipe (fd1);
    pid_t pidPadre = getpid();

    int numLeido = -1;
    int num;

    int i = 0;

    int valorFork = fork();

    switch(valorFork){
        case -1:
            printf("Algo ha salido mal en el fork!");
            break;

        case 0:
            //Estamos en el hijo
            wait(NULL);

            read(fd1[0], &numLeido, sizeof(numLeido));

            for(i = 0; i < numLeido; i++){
                printf("Iteracción %d\n",i+1);
            }
            break;

        default:
            //Estamos en el padre
            close(fd1[0]);

            printf("Dame un número, mierdecillas: ");

            scanf("%d",&num);

            printf("\n");

            write(fd1[1], &num, sizeof(num));
            close(fd1[1]);
    }
    wait(NULL);
}
