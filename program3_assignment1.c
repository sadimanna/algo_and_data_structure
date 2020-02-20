#include <stdio.h>
#include <stdlib.h>

//---------------------------MAIN-----------------------------
void main(int argc, char *argv[])
{
	printf("**********************************\n");
	printf("*     ASSIGNMENT 1 PROGRAM 3     *\n");
	printf("**********************************\n");

	//**********************************************************
	//* CHECKING IF THE GRAPH IS BIPARTITE OR NOT BY CHECKING  *
	//* IF TWO NODES IN THE SAME LAYER IN A BFS TREE HAS THE   *
	//* SAME COLOR OR NOT                                      *
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

	//QUEUE
	int *visited = (int *)malloc(numNodes*sizeof(int));

	for(i=0;i<numNodes;i++)
		visited[i]=0;

	int tempnode;
	int L = 0;
	int *color = (int *)malloc(numNodes*sizeof(int));

	int bipart = 1;
	
	for(i=0;i<numNodes;i++)
		visited[i]=0;
	
	int *this_layer = NULL;
	int this_layer_len = 0, next_layer_len = 1;
	int *next_layer = (int *)malloc(sizeof(int));//(int *)malloc(degrees[sNode-1]*sizeof(int));
	
	next_layer[0] = 1;
	visited[0] = 1;
	int numVisited = 1;
	color[0] = 1;
	//int cycle_node_count = 1;

	while(numVisited<numNodes)
	{
		this_layer = (int *)realloc(this_layer,next_layer_len*sizeof(int));
		
		for(i=0;i<next_layer_len;i++)
			this_layer[i]=next_layer[i];

		this_layer_len = next_layer_len;
		//printf("This Layer\n");
		//for(i=0;i<this_layer_len;i++)
		//	printf("T%d ",this_layer[i]);
		/*if(numVisited==2)
			break;*/
		next_layer_len = 0;
		L++;
		for(i=0;i<this_layer_len;i++)
		{
			//printf("Degrees %d \n", degrees[this_layer[i]-1]);
			for(j=0;j<degrees[this_layer[i]-1];j++)
			{
				tempnode = adjList[this_layer[i]-1][j];
				//printf("%d tempnode %d \n", this_layer[i], tempnode);
				if(!(visited[tempnode-1]))
				{
					next_layer_len++;
					next_layer = (int *)realloc(next_layer,sizeof(int)*next_layer_len);
					next_layer[next_layer_len-1] = tempnode;
					//nodeQueue[tail] = tempnode;
					visited[tempnode-1] = 1;
					numVisited++;
					//tail++;
					if(L%2!=0)
						color[tempnode-1]=2;
					else
						color[tempnode-1]=1;
				}
			}
		}
		//printf("Next Layer\n");
		//for(i=0;i<next_layer_len;i++)
		//	printf("N%d ",next_layer[i]);
		//printf("\n");

		//CHECKING ALL THE EDGES BETWEEN THE NODES IN THE SAME LAYER -- O(|E|)
		for(i=0;i<next_layer_len;i++)
		{
			for(j=i+1;j<next_layer_len;j++)
			{
				for(k=0;k<degrees[next_layer[i]-1];k++)
				{
					if(adjList[next_layer[i]-1][k]==next_layer[j])
					{
						bipart = 0;
						printf("\nNo\nNodes %d and %d having same color, also has an edge between them.\n",next_layer[i],adjList[next_layer[i]-1][k]);
						break;
					}
				}
				if(!bipart)
					break;
			}
			if(!bipart)
				break;
		}
		if(!bipart)
			break;
		if(numVisited<numNodes && next_layer_len==0)
		{
			j = 0;
			while(visited[j]!=0)
				j++;
			if(j+1<=numNodes)
			{
				next_layer = (int *)realloc(next_layer,sizeof(int));
				next_layer[0] = j+1;
				next_layer_len = 1;
				numVisited++;
			}
		}

	}
	if(bipart)
	{
		printf("\nYes\n");
		printf("(");
		for(i=0;i<numNodes;i++)
			if(color[i]==1)
				printf(" %d ",i+1);
		printf(") (");
		for(i=0;i<numNodes;i++)
			if(color[i]==2)
				printf(" %d ",i+1);
		printf(")");
	}
}