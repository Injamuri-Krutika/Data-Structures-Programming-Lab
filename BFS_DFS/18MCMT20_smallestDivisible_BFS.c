#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#define MAX_BUFFER_SIZE 100

typedef struct QueueElement{
int  value;
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


QueueElement * createNewQueueElement(int value){
	QueueElement * new =(QueueElement *)malloc(sizeof(QueueElement));
	new->value=value;
	new->next=NULL;
	return new;
}

void BFS(int input){
  int i=0;
  Queue * queue=createQueue();
  QueueElement * qElement=createNewQueueElement(9);
  enQueue(queue,qElement);
  for(int count=INT_MAX;count>0;count--){
    int element1 =(deQueue(queue))->value;
			if(element1%input==0){
		    printf("Smallest number divisible by input %d is %d\n", input,element1);
		    break;

		  }
        QueueElement * qElement1=createNewQueueElement(element1*10+0);
        QueueElement * qElement2=createNewQueueElement(element1*10+9);
        enQueue(queue,qElement1);
        enQueue(queue,qElement2);
        i++;
  }
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
int input;
char lineBuffer[MAX_BUFFER_SIZE*2];
if(file)
		while((fgets(lineBuffer,MAX_BUFFER_SIZE*2,file))!=NULL){
			printf("%s",lineBuffer);
			if(validateInput(lineBuffer)){
				input=atoi(lineBuffer);

		BFS(input);

	}else{
		printf("Invalid Input\n");
	}

}
else{
	perror("No File Found");
}
}
