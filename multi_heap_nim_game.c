#include <stdio.h>
#include <stdlib.h>

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

int bin2dec(int *binstr, int len)
{
	if (len==1)
		return binstr[0];

	int decnum = 0;
	int coeff = 1;
	//CONVERTING THE BINARY STRING TO DECIMAL VALUE
	for(int i=len-1;i>=0;i--)
	{
		decnum+=binstr[i]*coeff;
		coeff*=2;
	}
	return decnum;
}

int xorb(int b1, int b2)
{
	//SINGLE BIT XOR
	if (b1==1 && b2==1)
		return 0;
	if (b1==1 && b2==0)
		return 1;
	if (b1==0 && b2==1)
		return 1;
	if (b1==0 && b2==0)
		return 0;
}

int *xor(int *bin_num1, int *bin_num2, int len)
{
	int *xorstr = (int *)malloc(len*sizeof(int));
	//CALCULATING BIT BY BIT XOR
	for(int i=len-1;i>=0;i--)
		xorstr[i] = xorb(bin_num1[i],bin_num2[i]);

	return xorstr;
}


int nimsum(int *num_arr,int num_num)
{
	int *bin_num1, *bin_num2, *xor_num1_num2;
	int len=0, i=0, templen, decval = num_arr[0];
	//CALCULATING THE MAXIMUM NUMBER OF BITS REQUIRED
	for(;i<num_num;i++)
	{
		templen = get_maxlen(num_arr[i]);
		if(templen>len)
			len=templen;
	}
	//CALCULATING THE XOR BETWEEN ALL THE VALUES IN num_arr
	for(i=1;i<num_num;i++)
	{
		bin_num1 = dec2bin(decval,len);
		bin_num2 = dec2bin(num_arr[i],len);
		xor_num1_num2 = xor(bin_num1,bin_num2,len);

		decval = bin2dec(xor_num1_num2,len);
	}
		
	return decval;
}

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

int *optimal_move(int *N, int *M, int k)
{
	int i,j;
	static int move[2];
	int opt_move = 0,temp_val = 0,opt_index = -1;
	int N_max = 0, N_min, N_max_ind, N_min_ind;
	int s = nimsum(N,k);
	int d;
	int maxlen = 0;
	int *bin_N_i;

	//CALCULATING THE HEAP WITH MAX NUMBER OF STONES
	for(i=0;i<k;i++)
	{
		if(N[i]>N_max)
		{
			N_max=N[i];
			N_max_ind = i;
		}
	}
	//GET MAXIMUM NUMBER OF BITS REQUIRED
	maxlen = get_maxlen(N_max);

	//GETTING INDEX OF MSB OF NIMSUM
	d = get_maxlen(s);
	//printf("d :: %d\n",d);
	//IS NIMSUM IS ALREADY ZERO THEN PICK THE HEAP WITH MINIMUM NUMBER OF STONES
	//AND REMOVE SOME STONES SUCH THAT THE REMAINING STONES IS A MULTIPLE OF 
	//THE MAXIMUM ALLOWABLE NUMBER OF STONES THAT CAN BE REMOVED FROM THE HEAP
	if(d==0)
	{
		N_min = N_max;
		N_min_ind = N_max_ind;

		for(i=0;i<k;i++)
		{
			if(N[i]<N_min && N[i]!=0)
				N_min_ind=i;
		}
		opt_index = N_min_ind;
		//IF NUMBER OF STONES IS GREATER THAN EVEN MULTIPLE OF MAX ALLOWABLE WITHDRAWAL
		//BUT LESS THAN THE HIGHER ODD MULTIPLE
		if((N[N_min_ind] / M[N_min_ind]) % 2 == 0)
		{
			//IF IT IS AN EXACT EVEN MULTIPLE
			if((N[N_min_ind] % M[N_min_ind])==0)
				//REMOVE HALF OF MAX ALLOWABLE STONES
				opt_move = M[N_min_ind] / 2;
			else
				//REMOVE THAT MANY NUMBER OF STONES SO THAT 
				//THE REMAINING STONES IS AN EXACT MULTIPLE
				opt_move = N[N_min_ind] % M[N_min_ind];
		}
		//IF NUMBER OF STONES IS GREATER THAN ODD MULTIPLE OF MAX ALLOWABLE WITHDRAWAL
		//BUT LESS THAN THE HIGHER EVEN MULTIPLE
		if((N[N_min_ind] / M[N_min_ind]) % 2 != 0)
		{
			//IF IT IS AN EXACT MULTIPLE
			if((N[N_min_ind] % M[N_min_ind])==0)
				//REMOVE MAX ALLOWABLE NUMBER OF STONES
				opt_move = M[N_min_ind];
			else
				//REMOVE THAT MANY NUMBER OF STONES
				//THAT WOULD LEAVE 1 MORE THAN AN EXACT MULTIPLE
				opt_move = N[N_min_ind] % M[N_min_ind] - 1;
		}
		//IF STILL ZERO
		//REMOVE MAX ALLOWABLE
		if(opt_move==0)
			opt_move = M[N_min_ind];

		move[0] = opt_index;
		move[1] = opt_move;

		return move;
	}

	//y_k = s XOR x_k
	//REMOVE x_k - y_k NUMBER OF STONES
	for(i=0;i<k;i++)
	{
		bin_N_i = dec2bin(N[i],maxlen);
		
		if(bin_N_i[maxlen-d]==1)
		{
			opt_index = i;
			opt_move = N[opt_index] - bin2dec(xor(dec2bin(N[opt_index],maxlen),dec2bin(s,maxlen),maxlen),maxlen);
			
			if ((opt_move <= M[opt_index]) &&(opt_move > 0))
				break;
			else if (opt_move > M[opt_index])
				opt_move = M[opt_index];
			else if (opt_move < 0)
				opt_move = -opt_move;
		}
	}

	move[0] = opt_index;
	move[1] = opt_move;

	return move;
}

