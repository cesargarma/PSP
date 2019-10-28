#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void alpha();
void beta();
void decrementar();
void cerrar();

int contadorAlpha = 0;
int contadorBeta = 0;

void main() {

    signal(SIGUSR1, alpha);
    signal(SIGUSR2, beta);
    signal(SIGINT, decrementar);

    printf("Mi pid es %d\n", getpid());

    while (1) {
        printf("\n%s", "La red vex se encuentra operativa.");
        sleep(1);
    }
}

void alpha(){
    contadorAlpha += 1;
    printf("Atención: señal alpha recibida (%d)\n", contadorAlpha);
}

void beta(){
    contadorBeta += 1;

    if(contadorAlpha < 5){
        printf("ACCESO DENEGADO\n");
    }else{
        printf("Fallo en el sistema, la próxima señal alpha recibida cerrará el proceso.\n");
        signal(SIGUSR1, cerrar);
    }
}

void decrementar(){
    contadorAlpha-=1;
}

void cerrar(){
    exit(1);
}
