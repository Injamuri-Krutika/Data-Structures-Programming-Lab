#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#define MAX_BUFF_SIZE 256

typedef struct Element{
int i,j,value;
}Element;

typedef struct QueueElement{
Element element;
struct QueueElement * next;
}QueueElement;

typedef struct Queue{
QueueElement * front, * rear;
}Queue;

Queue * createQueue(){
	Queue * queue=(Queue *)malloc(sizeof(Queue));
	queue->front=queue->rear=NULL;
}


QueueElement * enQueue(Queue * queue, QueueElement * new){
	if (queue->rear == NULL){
       queue->front = queue->rear = new;
    }else{
			queue->rear->next = new;
	    queue->rear = new;
		}
	return new;
}


QueueElement * deQueue(Queue * queue){
	if (queue->front == NULL)
       return NULL;

	 struct QueueElement *temp = queue->front;
    queue->front = queue->front->next;

		if (queue->front == NULL)
		       queue->rear = NULL;
		    return temp;

}
Element * createNewElement(int i,int j,int val){
	Element * newElement =(Element *)malloc(sizeof(Element));
	newElement->i=i;
	newElement->j=j;
	newElement->value=val;
	return newElement;
}

QueueElement * createNewQueueElement(Element element){
	QueueElement * new =(QueueElement *)malloc(sizeof(QueueElement));
	new->element=element;
	new->next=NULL;
	return new;
}


QueueElement * insertInQueueIfNotVisited(Element * element,Queue * queue,int * visited,int size){
	int k=element->i;
	int l=element->j;
	int val=element->value;
	if(*((visited+k*size) + l)==0){
		*((visited+k*size) + l)=1;
		QueueElement * new=createNewQueueElement(*createNewElement(k,l,val));
		return enQueue(queue,new);
	}
	return queue->rear;

}


Element * findSourceIndex(int size,int * matrix){
	for(int i =0; i<size;i++){
		for(int j =0; j<size;j++){
			int val=*((matrix+i*size) + j);
			if(val==1){
				return createNewElement(i,j,val);
			}
		}
	}
}

Element * down(int size,int i,int j,int * matrix){
	int val=*((matrix+i*size) + (j+1));
	if((j+1)<size && val!=0 ){
		return createNewElement(i,j+1,val);
	}
	return NULL;
}

Element * left(int size,int i,int j,int * matrix){
	int val=*((matrix+(i)*size) + (j-1));
	if((j-1)>=0 && val!=0 ){
		return createNewElement(i,j-1,val);
	}
	return NULL;
}

Element * right(int size,int i,int j,int * matrix){
	int val=*((matrix+(i+1)*size) + j);
	if((i+1)<size && val!=0 ){
		return createNewElement(i+1,j,val);
	}
	return NULL;
}

Element * up(int size,int i,int j,int * matrix){
	int val=*((matrix+(i-1)*size) + j);
	if((i-1)>=0 && val!=0 ){
		return createNewElement(i-1,j,val);
	}
	return NULL;
}

void BFS(Element * source,int * matrix,int size){
int visited[size][size];
for(int i=0;i<size;i++){
	for(int j=0;j<size;j++){
		visited[i][j]=0;
	}
}

Queue * queue=createQueue();
bool foundDest=false;
Element * current=source;
visited[source->i][source->j]=1;
printf("Path Traversing: [i,j] values :\n" );
	while(current){
		printf("value :: %d, i :: %d,j :: %d\n",current->value,current->i,current->j );
		Element * leftElement = left(size,current->i,current->j,(int *)matrix);
		Element * rightElement = right(size,current->i,current->j,(int *)matrix);
		Element * downElement = down(size,current->i,current->j,(int *)matrix);
		Element * upElement = up(size,current->i,current->j,(int *)matrix);
		if(leftElement){
			if(leftElement->value==2){
				printf("Yes\n");
				foundDest=true;
				break;
			}
			insertInQueueIfNotVisited(leftElement,queue,(int *)visited,size);
		}
		if(rightElement){
			if(rightElement->value==2){
				printf("Yes\n");
				foundDest=true;
				break;
			}
			insertInQueueIfNotVisited(rightElement,queue,(int *)visited,size);

		}
		if(downElement){
			if(downElement->value==2){
				printf("Yes\n");
				foundDest=true;
				break;
			}
			insertInQueueIfNotVisited(downElement,queue,(int *)visited,size);
		}
		if(upElement){
			if(upElement->value==2){
				printf("Yes\n");
				foundDest=true;
				break;
			}
			insertInQueueIfNotVisited(upElement,queue,(int *)visited,size);

		}
		free(current);
		current=&(queue->front->element);
		deQueue(queue);

	}
	if(foundDest==false)
		printf("No\n");
}
bool validateInput(char* input){
	int i;
	for(i=0;input[i]!='\n'&&input[i]!=' ';i++){

		char c=input[i];
		if(!(c>='0'&&c<='3')){
			return false;
		}
	}
	return true;
}
int main(){
FILE * file=fopen("inputFile.txt","r");
bool isValid=false;
if(file){
	char * lineBuffer=(char *)malloc(sizeof(char)*MAX_BUFF_SIZE);
	int * matrix;
	int index1=0,count=0,N=0,numberOfRowsCompleted=0;
	while(fgets(lineBuffer,MAX_BUFF_SIZE,file)!=NULL)//used to read a line of size MAX_BUFF_SIZE from file
	{
		if(count!=0)
			numberOfRowsCompleted++;
		int numberOfInputsInRow=0,index2=0;
		for(int i=0;lineBuffer[i]!='\n';i++){
			if(count==0){
				N=atoi((char *)&lineBuffer[i]);
				matrix=(int *)malloc(sizeof(int)*N*N);
			}else{
				if(lineBuffer[i]!=' ' && validateInput((char *)&lineBuffer[i]) && numberOfInputsInRow<N){
						*(matrix+index1*N+index2)=atoi((char *)&lineBuffer[i]);
						index2++;
						numberOfInputsInRow++;
						isValid=true;
				}else if(numberOfInputsInRow>=N){
					printf("Number of elements in row are greater than size\n");
					isValid=false;
					break;
				}else if(lineBuffer[i]==' '){
					continue;
				}else{
					printf("Worng input format\n");
					isValid=false;
					break;
				}
			}

		}
		if(count!=0)
			index1++;
		count++;
		if(numberOfRowsCompleted == N){
			if(isValid){
				Element * source = findSourceIndex(N,matrix);
				BFS(source,matrix,N);
			}
			index1=count=N=numberOfRowsCompleted=0;
		}

	}
	// if(isValid){
	// 	Element * source = findSourceIndex(N,matrix);
	// 	BFS(source,matrix,N);
	// }

}else{
	perror("No File Found");
}
}
