#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

void main (){
    //char cadena[50] = "";

    int fd1[2];
    pipe (fd1);
    pid_t pidPadre = getpid();

    int valorFork = fork();

    if(valorFork == 0){
        //B1
        //estamos en el hijo
        close(fd1[0]);
        char cadena [30] = "Mensaje de B1 a B2";

        printf("Soy B1, mi pid es %d y el de mi padre es %d, y voy a enviar a B2 el siguiente mensaje: %s\n", getpid(), pidPadre, cadena);

        write(fd1[1], cadena, sizeof(cadena));
        close(fd1[1]);
    }else{
        //Estamos en el padre
        pid_t pidB1 = valorFork;
        valorFork = fork();
        if(valorFork == 0){
            //B2
            //estamos en el segundo hijo
            //FILE * fp = fopen("salida.txt", "w+");
            close(fd1[1]);
            char cadenaRecibo[50];

            read(fd1[0], cadenaRecibo, sizeof(cadenaRecibo));

            printf("Soy B2, mi pid es %d, el pid de mi padre es %d, he recibido el mensaje de B1 que pone: %s\n", getpid(), pidPadre, cadenaRecibo);
            //fprintf(fp, "%s",cadenaRecibo);
            system("echo 'Texto de Relleno' > salida.txt");
            char cadenaImprimir[50];
            sprintf(cadenaImprimir, "echo '%s' > salida.txt", cadenaRecibo);
            system(cadenaImprimir);
            close(fd1[0]);
            //fclose(fp);
        }else{
            //estamos en el padre
            pid_t pidB2 = valorFork;
            wait(NULL);
            printf("Soy A, con pid %d, tengo dos hijos, B1 con pid %d y B2 con pid %d\n", pidPadre, pidB1, pidB2);
        }
    }
}
