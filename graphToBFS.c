/*This code uses Graphviz for visualization
Install Graphviz from 
https://graphviz.gitlab.io/_pages/Download/Download_windows.html
before running this code
and add C:\Program Files (x86)\Graphviz2.38\bin to PATH
OR
Comment out the lines invcluding Graphviz commands or any call to Graphviz*/


#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
	int numNodes = atoi(argv[1]);
	int i=0, j=0, snode;
	int *adjArr = (int *)malloc(numNodes*numNodes*sizeof(int));
	printf("\nNumber of nodes in the Graph :: %d\n",numNodes);
	printf("\nEnter the Adjacency matrix :: \n");
	for (i=0;i<numNodes;i++)
	{
		for(j=0;j<numNodes;j++)
		{
			//printf("%d %d\n",i,j);
			scanf("%d", &adjArr[i*numNodes+j]);
		}
	}

	printf("\nAdjacency Matrix :: \n");
	printf("  ");
	for(i=0;i<numNodes;i++)
		printf("%d ",i+1);
	printf("\n");
	for(i=0;i<numNodes;i++)
	{
		printf("%d ",i+1);
		for(j=0;j<numNodes;j++)
			printf("%d ",adjArr[i*numNodes+j]);
		printf("\n");
	}

	//VISUALIZATION
	FILE *graph, *bfstree;
	graph = fopen("graph.dot","w");
	if (graph==NULL)
	{
		printf("Error!!");
		exit(1);
	}

	fprintf(graph,"graph {\n");

	for (i=0;i<numNodes;i++)
	{
		for(j=i+1;j<numNodes;j++)
			if (adjArr[i*numNodes+j] == 1)
				fprintf(graph,"%d -- %d\n",i+1,j+1);
		fflush(stdout);
	}

	fprintf(graph,"}\n");
	fflush(stdout);
	fclose(graph);

	char command[100];
	sprintf(command,"dot graph.dot -Tpng -o graph.png");
	system(command);
	
	#ifdef _WIN32
		#ifdef _WIN64
			printf("\nYou have Windows Operating System.\nKindly Open File Location to view Graph\n\n");
		#endif
	#else
		system("eog graph.png");
	
	#endif
	
	//BUILDING BFS
	bfstree = fopen("bfstree.dot","w");
	if(bfstree==NULL)
	{
		printf("Error!!");
		exit(1);
	}

	fprintf(bfstree,"digraph {\n");

	printf("Enter start node : \nOptions are :: ");
	for(i=0;i<numNodes;i++)
		printf("[%d] ",i+1);
	printf("\n");
	scanf("%d",&snode);

	int visitedNodes[numNodes],head=0,tail=0,v=0;
	visitedNodes[head] = snode;
	tail++;
	printf("%d\n",visitedNodes[head]);
	while(head!=tail || head<numNodes)
	{
		for(i=0;i<numNodes;i++)
		{
			if(adjArr[(visitedNodes[head]-1)*numNodes+i]==1)
			{
				for(j=0;j<tail;j++)
				{
					if((i+1)==visitedNodes[j])
					{
						v = 1;
						break;
					}
				}
				if(v!=1)
				{
					printf("%d",i+1);
					visitedNodes[tail] = i+1;
					tail++;

					fprintf(bfstree,"%d -> %d\n",visitedNodes[head],i+1);
				}
			}
			v = 0;
		}
		fflush(stdout);
		printf("\n");
		head++;
	}
	fprintf(bfstree,"}\n");
	fflush(stdout);
	fclose(bfstree);

	sprintf(command,"dot bfstree.dot -Tpng -o bfstree.png");
	system(command);	
}