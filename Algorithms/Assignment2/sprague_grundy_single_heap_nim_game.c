#include <stdio.h>
#include <stdlib.h>

/*  1 bin n balls
	Can move 1<= m < n balls from the bin
	User input n and m
	First move : User
	Output : Whether it is possible to defeat user
			 no matter what move the user makes
*/

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

void main()
{
	int n, m, num=0;
	char c;
	//printf("Enter n and m :: ");
	scanf("%d %d",&n,&m);

	//CLEARING THE LAGGING ENTER AND '\n'
	c = getchar();

	int n_val = n;
	int user_move, comp_move, max_moves, i=0,j, win_user = 0;
	max_moves = n/m+1;
	int *moves = (int *)malloc(max_moves*sizeof(max_moves));

	
	//printf("\nLet's play. You go first USER!! \n\n");
	while(n>0)
	{
		

		//USER MOVE
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
			
			//CONSTRUCTING THE INPUT
			if (c!=' ')
				num = num*10+c-'0';
			
			//STORING THE INPUT ONCE SPACE IS ENCOUNTERED
			if(c==' ')
			{
				user_move = num;
				num = 0;
				break;			
			}
		}
		
		moves[i] = user_move;
		i++;
		n = n-user_move;
		if(n==0)
		{
			win_user = 1;
			break;
		}
		//COMPUTER MOVE
		comp_move =  sprague_grundy_optimal_move(n,m);
		
		moves[i] = comp_move;
		i++;
		n = n-comp_move;
		
		printf("%d ",comp_move);
		if(n==0)
		{
			break;
		}

		/*for(j = 0;j<i;j++)
			printf("%d ",moves[j]);
		printf("\n");*/
	}

	/*for(j = 0;j<i;j++)
		printf("%d ",moves[j]);
	printf("\n\n");*/
	printf("\n\n");
	if(win_user)
		printf("NO\n");
	else
		printf("YES\n");

}
