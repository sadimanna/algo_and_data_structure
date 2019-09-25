#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node 
{
	int data;
	struct node *left, *right;
};

int insert_heap_type();
int *insert_node(int *, int, int, int);
int *delete_node(int *, int, int);

int extract_extremum(int *, int, int);
int extract_antapex(int *, int, int);

void heap_sort(int *, int, int);
void reverse_heap_sort(int *, int, int);

void heap_array(int *, int);
void visualize_heap(int *, int);

int main()
{
	printf("\n\n How you doin'? \n");
	printf("\n Program for HEAP \n\n");
	int option, val, n = 0;
	int heap_type;
	int *heap = NULL;

	do
	{
		printf("\n ************************* MAIN MENU ************************** \n");
		printf(" 1.  Insert Heap Type \n");
		printf(" 2.  Insert New Node \n");
		printf(" 3.  Delete Node \n");
		printf(" 4.  Extract Extremum \n");
		printf(" 5.  Extract Antapex \n");
		printf(" 6.  Heap Sort \n");
		printf(" 7.  Reverse Order Sort \n");
		printf(" 8.  View Heap as Array \n");
		printf(" 9.  Visualize Tree \n");
		printf(" 10. Delete the Heap \n");
		printf(" 11. EXIT \n");
		printf("\n\n Enter what you wanna do :: ");
		scanf("%d", &option);
		switch(option)
		{
			case 1:
				heap_type = insert_heap_type();
				break;
			case 2:
				printf("\n Enter Value of New Node : ");
				scanf("%d", &val);
				heap = insert_node(heap, n, val, heap_type);
				n = n + 1;
				break;
			case 3:
				//printf("In a Heap, the Extremum is always deleted!!");
				//ptr = search_tree(root, val);
				heap = delete_node(heap, n, heap_type);//ptr);
				n = n - 1;
				break;
			case 4:
				val = extract_extremum(heap, n, heap_type);
				n = n - 1;
				if(heap_type)
					printf("Maximum : %d", val);
				else
					printf("Minimum : %d", val);
				break;
			case 5:
				val = extract_antapex(heap, n, heap_type);
				n = n - 1;
				if(heap_type)
					printf("Minimum : %d", val);
				else
					printf("Maximum : %d", val);
				break;
			case 6:
				heap_sort(heap, n, heap_type);
				break;
			case 7:
				reverse_heap_sort(heap, n, heap_type);
				break;
			case 8:
				heap_array(heap, n);
				break;;
			case 9:
				visualize_heap(heap, n);
				break;
			case 10:
				free(heap);
				heap = NULL;
				n = 0;
				printf("\n\n Heap deleted\n\n");
		}
	}
	while(option != 11);
	//getch();
	return 0;
}

int insert_heap_type()
{
	int heap_type = -1;
	while(heap_type != 1 && heap_type != 0)
	{
		printf("\n Enter 1 for MAX\n Enter 0 for MIN\n");
		printf("\n Enter the type of Heap : ");
		scanf("%d",&heap_type);
		if(heap_type != 1 && heap_type != 0)
			printf("\n Attention!! You entered a wrong Option!!\n");
	}
	return heap_type;
}
int *insert_node(int *heap, int n, int val, int heap_type)
{
	int temp;
	n = n + 1;
	int pos = n - 1; //ACCOUNTING FOR ZERO INDEXING
	int parent;
	heap = (int *)realloc(heap, n*sizeof(int));
	heap[pos] = val;
	while(pos>0)
	{
		parent = (pos-1)/2;
		if(heap_type)
		{
			if(val>heap[parent])
			{
				temp = heap[parent];
				heap[parent] = heap[pos];
				heap[pos] = temp;
			}
		}
		else
		{
			if(val<heap[parent])
			{
				temp = heap[parent];
				heap[parent] = heap[pos];
				heap[pos] = temp;
			}
		}
		pos = parent;
	}
	return heap;
}

