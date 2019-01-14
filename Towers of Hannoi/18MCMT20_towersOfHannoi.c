#include <stdio.h>
#include <stdlib.h>
#include "validations.h"
#define MAX_BUFFER_SIZE 256
void towersOfHannoi(int numberOfElements,char fromRod,char toRod,char usedRod) {
  if(numberOfElements>1){
    towersOfHannoi(numberOfElements-1,fromRod,usedRod,toRod);
    printf("Move disk number %d from rod %c to rod %c \n",numberOfElements,fromRod,toRod );
    towersOfHannoi(numberOfElements-1,usedRod,toRod,fromRod);
  }else{
    printf("Move disk number %d from rod %c to rod %c \n",numberOfElements,fromRod,toRod );
  }

}

void readAndProcessInputFile(){

  FILE * fp;
  int disks;
  fp=fopen("inputFile.txt","r");
  if(fp!=NULL){
    char lineBuffer[MAX_BUFFER_SIZE*2];
    while((fgets(lineBuffer,MAX_BUFFER_SIZE*2,fp))!=NULL){
      printf("%s",lineBuffer );
      if(validateInput(lineBuffer)){
        disks=atoi(lineBuffer);
        towersOfHannoi(disks, 'A', 'C', 'B');  // A, B and C are names of rods
      }else{
        printf("Invalid number of disks\n" );
      }
      printf("<<<------------------------------------------>>>\n" );
    }
  }else{
    perror("File Not Found");
  }

  fclose(fp);
}


int main(){
  readAndProcessInputFile();
  return 0;
}
