#include <stdio.h>
#include <stdlib.h>

//---------------------------PART 1---------------------------



//---------------------------PART 2---------------------------

//---------------------------PART 3---------------------------

//---------------------------MAIN-----------------------------
void main(int argc, char *argv[])
{
	FILE *fp;

	//if(argv[1]!=NULL)
	//	fp = fopen(argv[1],"r");
	//else
	fp = fopen("input.txt","r");

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

	//---------------------------------PART 1-------------------------------------
	printf("\nPART 1\n");
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

	//---------------------------------PART 2-------------------------------------
	printf("\nPART 2\n");
	head = 0;
	tail = 1;
	int cycle_found = 0;
	int *parent = (int *)malloc(numNodes*sizeof(int));

	for(i=0;i<numNodes;i++)
	{
		parent[i]=-1;
		visited[i]=0;
	}
	int cycle_node_count = 1;

	while(head!=tail || head<numNodes)
	{
		for(j=0;j<degrees[nodeQueue[head]-1];j++)
		{
			tempnode = adjList[nodeQueue[head]-1][j];
			parent[tempnode-1] = nodeQueue[head];
			if(!(visited[tempnode-1]))
			{
				
				nodeQueue[tail] = tempnode;
				visited[tempnode-1] = 1;
				tail++;
			}
			else if(visited[tempnode-1] && parent[nodeQueue[head]-1]!=tempnode)
			{
				cycle_found = 1;
				break;
			}
		}
		cycle_node_count += 1;
		if(cycle_found)
			break;
		else
		{
			visited[nodeQueue[head]-1]=1;
			head++;
		}
		/*for(j=0;j<numNodes;j++)
			printf("%d ",nodeQueue[j]);
		printf("\n");*/
	}
	if(!cycle_found)
		printf("No\n");
	else
	{
		printf("Yes\n");
		//int *cycle_nodes = (int *)malloc(cycle_node_count*sizeof(int));
		for(j=cycle_node_count-1;j>=0;j--)
		{
			printf("%d ",tempnode);
			//cycle_nodes[j] = tempnode;
			tempnode = parent[tempnode-1];
		}
		printf("\n");
	}

	//--------------------------------------PART 3-----------------------------------

	printf("\nPART 3\n");
	head = 0;
	tail = 1;
	//int k = 0;
	int L = 0;
	int *color = (int *)malloc(numNodes*sizeof(int));
	color[nodeQueue[head]-1] = 1;
	//L++:
	int bipart = 1;
	for(i=0;i<numNodes;i++)
		visited[i]=0;
	visited[sNode-1] = 1;
	int numVisited = 1;
	int *this_layer = NULL;
	int this_layer_len = 0, next_layer_len = 1;
	int *next_layer = (int *)malloc(sizeof(int));//(int *)malloc(degrees[sNode-1]*sizeof(int));
	next_layer[0] = sNode;
	//int cycle_node_count = 1;

	while(numVisited<numNodes)
	{
		this_layer = (int *)realloc(this_layer,next_layer_len*sizeof(int));
		
		for(i=0;i<next_layer_len;i++)
			this_layer[i]=next_layer[i];

		this_layer_len = next_layer_len;
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
				/*for(k=0;k<next_layer_len;k++)
					printf("%d ", next_layer[k]);
				printf("\n");*/
			}
			/*for(j=0;j<next_layer_len;j++)
				printf("%d ", next_layer[j]);
			printf("\n");*/
		}
		//L++;
		//next_layer_len = j+1;
		/*for(j=0;j<numNodes;j++)
			printf("%d ",nodeQueue[j]);
		printf("\n");*/
	}
	int c1=0;
	int c2=0;
	for(i=0;i<numNodes;i++)
	{
		if(color[i]==1)
			c1++;
		if(color[i]==2)
			c2++;
	}

	int *color1 = (int *)malloc(sizeof(int)*c1);
	int *color2 = (int *)malloc(sizeof(int)*c2);

	c1=0;c2=0;
	for(i=0;i<numNodes;i++)
	{
		if(color[i]==1)
		{
			color1[c1] = i+1;
			c1++;
		}
		else
		{
			color2[c2] = i+1;
			c2++;
		}
	}

	for(i=0;i<c1;i++)
	{
		for(j=i+1;j<c1;j++)
		{
			for(k=0;k<degrees[color1[i]-1];k++)
				if(adjList[color1[i]-1][k]==color1[j])
				{
					bipart = 0;
					printf("No\nEdge between nodes %d and %d with color 1\n",color1[i],adjList[color1[i]-1][k]);
					break;
				}
		}
		if(!bipart)
			break;
	}
	if(bipart)
	{
		for(i=0;i<c2;i++)
		{
			for(j=i+1;j<c2;j++)
			{
				for(k=0;k<degrees[color2[i]-1];k++)
					if(adjList[color2[i]-1][k]==color2[j])
					{
						bipart = 0;
						printf("No\nEdge between nodes %d and %d with color 2\n",color2[i],adjList[color2[i]-1][k]);
						break;
					}
			}
			if(!bipart)
				break;
		}
	}
	if(bipart)
	{
		printf("Yes ");
		printf("( ");
		for(i=0;i<c1;i++)
			printf("%d ",color1[i]);
		printf(")");
		printf("( ");
		for(i=0;i<c2;i++)
			printf("%d ",color2[i]);
		printf(")");
		printf("\n");
	}
}