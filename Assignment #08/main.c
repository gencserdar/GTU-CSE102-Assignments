#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#define MAX 32000 //this was the max value without errors when i tested with malloc

void main()
{
	int seqlen, xs, loop[MAX], looplen=-1, h[9]; 
	printf("Please enter the sequence length: ");
	scanf("%d",&seqlen);
	printf("Please enter the first element: ");
	scanf("%d",&xs);
	check_loop_iterative(generate_sequence,xs,seqlen,loop, &looplen); //check and print loop, loop length, sequence, loop's first occurance
	
	if(loop[0]!='\0') //if a loop is detected print it
	{
		printf("Loop: {");
		for (int k =0; k<looplen; k++)
		{
			if (k==looplen-1)
				printf("%d}\n",loop[k]);
			else 
				printf("%d, ",loop[k]);
		}
	}
	else printf("\nNo loop found.\n"); //if no loop, print this
	
	hist_of_firstdigits(generate_sequence,xs,seqlen,h,1); //histogram of the first digits of the sequence
	
	printf("\nHistogram of the sequence: {");
	for (int k=0; k<9; k++)//print the histogram
	{
		if (k==8) printf("%d}\n",h[k]);
		else printf("%d, ",h[k]);
	}
}

int has_loop(int *arr, int n, int looplen, int *ls, int *le) //check if there is a loop
{
	int counter=0;
	for (int k =0; k<looplen; k++)
	{
		if (arr[n-1-k] == arr[n-looplen-k-1])
			counter++;	
	}
	if (counter==looplen) //if there is a loop with this loop length
	{
		*ls = n-looplen-looplen; //first occurance, first digit
		*le = n-looplen-1;	//first occurance, last digit
		return 1;
	}
	else return 0;
}

void generate_sequence(int xs, int currentlen, int seqlen, int *seq)
{

	if (currentlen>seqlen)
		return; // exit from function 

	seq[currentlen-1]=xs; //set the sequence

	if (xs%2==0)
		generate_sequence(xs/2,currentlen+1,seqlen,seq); // n/2 if even  
	else
		generate_sequence(xs*3+1,currentlen+1,seqlen,seq); // n*3 + 1 if odd
}

void check_loop_iterative(void (*f)(int, int, int, int*), int xs, int seqlen, int *loop,int *looplen)
{
	int ls, le;
	if (*looplen<2 && *looplen !=-1) // loop length cant be smaller than 2
	{
		return;
	}
	int seq[MAX];
	(*f)(xs,1,seqlen,seq); // call the generate_sequence function
	if (*looplen==-1) // to execute only once
	{
		printf("\nSequence: {");
		for (int k=0; k<seqlen; k++) // print the sequence
		{
			if (k==seqlen-1)
				printf("%d", seq[k]);
			else
				printf("%d, ",seq[k]);
		}
		printf("}\n");
		
		if (seqlen%2==0)
			*looplen=seqlen/2; //max loop length can be n/2
		else 
			*looplen= (seqlen-1)/2;
	}
	if (seqlen<2 || *looplen ==1)
	{
		return; //min loop length is 2, sequence with 1 number cant have loop
	}
	printf("\nChecking if there is a loop of length %d...",*looplen);
	
	if(has_loop(seq, seqlen, *looplen, &ls, &le)==1) //check if there is a loop
	{
		printf("\n\n\nLoop detected with a length of %d.\n", *looplen); 
		printf("The indexes of the loop's first occurance: %d (first digit), %d (last digit)\n",ls,le); //print indexes
		for (int k =0; k<*looplen; k++)
			loop[k]=seq[seqlen-*looplen+k]; //set the loop array
		return;
	}
	else 
		*looplen= *looplen-1; //if there is no loop with this loop length then subtract 1 and try again
	check_loop_iterative(generate_sequence,xs,seqlen,loop,looplen); 
}

void hist_of_firstdigits(void (*f)(int, int, int, int*), int xs, int seqlen, int *h, int digit)
{
	if (digit==10) return; //exit from function 
	int seq[MAX],counter=0;
	(*f)(xs,1,seqlen,seq); //call the generate_sequence function
	for (int k=0; k<seqlen; k++)
	{
		while (seq[k]>=10) seq[k]= seq[k]/10; //find the first digit of a number
		if (seq[k]==digit)
			counter++; //if the found digit matches the specific digit counter ++
	}
	h[digit-1]=counter; // set the amount of the first digits for each digit
	hist_of_firstdigits(generate_sequence,xs,seqlen,h,digit+1);
}
