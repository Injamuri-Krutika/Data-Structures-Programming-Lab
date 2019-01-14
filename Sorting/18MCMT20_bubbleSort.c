#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#define BUFF_SIZE 256
bool isValidNum(char * input){
	int i=0;
	for(i=0;input[i]!='\n'&&input[i]!='\0'&&input[i]!=' ';i++){
		char c=input[i];
		if(!(c>='0'&&c<='9')){
			return false;
		}
	}
	return true;
}

void printArr(int * arr,int size){
	printf("Printing Array after Bubble Sort->");
	for(int i=0;i<size;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");

}

void swap(int * val1,int * val2){
	
	int temp=*val1;
	*val1=*val2;
	*val2=temp;
}
 
int * bubbleSort(int * arr,int size){
	bool swaped=false;
	for(int i=size;i>=0;i--){
		for(int j=0;j<i;j++){
			if(arr[j]>arr[j+1]){
				swap(&arr[j],&arr[j+1]);
				swaped=true;
			}
		}
		if(!swaped)
			break;
	}
	
	return arr;
}

int main(){
	FILE * f =fopen("input.txt","r");
	if(!f){
		perror("File Error");
	}else{
		int j;
		char * lineBuff=(char *)malloc(sizeof(char)*BUFF_SIZE);
		while(fgets(lineBuff,BUFF_SIZE,f)!=NULL){
			printf("%s",lineBuff);
			int k=0,arrSize=0,i=0;
			int * arr;
			char * token1 = strtok(lineBuff, ":");
			bool isValid=false;
			while(token1!=NULL){
				if(!isValidNum(token1)){
					printf("Invalid Array Size\n");
					break;
				}
				arrSize=atoi(token1);
				if(arrSize==0){
					printf("Zero Array Size\n");
					break;
				}
				arr=(int *)malloc(sizeof(int)*arrSize);
				if(k==1){
					char * token2=strtok(token1, " ");
					while(token2!=NULL){
						if(isValidNum(token2)){
							arr[i++]=atoi(token2);
							isValid=true;
						}else{
							isValid=false;
							printf("Invalid Array Values\n");
							break;
						}
						token2=strtok(NULL, " ");
					}
				}
				token1 = strtok(NULL, ":"); 
				k++;
			}
			
			if(arrSize>0 && isValid){
				bubbleSort(arr,arrSize);
				printArr(arr,arrSize);
			}
		}
	}

	return 0;
}
