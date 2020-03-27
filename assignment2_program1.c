#include <stdio.h>
#include <stdlib.h>

/*  1 bin n balls
	Can move 1<= m < n balls from the bin
	User input n and m
	First move : User
	Output : Whether it is possible to defeat user
			 no matter what move the user makes
*/

int get_maxlen(int dec)
{
	int maxlen = 1;
	int mult2 = 1;
	//CALCULATING THE SMALLEST POWER OF 2, THE DECIMAL NUMBER DOES NOT EXCEED
	while(mult2<dec)
	{
		maxlen++;
		mult2*=2;
	}
	if(mult2>dec)
		maxlen--;
	//printf("\nFOR %d maximum number of bits required is %d\n",dec,maxlen);
	return maxlen;
}

int *dec2bin(int dec, int len)
{
	static int *binstr;
	int maxlen;
	//CALCULATING MAXIMUM NUMBER OF BITS REQUIRED
	if (len==0)
		maxlen = get_maxlen(dec);
	else
		maxlen = len;

	//printf("FOR %d maximum number of bits required is %d\n",dec,maxlen);
	binstr = (int *)malloc(maxlen*sizeof(int));

	int tempdec, i = maxlen-1;
	tempdec = dec;
	//CALCULATING BINARY REPRESENTATION OF THE DECIMAL NUMBER
	while(i>=0)
	{
		binstr[i]=tempdec%2;
		tempdec/=2;
		i--;
	}

	return binstr;
}

int optimalMove(int n, int m)
{
	int *bin_n;
	bin_n = dec2bin(n,0);
	int n_len = get_maxlen(n);
	int leftmost_1 = 0;
	int move_val = 1, final_move_val = 0, i, j=0;

	for(i=0;i<n_len;i++)
	{
		if(bin_n[i]==1)
			leftmost_1 = n_len - 1 - i;
		
		//CALCULATE THE MOVE VALUE
		while(j<leftmost_1)
		{
			move_val*=2;
			j++;
		}
		j = 0;
		
		//CHECK IF THE MOVE VALUE IS WITHIN THE LIMIT
		if (move_val+final_move_val <= m)
		{
			//CHECK IF THE REDUCED n VALUE IS A MULTIPLE OF 2
			if((n-(move_val+final_move_val))%2!=0)
				final_move_val+=move_val;
			else
			{
				return final_move_val+move_val;
			}
		}
		move_val = 1;
	}

	//EVEN AFTER ITERATION OVER ALL THE 1s IF THE FINAL MOVE VALUE
	//DOES NOT REDUCE n TO A MULTIPLE OF 2, THEN SET IT TO 1
	if(final_move_val!=0 && (n-final_move_val)%2!=0)
		final_move_val = move_val;

	//FINAL VALUE WILL NOT BE SET IF MOVE_VAL IS GREATER THN LIMIT
	//HENCE SETTING IT TO 1
	if (final_move_val==0)
		return 1;

	return final_move_val;
}

void visualize(int *moves, int n, int m, int num_moves)
{
	int i=0,j;

	int *leftovers = (int *)malloc((num_moves+1)*sizeof(int));
	leftovers[0] = n;

	for(i=0;i<num_moves;i++)
		leftovers[i+1]=leftovers[i] - moves[i];

	printf("_ ");
	for(i=0;i<num_moves;i++)
	{
		if(i%2==0)
			printf("U ");
		else
			printf("C ");
	}
	printf("<- Movers\n");

	printf("0 ");
	for(i=0;i<num_moves;i++)
		printf("%d ",moves[i]);
	printf("<- Moves\n");

	for(i=0;i<num_moves+1;i++)
		printf("%d ",leftovers[i]);
	printf("<- Remaining stones\n\n");

	int y_lim = n;
	for(i=0;i<n;i++)
	{
		for(j=0;j<num_moves+1;j++)
		{
			if(leftovers[j]==y_lim)
			{
				printf("* ");
				leftovers[j]--;
			}
			else
				printf("  ");
		}
		y_lim--;
		printf("\n");
	}
	for(j=0;j<num_moves+1;j++)
		printf("- ");
	printf("\n");
}


void main()
{
	int n, m;
	printf("Enter n and m :: ");
	scanf("%d %d",&n,&m);
	int n_val = n;
	int user_move, comp_move, max_moves, i=0,j, win_user = 0;
	max_moves = n/m+1;
	int *moves = (int *)malloc(max_moves*sizeof(max_moves));

	printf("\nLet's play. You go first USER!! \n\n");
	while(n>0)
	{
		//USER MOVE
		//printf("Enter your move USER :: ");
		scanf("%d",&user_move);
		if(user_move>m)
		{
			printf("Bad move. Setting to default value.\n");
			user_move = m;
		}
		if(user_move==0)
		{
			printf("Bad move. Setting to lowest possible value.\n");
			user_move = 1;
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
		comp_move = optimalMove(n,m);
		
		moves[i] = comp_move;
		i++;
		n = n-comp_move;
		
		if(n==0)
		{
			break;
		}

		for(j = 0;j<i;j++)
			printf("%d ",moves[j]);
		printf("\n");
	}

	for(j = 0;j<i;j++)
		printf("%d ",moves[j]);
	printf("\n\n");

	if(win_user)
		printf("YES\n");
	else
		printf("NO\n");

	printf("\nVISUALIZATION\n\n");
	visualize(moves,n_val,m,i);

}