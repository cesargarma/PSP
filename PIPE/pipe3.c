#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main (int argc, char* argv){
	pid_t pidTerminal = getppid();
	pid_t pidPadre = getpid();

	char string [50] = "hola";

	int fd [2];
	int fd2 [2];
	pipe (fd);
	pipe (fd2);

	printf("General: %s\n", string);

	int valorFork = fork();

	if(valorFork == -1){
		printf("%s\n", "Algo salió mal en el fork)");
	}else{
		if(valorFork == 0){
			//Estamos en el hijo
			close(fd[0]);
			close(fd2[1]);
			printf("%s\n", "Hijo escribiendo");
			strcat(string, " mijito");
			write(fd[1],string,sizeof(string));
			close(fd[1]);
			//esperamos la respuesta del padre
			//wait(NULL);
			printf("%s\n", "Hijo leyendo");
			read(fd2[0], string, sizeof(string));
			printf("%s %s\n", "Hijo dice: ",string);
			close(fd2[0]);
		}else{
			//estamos en el padre
			//wait(NULL);
			//esperamos al hijo
			close(fd[1]);
			close(fd2[0]);
			printf("%s\n", "Padre leyendo");
			read(fd[0], string, sizeof(string));
			printf("%s %s\n", "Padre dice:",string);
			close(fd[0]);
			//Mandamos mensaje al hijo.
			printf("%s\n", "Padre escribiendo");
			strcat(string, ", te voy a dar.");
			write(fd2[1], string,sizeof(string));
			close(fd2[1]);
		}
	}
}
