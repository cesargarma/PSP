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
	pipe (fd);

	int valorFork = fork();

	if(valorFork == -1){
		printf("%s\n", "Algo salió mal en el fork)");
	}else{
		if(valorFork == 0){
			//Estamos en el hijo
			close(fd[0]);
			strcat(string, " mijito");
			printf("%s\n", "Hijo escribiendo");
			write(fd[1], string, 50);
			close(fd[1]);
		}else{
			//estamos en el padre
			wait(NULL);
			close(fd[1]);
			printf("%s\n", "Padre leyendo");
			read(fd[0], string, 50);
			printf("%s\n", string);
			close(fd[0]);
		}
	}
	return 0;
}