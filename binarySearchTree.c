#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>

#define MAX_FILENAME_LEN 50
#define MAX_CMD_LEN 100
#define MAX_SUBTREE_LEN 20

struct node
{
	int data;
	struct node *left, *right;
};

struct node *root;
//Can declare = NULL here;
//Then we won't need the create_bt or create_bst function
//However going as per the book, we will use the function
//struct node *create_bt(struct node *);
struct node *create_bst(struct node *);

struct node *insert_node(struct node *, int);
struct node *delete_node(struct node *, int);

void preorder(struct node *);
void postorder(struct node *);
void inorder(struct node *);
void levelorder(struct node *);
void printCurrLevel(struct node *, int);

struct node *construct_from_traversal();
struct node *construct_from_inpre(int *);
struct node *construct_from_impost(int *);

struct node *search_tree(struct node *, int);
struct node *find_largest_node(struct node *);
struct node *find_smallest_node(struct node *);

int height_tree(struct node *);
int lowest_depth(struct node *);
int num_internal_nodes(struct node *);
int num_external_nodes(struct node *);
int num_nodes(struct node *);

struct node *balance_tree(struct node *);

struct node *delete_bst(struct node *);

void visualize_tree(struct node *);

int main()
{
	printf("\n\n How you doin'? \n");
	printf("\n Program for BINARY SEARCH TREE \n\n");
	int option, val;
	//char filename[MAX_FILENAME_LEN], cmd[MAX_CMD_LEN];
	struct node *ptr;
	create_bst(root);
	//clrscr();
	do
	{
		printf("\n ************************* MAIN MENU ************************** \n");
		printf(" 1.  Insert New Node \n");
		printf(" 2.  Delete Node \n");
		printf(" 3.  Search Tree \n");
		printf(" 4.  Preorder Traversal \n");
		printf(" 5.  Inorder Traversal \n");
		printf(" 6.  Postorder Traversal \n");
		printf(" 7.  Levelorder Traversal \n");
		printf(" 8.  Find the Smallest Node \n");
		printf(" 9.  Find the Largest Node \n");
		printf(" 10. Count the total number of Nodes \n");
		printf(" 11. Count the total number of External Nodes \n");
		printf(" 12. Count the total number of Internal Nodes \n");
		printf(" 13. Determine the Height of the Tree \n");
		printf(" 14. Determine the Lowest Depth of the Tree \n");
		printf(" 15. Balance Tree \n");
		printf(" 16. Visualize Tree \n");
		printf(" 17. Delete the Tree \n");
		printf(" 18. EXIT \n");
		printf("\n\n Enter what you wanna do :: ");
		scanf("%d", &option);
		switch(option)
		{
			case 1:
				printf("\n Enter Value of New Node : ");
				scanf("%d", &val);
				root = insert_node(root, val);
				break;
			case 2:
				printf("\n Enter Value of the Node : ");
				scanf("%d", &val);
				//ptr = search_tree(root, val);
				root = delete_node(root, val);//ptr);
				break;
			case 3:
				printf("\n Enter Value of the Node : ");
				scanf("%d", &val);
				ptr = search_tree(root, val);
				break;
			case 4:
				printf("\n The elements of the Tree in Preorder are : \n");
				preorder(root);
				break;
			case 5:
				printf("\n The elements of the Tree in Inorder are : \n");
				inorder(root);
				break;
			case 6:
				printf("\n The elements of the Tree in Postorder are : \n");
				postorder(root);
				break;
			case 7:
				printf("\n The elements of the Tree in Levelorder are : \n");
				levelorder(root);
				break;
			case 8:
				ptr = find_smallest_node(root);
				printf("\n The Smallest Node in the Tree : %d", ptr->data);
				break;
			case 9:
				ptr = find_largest_node(root);
				printf("\n The Largest Node in the Tree : %d", ptr->data);
				break;
			case 10:
				printf("Total number of nodes in the Tree : %d", num_nodes(root));
				break;
			case 11: 
				printf("Number of Internal Nodes in the Tree : %d",num_internal_nodes(root));
				break;
			case 12:
				printf("Number of External Nodes in the Tree : %d",num_external_nodes(root));
				break;
			case 13:
				printf("Height of the Tree : %d", height_tree(root));
				break;
			case 14:
				printf("Lowest Depth of the Tree : %d", lowest_depth(root));
				break;
			case 15:
				root = balance_tree(root);
				break;
			case 16:
				visualize_tree(root);
				break;
			case 17:
				root = delete_bst(root);
				printf("\n\nBinary Search Tree deleted\n\n");
		}
	}
	while(option != 18);
	//getch();
	return 0;
}

struct node *create_bst(struct node *root)
{
	root = NULL;
}

struct node *insert_node(struct node *root, int val)
{
	struct node *ptr, *parentptr, *nodeptr;
	ptr = (struct node *)malloc(sizeof(struct node));
	ptr->data = val;
	ptr->left = NULL;
	ptr->right = NULL;

	if(root == NULL)
	{
		root = ptr;
		root->left = NULL;
		root->right = NULL;
	}
	else
	{
		parentptr = NULL;
		nodeptr = root;
		while(nodeptr!=NULL)
		{
			parentptr=nodeptr;
			if(val<nodeptr->data)
				nodeptr=nodeptr->left;
			else
				nodeptr=nodeptr->right;
		}
		if(val<parentptr->data)
			parentptr->left = ptr;
		else
			parentptr->right = ptr;
	}
	return root;
}

struct node *delete_node(struct node *root, int val)
{
	struct node *suc;

