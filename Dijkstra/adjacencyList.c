#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define MAX_BUFF_SIZE 256
int numberOfVertices;
int sizeOfHeap;

typedef struct AdjacencyNode{
  int distance;
  int vertex;
  struct AdjacencyNode * next;
}AdjacencyNode;

typedef struct Graph{
  AdjacencyNode * head;
}Graph;

typedef struct MinHeapNode{
  int distance;
  int vertex;
  int finalised;
}MinHeapNode;

AdjacencyNode * createAdjacencyNode(int vertex,int distance){
  AdjacencyNode * adjNode=(AdjacencyNode *)malloc(sizeof(AdjacencyNode));
  adjNode->vertex=vertex;
  adjNode->distance=distance;
  adjNode->next=NULL;
  return adjNode;
}
void addEdge(Graph * graph,int src,int dest,int dist){
// printf("%d %d %d\n", src,dest,dist);
  AdjacencyNode * newNode=createAdjacencyNode(dest,dist);
    newNode->next=graph[src].head;
    graph[src].head=newNode;
}

void swap(MinHeapNode * node1,MinHeapNode * node2){
  MinHeapNode temp=*node1;
  *node1=*node2;
  *node2=temp;
}


void decreaseKey(MinHeapNode * minHeapArray,int * position,int distance,int vertex){
// printf("Inside decrease key +++++++++++++\n");
int childIndex=position[vertex];
int parentIndex=(childIndex-1)/2;
  // printf("Decrease key vertex %d distance %d\n",vertex,distance );
  minHeapArray[childIndex].distance=distance;
  // printf("childIndex :: %d,childValue:: %d , parentIndex :: %d,parentValue:: %d",childIndex,minHeapArray[childIndex].distance,parentIndex,minHeapArray[parentIndex].distance );

  while (childIndex && minHeapArray[childIndex].distance < minHeapArray[parentIndex].distance)
  {
    position[minHeapArray[childIndex].vertex] = parentIndex;
    position[minHeapArray[parentIndex].vertex] = childIndex;
    swap(&minHeapArray[childIndex], &minHeapArray[parentIndex]);
    childIndex=parentIndex;
  }
  // printf("End decrease key +++++++++++++\n");
}

void minify(MinHeapNode * minHeapArray, int index,int * position)
{
	int min, left, right;
	min = index;
	left = 2 * index + 1;
	right = 2 * index + 2;
	if (left < sizeOfHeap &&	minHeapArray[left].distance < minHeapArray[min].distance )
	min = left;
	if (right < sizeOfHeap &&		minHeapArray[right].distance < minHeapArray[min].distance )
	min = right;
	if (min != index)
	{
		position[minHeapArray[min].vertex] = index;
		position[minHeapArray[index].vertex] = min;
		swap(&minHeapArray[min], &minHeapArray[index]);
		minify(minHeapArray, min,position);
	}
}


MinHeapNode * extractMin(MinHeapNode * minHeapArray,int * position)
{

  if (sizeOfHeap==0)
		return NULL;
    // MinHeapNode * rootNode=minHeapArray;
    int rootVertex = minHeapArray[0].vertex;
    int lastVertex = minHeapArray[sizeOfHeap - 1].vertex;

	swap(&minHeapArray[0], &minHeapArray[sizeOfHeap - 1]);
	position[rootVertex] = sizeOfHeap-1;
	position[lastVertex] = 0;
	sizeOfHeap--;
	minify(minHeapArray, 0,position);
	return &minHeapArray[sizeOfHeap];
}

bool isInMinHeap(int * position,int vertex)
{
if (position[vertex] < sizeOfHeap)
	return true;
return false;
}

void printArr(int * finalVector)
{

  FILE * file=fopen("adjList_outfile.txt","w");
  if(file){
    fprintf(file, "%s", "Vertex\tDistance from Source\n");
    for (int i = 0; i < numberOfVertices; ++i)
  		fprintf(file,"%d \t\t %d\n", i, finalVector[i]);
  }else{
    perror("File creation / open problem::");
  }

}

