#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void main(){
  // char * fifo1 = "/mnt/z/DAM2/Inicio/FIFO";
  mkfifo("/mnt/z/DAM2/Inicio/FIFO", 0666);

  int fp;
  char buffer[100];
  char cadena[100];

  while(1){
    fp = open("FIFO1", O_RDONLY);
    //wait(NULL);
    //fgets(buffer,100,stdin);
    read (fp, buffer, sizeof(buffer));

    if(strcmp(buffer, cadena)){
        printf("Mensaje recibido: %s\n", buffer);
        strcpy(cadena, buffer);
    }

    close(fp);
  }
}
