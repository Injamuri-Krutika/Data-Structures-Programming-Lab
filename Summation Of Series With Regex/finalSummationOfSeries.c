#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_INPUT_SIZE 256
bool isFloatingPoint=false;
bool validateInput(char* input);
int main(){
char * value=malloc(sizeof(char)*MAX_INPUT_SIZE);

	if(value==NULL){
		perror("Malloc Error");
	}else{
		do{
			printf("Enter a Natural Number\n");
			fgets(value,MAX_INPUT_SIZE,stdin);
				
		}while(!validateInput(value));		

		unsigned long inputVal=strtoul(value,NULL,10);
		if(inputVal<=USHRT_MAX){
			unsigned int sum=0;
			sum=inputVal*(inputVal+1)/2;
			printf("Sum is %u\n",sum);
		} else if(inputVal<=UINT_MAX){
			unsigned long sum=0;
			sum=inputVal*(inputVal+1)/2;
			printf("Sum is %lu\n",sum);
		}else if(inputVal<=ULONG_MAX){
			unsigned long long sum =0;
			sum=inputVal*(inputVal+1)/2;
			printf("Sum is %llu\n",sum);
		}else{
			perror("Input is out of Range.");
			
		}
		exit(0);

		return 0;
	}
		
}

bool validateInput(char* input){
	int i;
	for(i=0;input[i]!='\n';i++){
		char c=input[i];
		
		if(!(c>='0'&&c<='9')){
			return false;
		}
	}
	
	if(strtoul(input,NULL,10)>0)
		return true;
}
