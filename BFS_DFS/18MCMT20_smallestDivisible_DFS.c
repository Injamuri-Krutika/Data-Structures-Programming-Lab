#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#define MAX_BUFFER_SIZE 100

int count=1000;
int input;
int arr[5000],i=0;
int DFS(int value){
	if(count>0 && value<9000000){
		if(value%input==0){
			arr[i++]=value;
		}else{
			DFS(value*10+0);
			DFS(value*10+9);
		}
	}else{
		return 0;
	}
		count--;
}


bool validateInput(char* input){
	int i;
	if(input[0]==' '||input[0]=='\n')
		return false;

	for(i=0;input[i]!='\n'&&input[i]!=' ';i++){
		char c=input[i];
		if(!(c>='0'&&c<='9')){
			return false;
		}
	}
	return true;
}
int main(){
FILE * file=fopen("inputFile1.txt","r");
bool isValid=false;
if(file){
	char lineBuffer[MAX_BUFFER_SIZE*2];
	    while((fgets(lineBuffer,MAX_BUFFER_SIZE*2,file))!=NULL){
				printf("%s",lineBuffer);
	      if(validateInput(lineBuffer)){
					input=atoi(lineBuffer);

			i=0;
			for(int j=0;j<5000;j++){
				arr[j]=0;
			}
			DFS(9);
			int smallest=INT_MAX;
			for(int j=0;j<i;j++){
				if(smallest>arr[j])
					smallest=arr[j];
			}
			printf("arr[i] %d\n",smallest);
		}else{
			printf("Invalid Input\n");
		}

	}
}
else{
	perror("No File Found");
}
}
