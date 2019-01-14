#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#define MAX_INPUT_SIZE 256
typedef struct Node{
	int val;
	struct Node * left;
	struct Node * right;
}Node;

typedef struct CircularQ{
	struct Node * front;
	struct Node * rear;
	int size;
}CircularQ;
CircularQ * createCQ(int size){
	CircularQ * cq=(CircularQ *)malloc(sizeof(CircularQ));
	cq->front=cq->rear=NULL;
	cq->size=size;
}
Node *createNewNode(int val){
	Node * new=(Node *)malloc(sizeof(Node));
	new->val=val;
	new->right=NULL;
	return new;
}

void printQ(CircularQ * cq,Node * temp){
	if(!temp)
		temp=cq->front;
	int size=cq->size;
	while(temp && size>0){
		printf("%d ",temp->val);
		if(size>1)
		printf("->");
		temp=temp->right;
		size--;
	}
	printf("\n" );
}

void enQ(Node * new,CircularQ * cq){

	if(!cq->rear){
		cq->front=cq->rear=new;
		new->right=cq->front;
		new->left=cq->rear;
	}
	else{
		cq->rear->right=new;
		new->right=cq->front;
		new->left=cq->rear;
		cq->front->left=new;
		cq->rear=new;

	}

}

int generateRandomNumber(int low,int high){
	srand(time(NULL));
	int rand=(rand%high-low)+low;
	return rand;
}
Node * deleteNode(int pos,CircularQ * cq){
	int i=pos;
	Node * temp=cq->front;
	printQ(cq,NULL);
	while(i>0){
//		printf("%d\n",i);
		temp=temp->right;
		i--;
	}
	Node * prev=temp->left;
	Node * next=temp->right;
	prev->right=temp->right;
	next->left=temp->left;
	if(pos==cq->size -1){
		cq->rear=prev;
	}
	if(pos==0){
		cq->front=next;
	}
	printf("Element deleted %d\n",temp->val );
	Node * node=temp->right;
	free(temp);


	--cq->size;
	return node;


}

bool validateInput(char* input){
	int i;
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
int main(){
	char * value=malloc(sizeof(char)*MAX_INPUT_SIZE);
//generateRandomNumber(0,10);
	int num;
	do{
		printf("Enter a valid number for size of the Queue\n");
		fgets(value,MAX_INPUT_SIZE,stdin);
	}while(!validateInput(value) || atoi(value)==0);
	num=atoi(value);
	CircularQ * cq=createCQ(num);
	int i;
	for(i=1;i<=num;i++){
		int val;
		do{
			printf("Enter a valid integer (No decimals allowed). You are entereing %d value.\n",i);
			fgets(value,MAX_INPUT_SIZE,stdin);
		}while(!validatInputPosNeg(value));
		val=atoi(value);
		Node *new =createNewNode(val);
		enQ(new,cq);
	}

	printf("You Q is ready!! Below is the Q \n");
	printQ(cq,NULL);

	for(i=0;i<num-1;i++){
		int randomNumber=generateRandomNumber(0,cq->size);
		printf("Position to be deleted %d -- ",randomNumber);
		Node * node=deleteNode(randomNumber,cq);
		printf("Print from next element :: " );
		printQ(cq,node);
		printf("size updated :: %d\n",cq->size);
		printf("------------\n" );

	}
	printf("Winner of the competition is :: %d\n",cq->front->val);
}