void dijkstra(Graph * graph,int src){
  int finalDistanceArr[numberOfVertices],visited[numberOfVertices];
  MinHeapNode minHeapArray[numberOfVertices];
  int position[numberOfVertices];
  for (size_t i = 0; i < numberOfVertices; i++) {
    if(i==src){
      finalDistanceArr[i]=0;
      minHeapArray[i].distance=0;
    }
    else{
      finalDistanceArr[i]=INT_MAX;
      minHeapArray[i].distance=INT_MAX;
    }
    minHeapArray[i].vertex=i;
    minHeapArray[i].finalised=false;
    position[i]=i;
  }
  //
  // for (size_t i = 0; i < numberOfVertices; i++) {
  //   /* code */
  //   printf("vertex ::%d distance ::%d \n",minHeapArray[i].vertex,minHeapArray[i].distance );
  // }

	decreaseKey(minHeapArray,position,finalDistanceArr[src],src);
	while (sizeOfHeap!=0)
	{
		MinHeapNode * minHeapNode = extractMin(minHeapArray,position);
    // printf("min vertex %d min dist %d\n",minHeapNode->vertex,minHeapNode->distance );
		int u = minHeapNode->vertex;
		AdjacencyNode * p = graph[u].head;
		while (p)
		{
        // for (size_t i = 0; i < numberOfVertices; i++) {
        //   printf("123 vertex ::%d distance ::%d position :: %d\n",minHeapArray[i].vertex,minHeapArray[i].distance,position[minHeapArray[i].vertex] );
        // }
			int v = p->vertex;
      // printf("--------------------\n" );
      // printf("vertex :: %d, position in Heap :: %d size of heap %d\n",v,position[v],sizeOfHeap );
      // printf("isInMinHeap %d \n",isInMinHeap(position, v));
			if (isInMinHeap(position, v) && finalDistanceArr[u] != INT_MAX &&
										p->distance + finalDistanceArr[u] < finalDistanceArr[v])
			{
				finalDistanceArr[v] = finalDistanceArr[u] + p->distance;
				decreaseKey(minHeapArray,position,finalDistanceArr[v],v);
        // printf("After decrease keyvertex :: %d, position in Heap :: %d size of heap %d\n",v,position[v],sizeOfHeap );
			}
			p = p->next;
		}
	}
	printArr(finalDistanceArr);
}
int main(int argc, char const *argv[]) {


    FILE * file=fopen("inputFile.txt","r");
    int source;
  if(file){
  	char * lineBuffer=(char *)malloc(sizeof(char)*MAX_BUFF_SIZE);

    int count=0;
    bool isValid=true,isValidEdge=false;
    Graph * graph;

  	while(fgets(lineBuffer,MAX_BUFF_SIZE,file)!=NULL)//used to read a line of size MAX_BUFF_SIZE from file
  	{
      int j=0,s,d,w;
      isValidEdge=false;
      char intCharacter[MAX_BUFF_SIZE]={};
      int charLength=0;
  		for(int i=0;lineBuffer[i-1]!='\n';i++){

  			if(count==0){
  				numberOfVertices=sizeOfHeap=atoi((char *)&lineBuffer[i]);
          graph=(Graph *)malloc(sizeof(Graph)*numberOfVertices);
          for (int j = 0; j < numberOfVertices; j++) {
            graph[j].head=NULL;
          }
  			}else if(count==1){
          source=atoi((char *)&lineBuffer[i]);
        }else{
  				if(lineBuffer[i]!=' ' && lineBuffer[i]!='\n'){
  						intCharacter[charLength++]=lineBuffer[i];
  				}
  				else if(lineBuffer[i]==' ' || lineBuffer[i]=='\n'|| lineBuffer[i]=='\0'){
            intCharacter[charLength]='\n';
            if(j==0){

              s=atoi(intCharacter);
            }

            if(j==1){
              d=atoi(intCharacter);
            }

            if(j==2){
              w=atoi(intCharacter);
              isValidEdge=true;
            }

            j++;
            charLength=0;
  				}else{
  					printf("Worng input format\n");
  					isValid=false;
  					break;
  				}
  			}

        if(isValid && isValidEdge){
          addEdge(graph,s,d,w);
        }
        count++;
  		}

  	}

   dijkstra(graph,source);
  }
  return 0;
}