void main()
{
	int i,j,k;
	scanf("%d",&k);
	int *N = (int *)malloc(k*sizeof(int));
	int *M = (int *)malloc(k*sizeof(int));

	int *N_copy = (int *)malloc(k*sizeof(int));

	for(i=0;i<k;i++)
		scanf("%d %d",&N[i],&M[i]);

	for(i=0;i<k;i++)
		N_copy[i] = N[i];

	int max_moves = 0;
	for(i=0;i<k;i++)
		max_moves+=(M[i]+1);

	int *moves_heaps = (int *)malloc(max_moves*sizeof(int));
	int *moves = (int *)malloc(max_moves*sizeof(int));

	int heap_index, user_move, comp_move, comp_move_index, win_user = 0;
	int *comp_opt_move;
	i = 0;

	int zero_flag=0;

	printf("\nLet's play. You go first USER!! \n\n");

	while(all_zero(N,k)!=1)
	{
		//USER MOVE
		scanf("%d %d",&heap_index,&user_move);
		if(user_move>M[heap_index-1])
		{
			printf("Invalid move. Enter Again.\n");
			scanf("%d",&user_move);
		}
		if(user_move==0)
		{
			printf("Invalid move. Enter Again.\n");
			scanf("%d",&user_move);
		}
		if(N[heap_index-1]==0)
		{
			printf("Invalid move. Size of heap %d is ZERO. Enter Again.\n",heap_index);
			scanf("%d %d",&heap_index,&user_move);
		}
		moves_heaps[i] = heap_index-1;
		moves[i] = user_move;
		i++;
		N[heap_index-1] = N[heap_index-1]-user_move;

		printf("State after User Move : ");
		for(j=0;j<k;j++)
			printf("%d ",N[j]);
		printf("\n");

		zero_flag = all_zero(N,k);
		if(zero_flag==1)
		{
			win_user = 1;
			break;
		}

		//COMPUTER MOVE
		comp_opt_move = optimal_move(N,M,k);
		comp_move_index = comp_opt_move[0];
		comp_move = comp_opt_move[1];
		moves_heaps[i] = comp_move_index;
		moves[i] = comp_move;
		i++;
		//printf("%d %d\n",comp_move_index+1,comp_move);

		N[comp_move_index] = N[comp_move_index] - comp_move;

		printf("State after Comp Move : ");
		for(j=0;j<k;j++)
			printf("%d ",N[j]);
		printf("\n");

		for(j=0;j<i;j++)
			printf("(%d, %d) ",moves_heaps[j]+1,moves[j]);
		printf("\n");
		
		zero_flag = all_zero(N,k);
		if(zero_flag==1)
			break;

		
	}

	if(win_user)
		printf("YES\n");
	else
		printf("NO\n");
}
