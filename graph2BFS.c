#include <stdio.h>
#include <stdlib.h>

//---------------------------MAIN-----------------------------
void main(int argc, char *argv[])
{
	printf("**********************************\n");
	printf("*     ASSIGNMENT 1 PROGRAM 1     *\n");
	printf("**********************************\n");
	FILE *fp;

	//if(argv[1]!=NULL)
	//	fp = fopen(argv[1],"r");
	//else
	fp = fopen("input1.txt","r");

	char ch;
	int numNodes, sNode, i = 0;

	//Scanning the first line
	do
	{
		fscanf(fp,"%c",&ch);
		if(ch!=' ' && ch!='\n')
		{
			if(i==0)
				numNodes = ch-'0';
			else
				sNode = ch-'0';
			i++;
		}
	}
	while(ch!='\n');

	//printf("Number of nodes : %d\nStart Node : %d\n",numNodes,sNode);

	//Taking Adjacency List as input

	//printf("Adjacency List : \n\n");
	int degrees[numNodes];
	for(i=0;i<numNodes;i++)
		degrees[i]=0;
	int **adjList = (int **)malloc(numNodes*sizeof(int *));
	int len = 0,j,k=0,l,read;
	char num[4];
	for(i=0;i<numNodes;i++)
	{
		adjList[i] = NULL;
		printf("Node %d ",i+1);
		do
		{
			read = fscanf(fp,"%c",&ch);
			if(read!=EOF)
			{
				if(ch!=' ' && ch!='\n')
				{
					num[k]=ch;
					k++;
				}
				else
				{
					k = 0;
					if(atoi(num)!=0)
					{
						len++;
						adjList[i] = (int *)realloc(adjList[i],sizeof(int)*len);
						adjList[i][len-1] = atoi(num);
						degrees[i]+=1;	
					}
					for(l=0;l<4;l++)
						num[l]=0;
				}
			}
			else
			{
				k = 0;
				if(atoi(num)!=0)
				{
					len++;
					adjList[i] = (int *)realloc(adjList[i],sizeof(int)*len);
					adjList[i][len-1] = atoi(num);
					degrees[i]+=1;	
				}
				break;
			}
		}
		while(ch!='\n');

		for(j=0;j<len;j++)
			printf("-> %d ",adjList[i][j]);
		printf("\n");
		printf("Degree of node %d : %d\n",i+1,degrees[i]);

		len = 0;
	}
	fclose(fp);

	//QUEUE
	int *nodeQueue = (int *)malloc(numNodes*sizeof(int));
	int head=0,tail=0;
	int *visited = (int *)malloc(numNodes*sizeof(int));

	for(i=0;i<numNodes;i++)
		visited[i]=0;
	//visited[sNode-1] = 1;
	nodeQueue[head] = sNode;
	tail++;
	int tempnode;
	while(head!=tail || head<numNodes)
	{
		for(j=0;j<degrees[nodeQueue[head]-1];j++)
		{
			tempnode = adjList[nodeQueue[head]-1][j];
			if(!(visited[tempnode-1]))
			{
				nodeQueue[tail] = tempnode;
				visited[tempnode-1] = 1;
				tail++;
			}
		}
		visited[nodeQueue[head]-1]=1;
		head++;
		/*for(j=0;j<numNodes;j++)
			printf("%d ",nodeQueue[j]);
		printf("\n");*/
	}

	printf("Starting vertex followed by the trace of BFS\n");
	for(i=0;i<numNodes;i++)
		printf("%d ",nodeQueue[i]);
	printf("\n\n");
}
