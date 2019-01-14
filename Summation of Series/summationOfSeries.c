#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#define MAX_INPUT_SIZE 256

bool validateInput(char* input);
char stringVal[MAX_INPUT_SIZE];
double doubleValue;
float floatVal;
int integerVal;
long longVal;
unsigned long convertStringToInt(char * inputVal);
int main(){
	char * value=malloc(sizeof(char)*MAX_INPUT_SIZE);
	int num;
	if(value==NULL){
		perror("Malloc Error");
	}else{
		do{
			printf("Enter a Natural Number\n");
			fgets(value,MAX_INPUT_SIZE,stdin);

	printf("Length of string %ld",strlen(value));
	//printf("Integer Value %lu",convertStringToInt(value));
			/*printf("%d\n",value);
			printf("%f\n",value);
			printf("%l\n",value);
			printf("%lf\n",value);
			printf("%s\n",value);*/
				
		}while(!validateInput(value));
		return 0;
	}
		
}

unsigned long convertStringToInt(char * s){
	unsigned double integerVal=0;
	short i=0;
	short length=strlen(s)-1;

	for(i=0;s[i]>='0' && s[i]<='9';i++){
		integerVal=integerVal*10+(*s-'0');
	}
	if(s[i]='.'){
	 	for(i+=1;s[i]>='0' && s[i]<='9';i++){
			integerVal=integerVal*10+(*s-'0');
		}	
	}
		

	
return integerVal;
}


bool validateInput(char* input){
	if(isdigit(*input)){
		printf("is a digit\n");
	
if(*input<SHRT_MAX){
	printf("Input :: %s Max SHort:: %d",input,SHRT_MAX);
	printf("inside short max");
}
	
	}else{
		printf("is a not digit\n");
	}
		printf("size of input: %lu\n",sizeof(input));	
	if((sscanf(input,"%s",stringVal))==1){
		printf("input is string\n");
	} if((sscanf(input,"%f",&floatVal))==1){
		printf("input is float %f \n",floatVal);
	} if((sscanf(input,"%d",&integerVal))==1){
		printf("input is integer %d \n",integerVal);
	} if((sscanf(input,"%ld",&longVal))==1){
		printf("input is long %ld\n",longVal);
	}
return true;
} 