	if(root==NULL)
	{
		printf("\nNode not present in the Tree\n");
		return root;
	}
	if(val<root->data)
		root->left = delete_node(root->left,val);
	else if (val>root->data)
		root->right = delete_node(root->right,val);
	else
	{
		if((root->left != NULL)&&(root->right != NULL))
		{
			suc = find_largest_node(root->left); //find_smallest_node(root->right);
			root->data = suc->data;
			root->left = delete_node(root->left,suc->data);
			//root->right = delete_node(root->right,suc->data);
		}
		else if((root->left==NULL)&&(root->right==NULL))
			root = NULL;
		else if((root->left==NULL)&&(root->right!=NULL))
			root = root->right;
		else
			root = root->left;
	}
	return root;
}

struct node *search_tree(struct node *root, int val)
{
	int found = 0;
	if(root==NULL)
	{
		printf("NOT FOUND\n");
		printf("\nI'm SORRY, I can't find your node twin!!\n");
		printf("You could've earned millions in Vegas\n\n");
		return NULL;
	}
	else
	{
		printf("[%d] -> ",root->data);
		if(val<root->data)
			root = search_tree(root->left,val);
		else if(val>root->data)
			root = search_tree(root->right,val);
		else
		{
			printf("FOUND!!\nHey! You found your node twin!!\n");
			return root;
		}
	}
}

void preorder(struct node *root)
{
	if(root!=NULL)
	{
		printf("%d\t",root);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(struct node *root)
{
	if(root!=NULL)
	{
		inorder(root->left);
		printf("%d\t",root->data);
		inorder(root->right);
	}
}

void postorder(struct node *root)
{
	if(root!=NULL)
	{
		postorder(root->left);
		postorder(root->right);
		printf("%d\t",root->data);
	}
}

void levelorder(struct node *root)
{
	int h = height_tree(root);
	for(int i = 1; i <= h; i++)
	{
		printCurrLevel(root,i);
		printf("\n");
	}	
}

void printCurrLevel(struct node *root, int level)
{
	if(root==NULL)
		return;
	if(level==1)
		printf("%d\t",root->data);
	else if(level>1)
	{
		printCurrLevel(root->left,level-1);
		printCurrLevel(root->right,level-1);
	}
}

struct node *find_smallest_node(struct node *root)
{
	if((root!=NULL) && (root->left!=NULL))
		return find_smallest_node(root->left);
	else
		return root;
}

struct node *find_largest_node(struct node *root)
{
	if((root!=NULL) && (root->right!=NULL))
		return find_largest_node(root->right);
	else
		return root;
}

int num_nodes(struct node *root)
{
	if(root==NULL)
		return 0;
	else
		return(num_nodes(root->left)+num_nodes(root->right)+1);
}

int num_external_nodes(struct node *root)
{
	if(root==NULL)
		return 0;
	else if((root->left==NULL)&&(root->right==NULL))
		return 1;
	else
		return (num_external_nodes(root->left)+num_external_nodes(root->right));
}

int num_internal_nodes(struct node *root)
{
	if((root==NULL)||((root->left==NULL)&&(root->right==NULL)))
		return 0;
	else
		return (num_internal_nodes(root->left) + num_internal_nodes(root->right)+1);
}

int height_tree(struct node *root)
{
	int lht, rht;
	if(root==NULL)
		return 0;
	else
	{
		lht = height_tree(root->left);
		rht = height_tree(root->right);
		if(lht>rht)
			return (lht+1);
		else
			return (rht+1);
	}
}

int lowest_depth(struct node *root)
{
	int ld, rd;
	if(root==NULL)
		return 0;
	else if((root->left==NULL)&&(root->right==NULL))
		return 1;
	else if(root->left == NULL)
		return (lowest_depth(root->right)+1);
	else if(root->right == NULL)
		return (lowest_depth(root->left)+1);
	else
	{
		ld = lowest_depth(root->left);
		rd = lowest_depth(root->right);
		if(ld<rd)
			return (ld+1);
		else
			return (rd+1);
	} 
}

struct node *delete_bst(struct node *root)
{
	if(root!=NULL)
	{
		delete_bst(root->left);
		delete_bst(root->right);
		free(root);
	}
}

struct node *balance_tree(struct node *root)
{
	return NULL;
}

void visualize_tree(struct node *root)
{
	printf("\n Hold On!! Generating Tree...\n\n");

	int n = num_nodes(root);
	int i = 0;
	int j = 0;
	int label = 0;
	FILE *fptr;
	fptr = fopen("graph.dot","w");
	
	if(fptr==NULL)
	{
		printf("\nError opening file\n");
		exit(1);
	}

	struct node *nodearr = (struct node *)malloc(n*sizeof(struct node));
	struct node *ptr;

	nodearr[0] = *root;
	i++;

	fprintf(fptr,"%s","digraph G {\n");
	fflush(fptr);

	while(j<i)
	{
		ptr = &nodearr[j];
		
		if(ptr->left!=NULL)
		{
			nodearr[i] = *(ptr->left);
			i++;
			fprintf(fptr,"%d -> %d;\n",ptr->data,ptr->left->data);
		}
		else
		{
			fprintf(fptr,"%d -> N%d;\n",ptr->data,label);
			label++;
		}

		if(ptr->right!=NULL)
		{
			nodearr[i] = *(ptr->right);
			i++;
			fprintf(fptr,"%d -> %d;\n",ptr->data,ptr->right->data);
		}
		else
		{
			fprintf(fptr,"%d -> N%d;\n",ptr->data,label);
			label++;
		}
		
		j++;
		fflush(fptr);
	}

	for(i = 0; i < label; i++)
		fprintf(fptr,"N%d [label = \"NULL\"] [shape=rectangle]\n",i);

	fprintf(fptr,"%s","}");
	fflush(fptr);

	fclose(fptr);

	system("dot -Tpng graph.dot -o graph.png");
	system("python showGraph.py -f graph.png");
}