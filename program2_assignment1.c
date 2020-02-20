#include <stdio.h>
#include <stdlib.h>

//---------------------------MAIN-----------------------------
void main(int argc, char *argv[])
{
	printf("**********************************\n");
	printf("*     ASSIGNMENT 1 PROGRAM 2     *\n");
	printf("**********************************\n");

	//**********************************************************
	//* CHECKING IF THERE IS A CYCLE OR NOT BY TRAVERSING THE  *
	//* GRAPH AS A DFS TREE                                    *
	//**********************************************************

	FILE *fp;

	//if(argv[1]!=NULL)
	//	fp = fopen(argv[1],"r");
	//else
	fp = fopen("input2&3.txt","r");

	char ch;
	int numNodes, i = 0;

	//Scanning the first line
	do
	{
		fscanf(fp,"%c",&ch);
		if(ch!=' ' && ch!='\n')
			numNodes = ch-'0';
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

	//STACK
	int *nodeStack = (int *)malloc(numNodes*sizeof(int));
	int top=0;
	int *visited = (int *)malloc(numNodes*sizeof(int));
	int *parent = (int *)malloc(numNodes*sizeof(int));
	int cycle_node_count = 0;
	for(i=0;i<numNodes;i++)
		visited[i]=0;
	visited[top] = 1;
	nodeStack[top] = 1;
	top++;
	int tempnode, topnode;
	int cycle_found = 0;
	while(top!=0)
	{
		topnode = nodeStack[top-1];
		top--;
		for(i=degrees[topnode-1]-1;i>=0;i--)
		{
			tempnode = adjList[topnode-1][i];
			parent[tempnode-1] = topnode;
			if(!visited[tempnode-1])
			{
				nodeStack[top] = tempnode;
				visited[tempnode-1] = 1;
				top++;
				cycle_node_count++;
			}
			else
			{
				if(parent[topnode-1]!=tempnode)
				{
					cycle_found = 1;
					cycle_node_count++;
					break;
				}
			}

		}
		if(cycle_found)
		{
			printf("\nYes\n");
			for(j=cycle_node_count-1;j>=0;j--)
			{
				printf("%d ",tempnode);
				tempnode = parent[tempnode-1];
			}
			printf("\n");
			break;
		}
		else if(!cycle_found && top==0)
		{
			j = 0;
			while(visited[j]!=0)
				j++;
			if(j+1<=numNodes)
			{
				nodeStack[top] = j+1;
				top++;
				cycle_node_count = 0;
			}
			else
				printf("\nNo\n");
		}
	}
}