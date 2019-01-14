#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_INPUT_SIZE 256
bool isFloatingPoint=false;
bool validateInput(char* input);

void exchange(int * val1,int * val2){
	int temp=*val1;
	*val1=*val2;
	*val2=temp;
}



void reverse(int firstIndex,int lastIndex, int * arr){
	if(firstIndex>=0){
		int mid=(lastIndex-firstIndex)/2;
		for(int i=firstIndex;i<=mid;i++)
		exchange(&arr[i],&arr[lastIndex-i]);
	}else{
		int mid=(lastIndex+firstIndex)/2;
		for(int i=0;i<=mid;i++)
		exchange(&arr[i+-1*firstIndex],&arr[lastIndex-i]);
	}


}

void rotate(int number,int sizeOfArray,int * arr){

	if(number<0)
	reverse(number,sizeOfArray-1,arr);
	else
	reverse(0,sizeOfArray-number-1,arr);

	reverse(0,sizeOfArray-1,arr);
	for(int i=0;i<sizeOfArray;i++)
	printf("%d ",arr[i]);

	printf("\n<<-------------------------------->>\n");

}





bool validateInput(char* input){
	int i;
	if(input[0]=='\n')
	return false;
	for(i=0;input[i]!='\n';i++){
		char c=input[i];
		if(!(c>='0'&&c<='9')){
			return false;
		}
	}
	return true;
}


bool validatInputPosNeg(char* input){

	if(input[0]=='-'){
		if(validateInput(input+1)==true)
		return true;
		else
		return false;
	}else{
		return validateInput(input);
	}

}
void readAndProcessInputFile(){
	FILE * fp;
	fp=fopen("inputFile.txt""","r");
	if(fp!=NULL){
		int rotation;
		int * intArrPointer=malloc(sizeof(int)*MAX_INPUT_SIZE);
		char character;
		char lineBuffer[MAX_INPUT_SIZE*2];
		while((fgets(lineBuffer,MAX_INPUT_SIZE*2,fp))!=NULL){
			printf("%s",lineBuffer);
			int k=0;
			char intCharacter[MAX_INPUT_SIZE]={},charLength=0;
			int * finalIntArr=malloc(sizeof(int)*MAX_INPUT_SIZE);
			int finalArrSize=0;
			bool isInvalid=false;
			for(k=0;lineBuffer[k-1]!='\n';k++){

				int i;
				if(lineBuffer[k]!='|' && lineBuffer[k]!=' ' && lineBuffer[k]!='\n'){
					intCharacter[charLength]=lineBuffer[k];
					charLength++;
				}else{
					intCharacter[charLength]='\n';
					charLength=0;
					if(validatInputPosNeg(intCharacter)){
						if(lineBuffer[k]=='|'){
							rotation=atoi(intCharacter);
						}
						else{
							finalIntArr[finalArrSize]=atoi(intCharacter);
							finalArrSize++;
						}
					}else{
						printf("Invalid input values\n" );
						printf("<<<------------------------------------------>>>\n" );
						isInvalid=true;
						break;
					}

				}


			}

			for (size_t i = 0; i < finalArrSize; i++) {
				printf("%d ", finalIntArr[i]);
			}
			printf("\n" );
			if(isInvalid!=true)
			if(finalArrSize<rotation){
				printf("Rotation is greater than number of array elements\n");
				printf("<<<--------------------------------------------->>>\n");

			}else{

				rotate(rotation,finalArrSize,finalIntArr);
			}

		}

		fclose(fp);
	}else{
		perror("File Not Found");
	}

}


int main(){
	readAndProcessInputFile();
}
