#include <stdio.h>
#include <stdlib.h>

int all_zero(int *N, int k)
{
	int zero_flag = 1;
	for(int i=0; i < k; i++)
		if(N[i]!=0)
		{
			zero_flag=0;
			break;
		}

	return zero_flag;
}

int sprague_grundy_optimal_move(int n, int m)
{
	int opt_move = 0;

	// COMPUTER IS IN P POSITION
	//WHATEVER INPUT YOU GIVE
	//USER WILL WIN
	if(n % (m+1) == 0)
		opt_move = m;
	//N POSITION
	//PUSH USER TO P POSITION
	else
		opt_move = n % (m+1);

	return opt_move;
}

int is_in_P_position(int n, int m)
{
	if (n % (m+1) == 0)
		return 1;
	else
		return 0; 
}

int all_P(int *N, int* M, int k)
{
	for(int i = 0; i < k; i++)
		if(is_in_P_position(N[i],M[i])==0)
			return 0;
	return 1;
}

int *sprague_grundy_multi_heap_optimal_move(int *N, int *M, int k)
{
	int i,j;
	static int move[2];
	int N_min,N_min_ind;

	if(all_P(N,M,k))
	{
		i = 0;
		while(N[i]==0)
			i++;
		N_min = N[i];
		N_min_ind = i;

		for(j=i+1;i<k;i++)
		{
			if(N[j]<N_min && N[j]!=0)
				N_min_ind=j;
		}
		
		move[0] = N_min_ind;
		move[1] = sprague_grundy_optimal_move(N[N_min_ind],M[N_min_ind]);

		return move;
	}
	
	for(i = 0; i < k; i++)
	{
		if(is_in_P_position(N[i],M[i])==0)
		{
			move[0] = i;
			move[1] = sprague_grundy_optimal_move(N[i],M[i]);
		}
	}

	return move;
}


void main()
{
	int i,j,k;
	scanf("%d",&k);
	int *N = (int *)malloc(k*sizeof(int));
	int *M = (int *)malloc(k*sizeof(int));

	for(i=0;i<k;i++)
		scanf("%d %d",&N[i],&M[i]);
	
	char c;
	//CLEARING THE LF from input buffer
	c = getchar();

	/*int *N_copy = (int *)malloc(k*sizeof(int));

	for(i=0;i<k;i++)
		N_copy[i] = N[i];

	int max_moves = 0;
	for(i=0;i<k;i++)
		max_moves+=(M[i]*2);

	int *moves_heaps = (int *)malloc(max_moves*sizeof(int));
	int *moves = (int *)malloc(max_moves*sizeof(int));*/

	int heap_index, user_move, comp_move, comp_move_index, num = 0, win_user = 0;
	int *comp_opt_move;
	i = 0;

	int zero_flag=0;

	//printf("\nLet's play. You go first USER!! \n\n");

	while(all_zero(N,k)!=1)
	{
		//USER MOVE
		printf("(");
		while(1)
		{
			//ENTERING RAW MODE
			//BUFFER IS DISABLED
			//WHATEVER IS TYPED IS SENT STRAIGHT TO c
			//INSTEAD OF STORING IN BUFFER 
			//TO BE SENT AFTER PRESSING ENTER KEY
			system("/bin/stty raw");

			//NO NEED TO PRESS ENTER TO TAKE INPUT
			c = getchar();

			//DISABLING RAW MODE AND ENTERING COOKED MODE AGAIN MANUALLY
			system("/bin/stty cooked");

			if (c!=',' && c!=')')
				num = num*10+c-'0';
			//HEAP INDEX
			if(c==',')
			{
				heap_index = num;
				num = 0;		
			}
			//USER MOVE
			if(c==')')
			{
				user_move = num;
				num = 0;
				break;
			}
		}
		
		//moves_heaps[i] = heap_index-1;
		//moves[i] = user_move;
		//i++;
		N[heap_index-1] = N[heap_index-1]-user_move;

		/*printf("\nState after User Move : ");
		for(j=0;j<k;j++)
			printf("%d ",N[j]);
		printf("\n");*/

		zero_flag = all_zero(N,k);
		if(zero_flag==1)
		{
			win_user = 1;
			break;
		}

		//COMPUTER MOVE
		comp_opt_move = sprague_grundy_multi_heap_optimal_move(N,M,k);
		comp_move_index = comp_opt_move[0];
		comp_move = comp_opt_move[1];
		//moves_heaps[i] = comp_move_index;
		//moves[i] = comp_move;
		//i++;
		printf("(%d,%d)",comp_move_index+1,comp_move);

		N[comp_move_index] = N[comp_move_index] - comp_move;

		/*printf("\nState after Comp Move : ");
		for(j=0;j<k;j++)
			printf("%d ",N[j]);
		printf("\n");*/
		
		/*for(j=0;j<i;j++)
			printf("(%d, %d) ",moves_heaps[j]+1,moves[j]);
		printf("\n");*/

		zero_flag = all_zero(N,k);
		if(zero_flag==1)
			break;

	}

	/*for(j=0;j<i;j++)
		printf("(%d, %d) ",moves_heaps[j]+1,moves[j]);
	printf("\n");*/

	printf("\n\n");
	if(win_user)
		printf("NO\n");
	else
		printf("YES\n");
}
