//readme:first input the number of vertex and the first vertex
//then input the adjenct matrix


#include <stdio.h>
#include <stdlib.h>

//the queue structure
struct Queue{
	int Front;
	int Rear;
	int Size;
	int Capacity;
	int* Array;
};

//create a graph, return nthe adjacent matrix
int** CreateGraph(int vertexnum);
//breadth-first search , return an array  , start mark the beginning position in the result array
void BreadthFirst(int vertexnum,int** graph,int vertex,int start,int* result,int* knownvertex);
//
int DepthFirst(int vertexnum,int** grapgh,int vertex,int start,int* result,int* knownvertex);
//enter the queue
void EnQueue(struct Queue* queue, int vertex);
//delete the front data and return 
int DeQueue(struct Queue* queue ) ;


int main(void)
{
	//number of vertex, the first vertex, the graph
	int vertexnum;
	int firstvertex;
	int** graph;
	//get the input
	scanf("%d%d",&vertexnum,&firstvertex);
	graph = CreateGraph(vertexnum);
	//end input
	
	int i = 0;
	
	//solve in two strategies
	//the result array which stored the order
	int* result = (int*)malloc(vertexnum*sizeof(int));
	//the known array, 1 means known and 0 means unknown
	//it is used to mark the vertex
	int* knownvertex = (int*)malloc(sizeof(int)*vertexnum);
	//initialize the knownarray
	for( i=0 ; i<vertexnum ; i++ )
		knownvertex[i] = 0;
	
	
	
	//first take breadth-first search
	BreadthFirst(vertexnum,graph,firstvertex,0,result,knownvertex);
	//print the end
	printf("breadth-first search:");
	for( i=0; i<vertexnum;i++ )
		printf("v%d ",result[i]+1);
	
	
	//then take depth-first search
	//renew the knownvertex array
	for(i=0 ; i<vertexnum ; i++)
		knownvertex[i] = 0;
	int tempstart = DepthFirst(vertexnum,graph,firstvertex,0,result,knownvertex);
	//check the knownvertex array
	for(i=0;i<vertexnum;i++)
	{
		if(knownvertex[i]==0)
		{
			tempstart = DepthFirst(vertexnum,graph,i+1, tempstart,result,knownvertex);
		}
	}
	printf("depth-first search:");
	for( i=0; i<vertexnum;i++ )
		printf("v%d ",result[i]+1);
	
	
	
	//end main
	return 0;
}

int** CreateGraph(int vertexnum)
{
	int** graph = (int**)malloc(vertexnum*sizeof(int*));
	int i = 0,j=0;
	for( i=0;i<vertexnum;i++)
		graph[i]=(int*)malloc(vertexnum*sizeof(int));
		
	//get the input
	for(i=0;i<vertexnum;i++)
		for(j=0;j<vertexnum;j++)
		{
			scanf("%d",&graph[i][j]);
		}

	return graph;
	
}


int DepthFirst(int vertexnum,int** grapgh,int firstvertex,int start,int* result,int* knownvertex)
{
	//create a queue
	struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
	queue->Array = (int*)malloc(sizeof(int)*vertexnum);
	queue->Capacity = vertexnum;
	queue->Front = 0;
	queue->Rear = -1;
	queue->Size = 0;
	
	int i,j;
	
	
	//first vertex enter the queue
	EnQueue(queue,firstvertex);
	knownvertex[firstvertex-1] = 1;
	//then the neighbors enter the queue
	for(j=0;j<vertexnum;j++)
	{
		if(knownvertex[j] == 0 && grapgh[firstvertex-1][j]!=-1)
		{
			EnQueue(queue,j+1);
			knownvertex[j] = 1;
		}
	}
	
	//get out of teh queue
	result[start] = DeQueue(queue)-1;
	start++;
	
	while(queue->Size != 0)
		start = DepthFirst(vertexnum , grapgh , DeQueue(queue) , start , result , knownvertex );
	
	return start;
}



void BreadthFirst(int vertexnum,int** graph,int firstvertex,int start,int* result,int* knownvertex)
{
	int i = 0,j=0;
	//store the result
	
	
	
	
	//use the queue to help search
	//initialize the queue
	struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
	queue->Capacity = vertexnum;
	queue->Array = (int*)malloc(sizeof(int)*queue->Capacity);
	queue->Front = 0;
	queue->Rear = -1;
	queue->Size = 0;
	
	//start the search
	//store the current vertex
	int tempvertex = 0;
	//initialize 
	tempvertex = firstvertex-1;
	EnQueue(queue,firstvertex-1);
	knownvertex[firstvertex-1] = 1;
	//use the queue 
	for(i = start ; queue->Size!=0;i++)
	{
		for(j=0 ; j<vertexnum  ; j++)
		{
			if( graph[queue->Array[queue->Front]][j]<=0 )
				continue;
			tempvertex = j;
			//first , make it known,then enter the queue
			if( knownvertex[tempvertex]==0 )
			{
				//make it known
				knownvertex[tempvertex] = 1;
				//enter the queue
				EnQueue(queue,tempvertex);
			}
		}
		//delete the front element
		result[i] = DeQueue(queue);	
	}
	
	//
	if(i != vertexnum)
	{
		j = 0;
		for(j=0;j<vertexnum;j++)
		{
			if(knownvertex[j] == 0)
				BreadthFirst(vertexnum,graph,j+1,i,result,knownvertex);
		}
		
	}
		
	
	
	return ;
}


void EnQueue(struct Queue* queue , int vertex)
{
	if(queue->Size == queue->Capacity)
		return;
	else 
	{
		queue->Size++;
		queue->Rear++;
		if(queue->Rear==queue->Capacity)
			queue->Rear = 0;
		queue->Array[queue->Rear] = vertex;
	}
}

int DeQueue(struct Queue* queue )
{
	if(queue->Size == 0)
		return -1;
	else
	{
		
		queue->Size--;
		queue->Front++;
		int result =  queue->Array[queue->Front-1];
		if(queue->Front==queue->Capacity)
			queue->Front = 0;
		return result;
	}
}

