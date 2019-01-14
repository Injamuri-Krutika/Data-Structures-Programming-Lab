#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MAX_INPUT_SIZE 256
bool isFloatingPoint=false;
unsigned long long fib(unsigned long number){
	  int f1=0,f2=1,f;
	  do{
	  f=f1+f2;
	  f1=f2;
	  f2=f;
	  number--;
	  }while(number>1);
	  return f;
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

int main(){
char * value=malloc(sizeof(char)*MAX_INPUT_SIZE);
char * option=malloc(sizeof(char));
	//int num;
	if(value==NULL){
		perror("Malloc Error");
	}else{	
		int val;
		do{
			printf("Welcome to Fibonacci!! Choose one of the below: \n Press 1 to evaluate with Max value in fibonacci sequence. \n\tOR\n Press 2 to choose number of values in sequence \n");
			fgets(option,MAX_INPUT_SIZE,stdin);
			val=atoi(option);
		}while(!(validateInput(option)&& val==1 || val==2));		
		
		if(val==1){
			do{
			printf ("Enter Max val fib  sequence to be printed\n");
			fgets(value,MAX_INPUT_SIZE,stdin);
				
			}while(!validateInput(value));

			printf("Fibannoci Series is :: ");
			unsigned long input=strtoul(value,NULL,10),i=1;
			int fibValue;
			while((fibValue=fib(i++))<=input){
				printf("%llu ",fibValue);
			}
			
		}else{	
			do{
			printf ("Enter number of numberof fib  sequence to be printed\n");
			fgets(value,MAX_INPUT_SIZE,stdin);
				
			}while(!validateInput(value));

			printf("Fibannoci Series is :: ");
			unsigned long input=strtoul(value,NULL,10),i;
			for(i=0;i<=input;i++)
				if(i!=0)
					printf("%llu ",fib(i));
		}
		
		
		printf("\n");
	}

}


