#include <regex.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_INPUT_SIZE 256
bool isFloatingPoint=false;
bool validateInput(char* input);

//unsigned long convertStringToInt(char * inputVal);
int main(){
char * value=malloc(sizeof(char)*MAX_INPUT_SIZE);

	//int num;
	if(value==NULL){
		perror("Malloc Error");
	}else{
		do{
			printf("Enter a Natural Number\n");
			fgets(value,MAX_INPUT_SIZE,stdin);
				
		}while(!validateInput(value));
		
/*		char * value1=malloc(sizeof(char)*MAX_INPUT_SIZE);
		sprintf(value1,"%u",SHRT_MAX);	
printf("%s",value1);
		if(sprintf(value1,"%u",SHRT_MAX)>=*value){
			short input=(short)*value;
			int sum=input*(input)/2;
			printf("Sum is %d\n",sum);

		}else if(sprintf(value1,"%u",USHRT_MAX)>=*value){
			unsigned short input=atoi(value);
			unsigned int sum=input*(input)/2;
			printf("Sum is %u\n",sum);
		}else if(sprintf(value1,"%u",INT_MAX)>=*value){
			int input=(int)*value;
			long sum=input*(input)/2;
			printf("Sum is %ld\n",sum);

		}else if(sprintf(value1,"%u",UINT_MAX)>=*value){
			unsigned int input=(unsigned int)strtoul(value,NULL,10);;
			unsigned long sum=input*(input)/2;
			printf("Sum is %lu\n",sum);
		}else if(sprintf(value1,"%lu",LONG_MAX)>=*value){
			long input=(long)strtoul(value,NULL,10);
			unsigned long int sum=input*(input)/2;
			printf("Sum is %ld\n",sum);

		}else if(sprintf(value1,"%lu",ULONG_MAX)>=*value){
			unsigned long input=strtoul(value,NULL,10);
			unsigned long long sum=input*(input)/2;
			printf("Sum is %llu\n",sum);
		}*/
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
		
		if((c>='0'&&c<='9')||(c=='.'&&!isFloatingPoint)){
			if(c=='.')
				isFloatingPoint=true;
		}else{
			isFloatingPoint=false;
			return false;	
		}
	}
	if(isFloatingPoint){
		char* p=strchr(input,'.');
		int indexOfPoint=(int)(p-input);
		if(indexOfPoint==(strlen(input)-2))
			return false;
	}
	
	if(strtoul(input,NULL,10)>0)
		return true;
}

/*bool validateInput(char* input){
        regex_t regex;
        int reti;
        char msgbuf[100];

//Compile regular expression 
        reti = regcomp(&regex, "^[0-9]+(\\.[0-9]+)?\n$", REG_EXTENDED);
        if( reti ){ fprintf(stderr, "Could not compile regex\n"); exit(1); }

// Execute regular expression 
        reti = regexec(&regex, input, 0, NULL, 0);
        if( !reti ){
		if(strtoul(input,NULL,10)>0)
			return true;
		else{
			fprintf(stderr,"%s","Entered value is wrong. Please re-enter the NATURAL NUMBER\n");
			return false;
		}
		
        }
        else if( reti == REG_NOMATCH ){
		fprintf(stderr,"%s","Entered value is wrong. Please re-enter the value\n");
		return false;
        }
        else{
                regerror(reti, &regex, msgbuf, sizeof(msgbuf));
                fprintf(stderr, "Regex match failed: %s\n", msgbuf);
                exit(1);
        }

// Free compiled regular expression if you want to use the regex_t again 
	regfree(&regex);

        return 0;
}*/
