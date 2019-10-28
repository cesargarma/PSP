#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void menu();

void main() {
    printf("%s", "PID del proceso VEX: ");
    pid_t pidVex;
    scanf("%d", &pidVex);

    while (1) {
        menu(pidVex);
    }
}

void menu(pid_t pidVex){
    int opcion;
    printf("Elija una opción: \n1) Enviar señal Alpha \n2) Enviar señal Beta \nopción: ");
    scanf("%d",&opcion);
    switch (opcion) {
        case -1:
            printf("%s\n", "Algo ha salido mal al introducir el numero;");
            break;
        case 1:
            kill(pidVex, SIGUSR1);
            break;
        case 2:
            kill(pidVex, SIGUSR2);
            break;
        default:
            printf("Algo no ha funcionado correctamente, saliendo...\n");
    }
}
