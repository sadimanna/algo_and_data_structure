#include <stdio.h>
#include <stdlib.h>

//CALCULATING MAXIMUM NUMBER OF BIT
//REQUIRED TO REPRESENT THE NUMBER
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

//DECIMAL TO BINARY CONVERSION
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

//BINARY TO DECIMAL CONVERSION
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

//BIT-BY-BIT XOR
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

//CALCULATING XOR OF TWO NUMBERS
int *xor(int *bin_num1, int *bin_num2, int len)
{
	int *xorstr = (int *)malloc(len*sizeof(int));
	//CALCULATING BIT BY BIT XOR
	for(int i=len-1;i>=0;i--)
		xorstr[i] = xorb(bin_num1[i],bin_num2[i]);

	return xorstr;
}

//CALCULATING NIMSUM
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

//CHECK IF ALL HEAPS ARE EMPTY
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

//OPTIMAL MOVE ACCORDING TO SPRAGUE-GRUNDY THEOREM
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

//CHECK IF IN P POSITION
int all_P(int *N, int* M, int k)
{
	int rems[k];

	for(int i=0;i<k;i++)
		rems[i] = N[i]%(M[i]+1);

	int nim_sum_sg = nimsum(rems,k);

	if(nim_sum_sg!=0)
		return nim_sum_sg;
	else 
		return 0;
}

int *sprague_grundy_multi_heap_optimal_move(int *N, int *M, int k)
{
	int i,j;
	static int move[2];
	int N_max,N_max_ind;
	int nim_sum_sg;
	//CALCULATE THE NIMSUM OF THE SG-VALUES
	nim_sum_sg = all_P(N,M,k);

	if(nim_sum_sg==0)
	{
		i = 0;
		while(N[i]==0)
			i++;
		N_max = N[i];
		N_max_ind = i;

		for(j=i+1;j<k;j++)
		{
			if(N[j]>N_max && N[j]!=0)
			{
				N_max = N[j];
				N_max_ind=j;
			}
		}
		
		move[0] = N_max_ind;
		move[1] = sprague_grundy_optimal_move(N[N_max_ind],M[N_max_ind]);

		return move;
	}

	//GET THE INDEX OF THE MOST SIGNIFICANT BIT
	int kth_bit = get_maxlen(nim_sum_sg);

	//CALCULATE THE OPTIMAL MOVE
	int *binstr;

	for(i = 0; i < k; i++)
	{
		binstr = dec2bin(N[i]%(M[i]+1),0);

		if(binstr[kth_bit-1]==1)
		{
			move[0] = i;
			move[1] = sprague_grundy_optimal_move(N[i],M[i]);
			break;
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
			printf("%d ",N[j]%(M[j]+1));
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
			printf("%d ",N[j]%(M[j]+1));
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