int *delete_node(int *heap, int n, int heap_type)
{
	int temp;
	int pos = n-1;
	temp = heap[pos];
	heap[pos] = heap[0];
	heap[0] = temp;

	n = n - 1;
	heap = (int *)realloc(heap,n*(sizeof(int)));

	int parent = 0, left = 1, right = 2;

	while(left<n-1)
	{
		if(heap_type)
		{
			if (heap[parent]>heap[left] && heap[parent]>heap[right])
				return heap;

			if(heap[left]>heap[right])
			{
				temp = heap[parent];
				heap[parent] = heap[left];
				heap[left] = temp;
				parent = left;
			}
			else
			{
				temp = heap[parent];
				heap[parent] = heap[right];
				heap[right] = temp;
				parent = right;
			}
		}
		else
		{
			if (heap[parent]<heap[left] && heap[parent]<heap[right])
				return heap;

			if(heap[left]<heap[right])
			{
				temp = heap[parent];
				heap[parent] = heap[left];
				heap[left] = temp;
				parent = left;
			}
			else
			{
				temp = heap[parent];
				heap[parent] = heap[right];
				heap[right] = temp;
				parent = right;
			}
		}
		left = 2*parent + 1;
		right = left + 1;
	}

	return heap;
}

int extract_extremum(int *heap, int n, int heap_type)
{
	int extremum = heap[0];
	heap = delete_node(heap, n, heap_type);
	return extremum;
}

int extract_antapex(int *heap, int n, int heap_type)
{
	int antapex = heap[0];
	for(int i = 1; i < n; i++)
	{
		if(heap_type)
			if(heap[i]<antapex)
				antapex = heap[i];
		else
			if(heap[i]>antapex)
				antapex = heap[i];
	}
	return antapex;
}

void heap_sort(int *heap, int n, int heap_type)
{
	int i, j, val, ntemp = n;
	int *temp_heap;
	temp_heap = (int *)malloc(n*sizeof(int));
	for(i = 0; i < n; i++)
		temp_heap[i] = heap[i];

	printf("\n Original Heap : \n\n");
	for(i = 0; i < n; i++)
		printf(" %d ", temp_heap[i]);
	printf("\n\n");

	printf(" Sorted Array : \n\n");
	for(i = 0; i < n; i++)
	{
		val = temp_heap[0];
		temp_heap = delete_node(temp_heap, ntemp, heap_type);
		printf(" %d ", val);
		ntemp -= 1;
	}
	printf("\n\n");
}

void reverse_heap_sort(int *heap, int n, int heap_type)
{
	int i, j, ntemp = n;
	int *temp_heap;
	temp_heap = (int *)malloc(n*sizeof(int));
	for(i = 0; i < n; i++)
		temp_heap[i] = heap[i];

	int *stack;
	stack = (int *)malloc(n*sizeof(int));
	int si = 0;

	for(i = 0; i < n; i++)
	{
		stack[si] = temp_heap[0]; //Push into Stack
		temp_heap = delete_node(temp_heap, ntemp, heap_type);
		ntemp -= 1;
		si += 1;
	}

	printf("\n Sorted in Reverse Order : \n\n");
	//STACK
	for(i = si-1; i >= 0; i--)
		printf(" %d ", stack[i]);
	printf("\n\n");
}

void heap_array(int *heap, int n)
{
	for(int i = 0; i < n; i++)
		printf(" %d ",heap[i]);
}

void visualize_heap(int *heap, int n)
{
	int parent, child;

	printf("\n Hold On!! Generating Tree...\n\n");

	int i = 0;
	
	FILE *fptr;
	fptr = fopen("heap.dot","w");
	
	if(fptr==NULL)
	{
		printf("\nError opening file\n");
		exit(1);
	}

	fprintf(fptr,"%s","digraph G {\n");
	fflush(fptr);

	for(;i<n/2;i++)
	{
		fprintf(fptr,"%d -> %d;\n",heap[i],heap[2*i+1]);
		if (2*i+2 < n)
			fprintf(fptr,"%d -> %d;\n",heap[i],heap[2*i+2]);
		fflush(fptr);
	}

	fprintf(fptr,"%s","}");
	fflush(fptr);

	fclose(fptr);

	system("dot -Tpng heap.dot -o heap.png");

	printf(" You have 5 seconds. The window will automatically close after that.\n");
	system("python showGraph.py -f heap.png");
}