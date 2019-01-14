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
	printf("Printing Array after Merge Sort->");
	for(int i=0;i<size;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");

}

void merge(int * arr,int l,int m,int r){

	int i=0,j=0,k=l;
	int n1=m-l+1;
	int n2=r-m;
	int L[n1],R[n2];
	for(int p=0;p<n1;p++){
		L[p]=arr[l+p];
	}
	for(int p=0;p<n2;p++){
		R[p]=arr[m+1+p];
	}
	
	while(i < n1 && j < n2){
		if(L[i]<=R[j]){
			arr[k]=L[i++];
		}else{
			arr[k]=R[j++];
		}
		k++;
	}

	while (i < n1) 
	        arr[k++] = L[i++]; 
       
  
   
	while (j < n2) 
		arr[k++] = R[j++]; 
}

 
int * mergeSort(int * arr,int low,int high){
	
	if(high>low){
		int mid=(low+high)/2;
		mergeSort(arr,low,mid);
		mergeSort(arr,mid+1,high);
		merge(arr,low,mid,high);
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
				mergeSort(arr,0,arrSize);
				printArr(arr,arrSize);
			}
		}
	}

	return 0;
}
