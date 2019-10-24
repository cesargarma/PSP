#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void main(){
  // char * fifo1 = "/mnt/z/DAM2/Inicio/FIFO";
  mkfifo("/mnt/z/DAM2/Inicio/FIFO", 0666);

  int fp;
  char buffer[100] = "buenas";

  while(1){
    fp = open("FIFO1", O_WRONLY);

    fgets(buffer,100,stdin);
    //wait(NULL);
    write (fp, buffer, sizeof(buffer));
    close(fp);
  }
}
