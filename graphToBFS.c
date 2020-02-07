/*
AUTHOR : SILADITTYA MANNA
DATE: 06-02-2020

This code uses Graphviz for visualization
Install Graphviz from 
https://graphviz.gitlab.io/_pages/Download/Download_windows.html
before running this code
and add C:\Program Files (x86)\Graphviz2.38\bin to PATH

FOR UBUNTU run "sudo apt-get install graphviz" in terminal

OR
Comment out the lines with Graphviz commands or any call to Graphviz

The BFS Tree is represented using the data structure as shown below

				    ______
	L0			   |_ROOT_|
				      |
				    __|
				____|____    __________    _________
	L1		       |___child_|--|_sibling__|--|_sibling_|----
					|	 |	
				   ____	|     ___|____    _________    _________
			       	|	     |_child__|--|_sibling_|--|_sibling_|----
		    	     ___|____    ___________
	L2	   	    |_child__|--|__sibling__|----



*/


#include <stdio.h>
#include <stdlib.h>

struct bfsnode
{
	int node;
	struct bfsnode *parent, *sibling, *child;
};

void main(int argc, char *argv[])
{
	int numNodes = atoi(argv[1]);
	int i=0, j=0, snode, tnode;
	int *adjArr = (int *)malloc(numNodes*numNodes*sizeof(int));
	char *rowinput = (char *)malloc(numNodes*sizeof(char));

	printf("\nNumber of nodes in the Graph :: %d\n",numNodes);
	printf("\nEnter the Adjacency matrix :: \n");
	for (i=0;i<numNodes;i++)
	{
		printf("Enter adjacency matrix row for node [%d] : ",i+1);
		scanf("%s", rowinput);
		
		for(j=0;j<numNodes;j++)
			adjArr[numNodes*i+j] = rowinput[j] - '0';
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

	//------------------------------------------VISUALIZATION
	FILE *graph;
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
	
	//-------------------------------------BUILDING BFS
	//-------------------------------------------------using QUEUE
	FILE *bfstree;
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

	printf("Enter target node : \nOptions are :: ");
	for(i=0;i<numNodes;i++)
		printf("[%d] ",i+1);
	printf("\n");
	scanf("%d",&tnode);

	int head=0,tail=0,v=0;

	struct bfsnode *bfsTreeArr = (struct bfsnode *)malloc(numNodes*sizeof(struct bfsnode));

	bfsTreeArr[0].node = snode;
	bfsTreeArr[0].parent = NULL;
	bfsTreeArr[0].sibling = NULL;
	bfsTreeArr[0].child = NULL;
	tail++;

	printf("Start Node : %d\n",bfsTreeArr[head].node);
	while(head!=tail || head<numNodes)
	{
		for(i=0;i<numNodes;i++)
		{
			if(adjArr[(bfsTreeArr[head].node-1)*numNodes+i]==1)
			{
				for(j=0;j<tail;j++)
				{
					if((i+1)==bfsTreeArr[j].node)
					{
						v = 1;
						break;
					}
				}
				if(v!=1)
				{
					printf("%d ",i+1);

					if(bfsTreeArr[head].child==NULL)
						bfsTreeArr[head].child = &bfsTreeArr[tail];
					
					bfsTreeArr[tail].node = i+1;
					bfsTreeArr[tail].parent = &bfsTreeArr[head];
					if(head != tail-1 && bfsTreeArr[tail-1].parent->node == bfsTreeArr[tail].parent->node)
						bfsTreeArr[tail-1].sibling = &bfsTreeArr[tail];
					
					bfsTreeArr[tail].sibling = NULL;
					bfsTreeArr[tail].child = NULL;
					
					tail++;

					fprintf(bfstree,"%d -> %d\n",bfsTreeArr[head].node,i+1);
				}
			}
			v = 0;
			/*if(bfsTreeArr[tail-1].node == tnode)
			{
				found = 1;
				break;
			}*/
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

	/*for(i=0;i<numNodes;i++)
		printf("%d ",bfsTreeArr[i].node);*/


	//-------------------------------------VISUALIZING IN TERMINAL
	printf("\nPrinting BFS Tree\n\n");
	i = 1;
	j = 0;
	struct bfsnode parent, *child, *sibling;
	parent = bfsTreeArr[0];
	child = parent.child;
	sibling = parent.sibling;

	//---------------------Initialization
	printf("L%d : -%d-\n",j,parent.node);
	printf("L%d : ",++j);
	
	//-------------------Loooooooooooooooooop
	while(i<numNodes)
	{
		printf("-%d-",parent.child->node);
		i++;
		if(parent.child->sibling != NULL)
			parent.child = parent.child->sibling;
		else
		{
			if(parent.sibling == NULL)
			{
				parent = *child;
				child = parent.child;
				sibling = parent.sibling;
				printf("\n");
				if(i<numNodes)
					printf("L%d : ",++j);
			}
			else
			{
				parent = *sibling;
				sibling = parent.sibling;
				printf("|");
			}	
		}
	}

	//*******************************************THE END
}
