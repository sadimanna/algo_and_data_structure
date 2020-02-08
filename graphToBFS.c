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
	L1		   |___child_|--|_sibling__|--|_sibling_|----
					|				 |	
				____|			  ___|____    _________    _________
			   |				 |_child__|--|_sibling_|--|_sibling_|----
		    ___|____    ___________
	L2	   |_child__|--|__sibling__|----



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

	#ifdef _WIN32
		#ifdef _WIN64
			printf("\nInstall Graphviz from https://graphviz.gitlab.io/_pages/Download/Download_windows.html before running this code and add C:\\Program Files (x86)\\Graphviz2.38\\bin to PATH\n\n");
		#endif
	#else
		printf("\nTo install Graphviz RUN 'sudo apt-get install graphviz' in TERMINAL before running this program\n\n");
		//system("sudo apt-get install graphviz");
	#endif

	int numNodes = atoi(argv[1]);
	int i=0, j=0, snode, tnode;
	/*int *adjArr = (int *)malloc(numNodes*numNodes*sizeof(int));
	char *rowinput = (char *)malloc(numNodes*sizeof(char));

	printf("\nNumber of nodes in the Graph :: %d\n",numNodes);
	printf("\nEnter the Adjacency matrix :: \n");
	for (i=0;i<numNodes;i++)
	{
		printf("Enter adjacency matrix row for node [%d] : ",i+1);
		scanf("%s", rowinput);
		
		for(j=0;j<numNodes;j++)
			adjArr[numNodes*i+j] = rowinput[j] - '0';
	}*/

	//Taking the graph given in Figure 3.2 of the book "Algorithm Design" as example
	//To take custom input uncomment the previous part and commen this line
	int adjArr[] = {1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,0,1,0,1,1,0,1,0,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0,0,1,1};

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

	/*printf("Enter target node : \nOptions are :: ");
	for(i=0;i<numNodes;i++)
		printf("[%d] ",i+1);
	printf("\n");
	scanf("%d",&tnode);*/

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
	printf(" '|' separates children of different nodes or denotes end of a LEVEL\n");
	printf(" '[-]' denotes the parent node has no children \n\n");
	//---------------------Initialization
	
	head = 0;
	tail = 0;
	int L = 0, Lchange = 1;
	struct bfsnode *currNode,*tempnode,*tempnode2;

	printf("L%d : ",L);
	printf("-%d-\n",bfsTreeArr[head].node);
	
	tempnode = &bfsTreeArr[head];
	//-------------------Loooooooooooooooooop
	while(head < numNodes)
	{
		if(Lchange==1)
		{
			L++;
			printf("L%d : ",L);
			Lchange=0;
		}
		if(tempnode->child != NULL)
		{
			printf("-%d-",tempnode->child->node);
			tail++;
			while(tempnode->child->sibling!=NULL)
			{	
				printf("-%d-",tempnode->child->sibling->node);
				if(tempnode->child->sibling!=NULL)
					tempnode->child = tempnode->child->sibling;
				tail++;
			}
		}
		else
		{
			printf("[-]");
		}
		printf("|");
		//Checking if the Level contains anymore nodes or not
		if(tempnode->sibling==NULL) 
		{
			tempnode2 = tempnode;
			
			if(tempnode2->sibling==NULL && tempnode2->parent==NULL) //FOR  ROOT
			{
				printf("\n");
				Lchange=1;
			}
			else
			{
				while(tempnode2->sibling==NULL)
				{
					if(tempnode2->parent==NULL)
						break;

					tempnode2 = tempnode2->parent;
				}
				if(tempnode2->sibling==NULL && tempnode2->parent==NULL)
				{
					printf("\n");
					Lchange=1;
				}
			}
		}
		head++;
		tempnode = &bfsTreeArr[head];
	}
	printf("\n\n");
	//*******************************************THE END
}