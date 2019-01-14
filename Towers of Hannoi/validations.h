#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


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
