#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_INPUT_SIZE 256
int compare(const void *a, const void *b)
{
    const char **X = (const char **)a;
    const char **Y = (const char **)b;
    int len = strlen(*X) + strlen(*Y) + 1;
    char XY[len];
    strcpy(XY, *X);
    strcat(XY, *Y);
    char YX[len];
    strcpy(YX, *Y);
    strcat(YX, *X);
    return strcmp(YX, XY);
}

bool validateInput(char* input){
	int i;
	for(i=0;input[i]!='\0' && input[i]!='\n' ;i++){
		char c=input[i];
		if(!(c>='0'&&c<='9')){
      printf("%c\n",c );
			return false;
		}
	}
	return true;
}

void readAndSortArr(){
  char ** arr = malloc(10 * sizeof(char*));
  FILE * fp;
  fp=fopen("inputFile.txt""","r");
  if(fp!=NULL){
    char * intArrPointer=malloc(sizeof(int)*MAX_INPUT_SIZE);
		char character;
		char lineBuffer[MAX_INPUT_SIZE*2];
		while((fgets(lineBuffer,MAX_INPUT_SIZE*2,fp))!=NULL){
      for (int i =0 ; i < 10; ++i)
          arr[i] = malloc(20 * sizeof(char));
			printf("%s",lineBuffer);
			int charLength=0,finalArrSize=0;
			char intCharacter[MAX_INPUT_SIZE]={};
			bool isInvalid=false;
			for(int k=0;lineBuffer[k-1]!='\n';k++){
				if(lineBuffer[k]!=',' && lineBuffer[k]!='\n'){
					intCharacter[charLength]=lineBuffer[k];
					charLength++;
				}else{
					intCharacter[charLength]='\0';
					if(validateInput(intCharacter)){
            strcpy(arr[finalArrSize],intCharacter);
							finalArrSize++;
              printf("%s\n", intCharacter);
					}else{
						printf("Invalid input values\n" );
						isInvalid=true;
						break;
					}
          charLength=0;
				}
			}
			if(isInvalid!=true)
	    qsort(arr, finalArrSize, sizeof(arr[0]), compare);
        int n = sizeof(arr)/sizeof(arr[0]);
      for (int i = 0; i < finalArrSize ; i++ )
          printf("%s", arr[i]);
          printf("\n<<<<--------------------------------------->>>>\n" );
          for (int i = 0; i < finalArrSize ; i++ )
            free(arr[i]);
		}
		fclose(fp);
  }else{
    perror("File not found");
  }
}

int main(void)
{
    readAndSortArr();
    return 0;
}
