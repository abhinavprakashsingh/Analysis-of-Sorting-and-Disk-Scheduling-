#include<stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#define TEST_LIMIT	9000
#define SORT_TYPES		6
#define INCOMPATIBLE_SORT_TYPES	3
typedef void (*sortf_t)(int*,int);
extern int dominatelist[];
extern double timelist[];
extern int curr_no_of_test;

void put_subheads(FILE *fpout, char* subhead)
{
	int i;
	for(i=0; i<150; i++)
		fprintf(fpout,"-");
	fprintf(fpout,"\n\t\t%s\n",subhead);	
	for(i=0; i<150; i++)
		fprintf(fpout,"-");
	fprintf(fpout,"\n\n");
}

int cmpf_int(const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}

void analysis_fprinter(FILE *fpout, double arr[], char opname[][25], const int size, int* testcases, int testctr[])
{	
int i,j;
	put_subheads(fpout,"ALGORITHM ANALYSIS DETAILS");
	//put_subheads(fpout,"TEST CASE WISE EXECUTION TIME");
	//for(i=0; i<size; i++)		
	//{
		//fprintf(fpout,"%s:\t%fms\n",opname[i],testctr[i]);
		//fprintf(fpout,"\n");
	//}
	put_subheads(fpout,"OVERALL EXECUTION TIME");
	for(i=0; i<size; i++)
		fprintf(fpout,"%s:\t%fms\n",opname[i],arr[i]);
	fprintf(fpout,"\n");

	put_subheads(fpout,"ALGORITHM-WISE BEST-PERFORMANCE TEST CASES");
	fprintf(fpout,"Total Test-cases: %d\n\n",curr_no_of_test);
	for(i=0; i<size; i++)
	{
		fprintf(fpout,"%s: Performs best in following %d test-cases-\n",opname[i],testctr[i]);
		for(j=0; j<testctr[i]; j++)
			fprintf(fpout,"%d ",*((int*)testcases+i*TEST_LIMIT+j));
		fprintf(fpout,"\n\n");
	}
	fprintf(fpout,"\n\n");
}

void timer_sortf(sortf_t slist,int *arr,const int size,double *timelist,const int i, double *mintime, int *minpos)
{
	double timeinms;
	clock_t timer=clock();
	(*slist)(arr,size);
	timer=clock()-timer;
	timeinms=(double)timer*1000/CLOCKS_PER_SEC;
	timelist[i]+=timeinms;
	if(timeinms<(*mintime))
	{
		*mintime=timeinms;
		*minpos=i;
	}
}

void fileread_sort(char *filepath)
{
	char sortname[SORT_TYPES][25]={"Selection Sort","Bubble Sort","Insertion Sort","Merge Sort","Quick Sort","Randomized Quick Sort"};
	int testcases[SORT_TYPES][TEST_LIMIT],testctr[6];
	sortf_t sortflist[3]={&selectionSort,&bubbleSort,&insertionSort};
	int i,j,k,n,t,ctr,asize,lsize,size,*values[SORT_TYPES];
	for(i=0; i<SORT_TYPES; i++)
	{	
		timelist[i]=0.000;
		dominatelist[i]=0;
		testctr[i]=0;
	}
	FILE *fpin;
	fpin=fopen(filepath,"r");
	FILE *fpout=fopen("sorting_output_#.txt","w");
	if(fpout==NULL)
	{
		printf("File couldn't be written!\n");
		fclose(fpin);
		fclose(fpout);
		return;
	}
	if(fpin!=NULL)
	{
		if(!feof(fpin))
			fscanf(fpin,"%d",&t);

		curr_no_of_test=t;
		for(k=0; k<t; k++)
		{
			fscanf(fpin,"%d",&n);
			for(i=0; i<SORT_TYPES; i++)
			{	
				values[i]=calloc(n,sizeof(int));
				if(values[i]==NULL)
				{
					fprintf(fpout,"Couldn't allocate enough memory!\n");
					fclose(fpin);
					fclose(fpout);
					return;
				}
			}
			for(i=0; !feof(fpin), i<n; i++)
			{
				fscanf(fpin,"%d",&values[0][i]);
				for(j=1; j<SORT_TYPES; j++)
					values[j][i]=values[0][i];
			}

			double mintime=999.999;
			int minpos=0;
			for(i=0; i<SORT_TYPES-INCOMPATIBLE_SORT_TYPES; i++)
				timer_sortf(sortflist[i],values[i],n,timelist,i,&mintime,&minpos);

			clock_t timer=clock();
			double timeinms;
			mergeSort(values[3],0,n-1);
			timer=clock()-timer;
			timeinms=(double)timer*1000/CLOCKS_PER_SEC;		
			timelist[3]+=timeinms;
			if(timeinms<mintime)
			{
				mintime=timeinms;
				minpos=3;
			}
			timer=clock();
			quickSort(values[4],0,n-1);
			timer=clock()-timer;
			timeinms=(double)timer*1000/CLOCKS_PER_SEC;		
			timelist[4]+=timeinms;
			if(timeinms<mintime)
			{
				mintime=timeinms;
				minpos=4;
			}
			timer=clock();
			qsort(values[5], n, sizeof(int), cmpf_int);
			timer=clock()-timer;
			timeinms=(double)timer*1000/CLOCKS_PER_SEC;		
			timelist[5]+=timeinms;
			if(timeinms<mintime)
			{
				mintime=timeinms;
				minpos=5;
			}
			
			for(i=0; i<SORT_TYPES; i++)
				free(values[i]);

			dominatelist[minpos]++;
			testcases[minpos][testctr[minpos]++]=k+1;
		}
		//asize=sizeof(timelist)/sizeof(timelist[0]);
		size=sizeof(sortname)/25;
		//size=(asize<lsize)?asize:lsize;
		analysis_fprinter(fpout,timelist,sortname,size,testcases,testctr);
		fclose(fpin);
		fclose(fpout);
		chartor(0);
		return;
	}
	printf(fpout,"File couldn't be read\n");
	fclose(fpin);
	fclose(fpout);
}


