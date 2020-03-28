#include <stdio.h>
#include <stdlib.h>

void main()
{
	int MAX_NUM = 10;
	int *seq = (int *)malloc(MAX_NUM*sizeof(int));
	int num = 0, i, j, num_inps = 0;
	char c;

	//READING THE SEQUENCE
	printf("Input : \n");
	while(scanf("%c",&c))
	{
		//printf("Input read : %d\n",c);
		if (c!='\n' && c!=' ')
			num = num*10+c-'0';

		if(c==' '||c=='\n')
		{
			//IF NUMBER OF INPUTS EXCEEDS SIZE OF ARRAY
			num_inps++;
			if(num_inps > MAX_NUM)
			{
				//printf("MEMORY EXCEEDED!! SIZE Increased!!\n");
				seq = (int *)realloc(seq,2*MAX_NUM*sizeof(int));
				MAX_NUM = 2*MAX_NUM;
			}
			//printf("Input number : %d; Input : %d\n",num_inps,num);
			seq[num_inps-1] = num;
			num = 0;			
		}

		if(c=='\n')
			break;
	}

	printf("\nSequence : \n");
	for(i=0;i<num_inps;i++)
		printf("%d ",seq[i]);
	printf("\n");

	//FINDING THE LONGEST INCREASING SEQUENCE
	int *longest_inc_seq = (int *)malloc(num_inps*sizeof(int));

	longest_inc_seq[0] = 1;
	int longest_len = 1;

	for(i=1;i<num_inps;i++)
	{
		longest_inc_seq[i] = 1;
		longest_len = 1;

		for(j=0;j<i;j++)
			if((seq[j]<seq[i])&&(longest_inc_seq[j]+1 > longest_len))
				longest_len = longest_inc_seq[j]+1;

		longest_inc_seq[i] = longest_len;
	}
	
	printf("Length of longest increasing sequence : ");
	printf("%d\n",longest_len);

	//wE HAVE TO REPLACE THE REMAINING ELEMENTS BY INTERMEDIATE NUMBERS
	printf("Minimum number of integers that must be changed");
	printf("to make the input sequence strictly increasing : \n");
	printf("\n%d\n\n",num_inps-longest_len);

}
