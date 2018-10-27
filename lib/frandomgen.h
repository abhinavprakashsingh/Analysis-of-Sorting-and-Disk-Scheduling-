#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SORT_TEST_LIMIT		100		
#define SORT_TEST_MIN		10
#define SORT_SIZE_LIMIT		100
#define SORT_RANGE_LIMIT	2000
#define SORT_RANGE_MIN		10

void frandomgen_sort(const char*);
void frandomgen_main(int op)
{
	switch(op)
	{
		case 0: frandomgen_sort("sorting_input_#.txt");
		break;
		default:break;
	}
}

void frandomgen_sort(const char* filepath)
{
	FILE *fpout=fopen(filepath,"w");
	if(fpout==NULL)
	{
		printf("File couldn't be written!\n");
		fclose(fpout);
		return;
	}
	int c,t,n,num,max;
	time_t tmr;
	srand((unsigned) time(&tmr));
	t=rand()%SORT_TEST_LIMIT+SORT_TEST_MIN;
	fprintf(fpout,"%d\n",t);
	while(t--)
	{
		n=rand()%SORT_SIZE_LIMIT+1;
		max=rand()%SORT_RANGE_LIMIT+SORT_RANGE_MIN;
		fprintf(fpout,"%d\n",n);
		for(c = 1; c <= n; c++)
		{
			num = rand()%(2*max)-max;
			fprintf(fpout,"%d ",num);
		}
		fprintf(fpout,"\n\n");
	}
	fclose(fpout);
	fileread_sort(filepath);
}

