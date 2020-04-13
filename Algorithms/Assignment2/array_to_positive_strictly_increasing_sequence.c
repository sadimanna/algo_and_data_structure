#include <stdio.h>
#include <stdlib.h>

int LIS(int *seq, int arrlen)
{
	//FINDING THE LONGEST INCREASING SEQUENCE
	int *longest_inc_seq = (int *)malloc(arrlen*sizeof(int));
	int *smallest_elem_of_lis = (int *)malloc(arrlen*sizeof(int));
	int  prev_lis_se = 0;

	int longest_len = 1;
	longest_inc_seq[0] = 1;
	smallest_elem_of_lis[0] = 0;
	int i = arrlen-1;

	for(i=1;i<arrlen;i++)
	{
		longest_inc_seq[i]=1;
		smallest_elem_of_lis[i] = i;
		for(int j=0;j<i;j++)
		{
			if((seq[i]>seq[j])&&(seq[i]-seq[j])>=(i-j))
			{
				if(longest_inc_seq[j]+1 > longest_inc_seq[i])
				{
					smallest_elem_of_lis[i] = smallest_elem_of_lis[j];
					longest_inc_seq[i] = longest_inc_seq[j]+1;
				}
			}
		}
		if((longest_len < longest_inc_seq[i])&&(seq[smallest_elem_of_lis[i]]-1>=smallest_elem_of_lis[i]-prev_lis_se))
		{
			
			longest_len = longest_inc_seq[i];
			prev_lis_se = smallest_elem_of_lis[i];
		}
	}
	return longest_len;
}

void main()
{
	int MAX_NUM = 10;
	int *seq = (int *)malloc(MAX_NUM*sizeof(int));
	int num = 0, i, j, num_inps = 0;
	char c;

	//READING THE SEQUENCE
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
			seq[num_inps-1] = num;
			num = 0;			
		}

		if(c=='\n')
			break;
	}

	/*printf("Sequence : \n");
	for(i=0;i<num_inps;i++)
		printf("%d ",seq[i]);
	printf("\n");*/

	int longest_len = LIS(seq, num_inps);

	//wE HAVE TO REPLACE THE REMAINING ELEMENTS BY INTERMEDIATE NUMBERS
	//printf("Minimum number of integers that must be changed");
	//printf("to make the input sequence strictly increasing : \n");
	printf("\n%d\n\n",num_inps-longest_len);

}
