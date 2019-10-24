#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main (void){
	char cadena [50] = "hola";

	int fd1[2];
	int fd2[2 ];

	pipe(fd1);
	pipe(fd2);

	int valorFork = fork();

	if(valorFork == 0){
		//Estamos en el hijo
		int valorFork1 = fork();

		if(valorFork1 == 0){
			//Estamos en el nieto
			close(fd2[1]);
			close(fd1[0]);

			char cadenaMando [50] = "Mensaje de C a B";
			char cadenaRecibo [50];

			//leemos mensaje del hijo
			read(fd2[0], cadenaRecibo, sizeof(cadenaRecibo));
			printf("\t\tC recibe mensaje de B: %s C\n",cadenaRecibo);

			//Mandamos mensaje a Hijo
			write(fd1[1], cadenaMando, sizeof(cadenaMando));
			printf("\t\tC envía mensaje a B: %s\n", cadenaMando);

		}else{
            //Seguimos en el hijo
      char cadenaMando [50] = "mensaje de B a";
	    char cadenaRecibo [50];

            //Hijo empieza a leer del padre
			read(fd1[0], cadenaRecibo, sizeof(cadenaRecibo));
			printf("\tB recibe mensaje de A: %s\n", cadenaRecibo);

			//Hijo empieza a escribir al nieto
			printf("\tB envía mensaje a C: %s C\n",cadenaMando);
			write (fd2[1], cadenaMando, sizeof(cadenaMando));

			//Hijo lee del nieto
			read(fd1[0], cadenaRecibo, sizeof(cadenaRecibo));
			printf("\tB recibe mensaje de C: %s\n", cadenaRecibo);

            //Hijo empieza a escribir al padre
			printf("\tB envía mensaje a A: %s A\n",cadenaMando);
			write(fd2[1], cadenaMando, sizeof(cadenaMando));
		}
	}else{
		//Estamos en el padre
		close(fd1[0]);
		close(fd2[1]);
		char cadenaMando [50] = "Mensaje de A a B";
		char cadenaRecibo [50];

		write(fd1[1], cadenaMando,sizeof(cadenaMando));
		printf("A envía mensaje a B: %s\n",cadenaMando);
		//padre acaba de escribir

		//Padre empieza a leer
    wait(NULL);
		read(fd2[0], cadenaRecibo, sizeof(cadenaRecibo));
		printf("A recibe mensaje de B: %s A\n",cadenaRecibo);
	}
	wait(NULL);
	return 0;
}
