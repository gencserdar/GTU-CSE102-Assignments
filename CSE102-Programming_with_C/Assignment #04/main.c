#include <stdio.h>


int how_many_digit(int y);
//checks how many digit of number ,signs are also counted  (for example -50= 3 digits)

void print_graph(int a,int b,int c);
//print graph into a file without colors and numbers

void sketch_graph(int a,int b,int c);
//print graph to terminal with colors and numbers

int main()
{
    int op;
    do
    {
        do
        {
            printf("Select an operation...\n1 -> Enter the coefficients.\n2 -> Draw the graph.\n3 -> Print the graph into a .txt file\n4 -> Exit.\n\nChoice: ");
            scanf("%d",&op);
            if(op!=1 && op!=2 && op!=3 && op!=4 ) printf("\n---------------------\nPlease enter a valid operation.\n---------------------\n\n");
        }while (op!=1 && op!=2 && op!=3 && op!=4 ); //validation check

        if (op==1)
        {
            int a,b,c;
            printf("\nPlease enter the coefficient for the following equation: x= a*(y*y) + b*y + c\n\n");
            printf("a: ");
            scanf("%d",&a);
            printf("b: ");
            scanf("%d",&b);
            printf("c: ");
            scanf("%d",&c);
	    //take inputs
	    
            FILE*file=fopen("coefficients.txt","w+");
            if(file != NULL) printf("\ncoefficients.txt file has been created.\n\n"); 
            else
            {
                printf("\n---------------------\nAn error occured while creating the file!\n---------------------\n");
                return -1;
            }
            //open file to write coefficionts
            
            fprintf(file,"%d\n%d\n%d\n",a,b,c);
            fclose(file);
        }
        
        if (op==2)
        {
            int a,b,c;
            FILE*file=fopen("coefficients.txt","r");
            if(file == NULL)
            {
                printf("\n---------------------\ncoefficients.txt does not exist!\n---------------------\n");
                return -2;
            }
            //open coefficients file to read
            
            fscanf(file,"%d %d %d",&a,&b,&c);
	    printf("\nCoefficients has been read from the coefficient file.\n");
            sketch_graph(a,b,c);
	    fclose(file);
        }
        
        if (op==3)
        {
           int a,b,c;
           FILE*file=fopen("coefficients.txt","r");
           if(file == NULL)
           {
               printf("\n---------------------\ncoefficients.txt does not exist!\n---------------------\n");
               return -3;
           }
           //open coefficients file to read
           
           fscanf(file,"%d %d %d",&a,&b,&c);
           printf("\nCoefficients has been read from the coefficient file.\n");
           print_graph(a,b,c);
           fclose(file);
        }
    }while (op!=4); 
    //exit status
    
    return 0;
}

void sketch_graph(int a, int b, int c)
{	
    printf("Printing the graph of x= %d*(y*y) + %d*y + %d\n\n",a,b,c);
    int x, y; 
    // x represents columns(-50,50), y represents lines(15,-15)
    
    for(x=-50;x<=0;x++) printf(" ");
    printf(" ^\n");
    for(y=15;y>=-15;y--)
    {
        if (y==0)
        // Printing the horizontal axis
        {
            printf(" <");
            for(x=-50;x<0;x++) 
            {
                if (x==a*y*y+b*y+c)
                {
                    printf("\033[0;34m");
                    printf("#");
                    printf("\033[0m");
                }
                else printf("-");
            }
            //for x<0
            
            if (a*y*y+b*y+c==0) 
            {
                printf("\033[0;34m");
                printf("#");
                printf("\033[0m");
            }
            else printf("|");
            //for x=0
            
            for(x=1;x<51;x++) 
            {
                if (x==a*y*y+b*y+c)
                {
                    printf("\033[0;34m");
                    printf("#");
                    printf("\033[0m");
                }
                else printf("-");
            }
            printf(">\n");
            //for x>0
        }
        else
        //printing every other line except the line contains horizontal axis
        {
            if (y!=-1)
            //in y=-1, the number values of horizontal axis will be printed so it will require a seperate code than other lines
            {
                for(x=-52;x<0;x++)
                {
                    if (x==a*y*y+b*y+c) 
                    {
                        printf("\033[0;34m");
                        printf("#");
                        printf("\033[0m");
                    }
                    else printf(" ");
                }
                
                if (y%5==0 && a*y*y+b*y+c!=-1 && a*y*y+b*y+c!=-2 && a*y*y+b*y+c!=-3) // checks if is there a number intersecting with "#"
                {
                    for (int k=0; k<how_many_digit(y);k++) printf("\b");
                    //checks how many digit does the number to be printed have and deletes that much space to place the number there
                    
                    printf("\033[0;33m");
                    printf("%d",y);
                    printf("\033[0m");
                }
                // if there is no "#" intersecting, it will print the vertical axis number values which are dividible by 5
                // for x<0
                
                if (a*y*y+b*y+c==0) 
                {
                    printf("\033[0;34m");
                    printf("#");
                    printf("\033[0m");
                }
                else printf("|");
                // if there needs to be a "#" on the vertical, prints "#" instead of "|" 
                // for x=0
                
                for(x=1;x<50;x++)
                {
                    if (x==a*y*y+b*y+c) 
                    {
                        printf("\033[0;34m");
                        printf("#");
                        printf("\033[0m");
                    }
                    else printf(" ");
                }
                printf("\n");
                // for x>0
            }    
            else
            //for y=-1
            {
                for(x=-52;x<-1;x++)
                {
                    if (x==a*y*y+b*y+c)
                    {
                        printf("\033[0;34m");
                        printf("#");
                        printf("\033[0m");
                    }
                    else printf(" ");
                    
                    if (x%10==0 && x-3!=a*y*y+b*y+c && x-2!=a*y*y+b*y+c && x-1!=a*y*y+b*y+c && x!=a*y*y+b*y+c) // checks if is there a number intersecting with "#"
                    {
                        for (int k=0; k<how_many_digit(x);k++) printf("\b");
                        //checks how many digit does the number to be printed have and deletes that much space to place the number there
                        
                        printf("\033[0;33m");
                        printf("%d",x);
                        printf("\033[0m");
                    }
                }
                // for x<-1
                
                if (a*y*y+b*y+c==-1) 
                {
                    printf("\033[0;34m");
                    printf("#");
                    printf("\033[0m");
                }
                else
                {
                    printf("\033[0;33m");
                    printf("0");
                    printf("\033[0m");
                }
                //for x=-1, "0" will be printed here if there is no "#" intersecting
                
                if (a*y*y+b*y+c==0) 
                {
                    printf("\033[0;34m");
                    printf("#");
                    printf("\033[0m");
                }
                else printf("|");
                // for x=0, a "|" will be printed here to continue printing the vertical axis if there is no "#" intersecting
                
                for(x=1;x<51;x++)
                {
                    if (x==a*y*y+b*y+c) 
                    {
                        printf("\033[0;34m");
                        printf("#");
                        printf("\033[0m");
                    }
                    else printf(" ");
                    if (x%10==0 && x-3!=a*y*y+b*y+c && x-2!=a*y*y+b*y+c && x-1!=a*y*y+b*y+c && x!=a*y*y+b*y+c) // checks if is there a number intersecting with "#"
                    {
                        for (int k=0; k<how_many_digit(x);k++) printf("\b");
                        //checks how many digit does the number to be printed have and deletes that much space to place the number there
                        
                        printf("\033[0;33m");
                        printf("%d",x);
                        printf("\033[0m");
                    }
                }
                printf("\n");
                // for x>0
            }
        }
    }
    for(x=-50;x<=0;x++) printf(" ");
    printf(" v\n");
}

void print_graph(int a, int b, int c)
// this is the same code as sketch_graph, but the number and color codes are excluded; and instead of terminal, printed into a file named "graph.txt".
{
    FILE*file=fopen("graph.txt","w+");
    int x, y;
    for(x=-50;x<=0;x++) fprintf(file," ");
    fprintf(file," ^\n");
    for(y=15;y>=-15;y--)
    {
        if (y==0)
        {
            fprintf(file," <");
            for(x=-50;x<0;x++) 
            {
                if (x==a*y*y+b*y+c) fprintf(file,"#");
                else fprintf(file,"-");
            }
            if (a*y*y+b*y+c==0) fprintf(file,"#");
            else fprintf(file,"|");
            for(x=1;x<51;x++) 
            {
                if (x==a*y*y+b*y+c) fprintf(file,"#");
                else fprintf(file,"-");
            }
            fprintf(file,">\n");
        }

        else
        {

            for(x=-52;x<0;x++)
            {
                if (x==a*y*y+b*y+c) fprintf(file,"#");
                else fprintf(file," ");
            }
            if (a*y*y+b*y+c==0) fprintf(file,"#");
            else fprintf(file,"|");
            for(x=1;x<50;x++)
            {
                if (x==a*y*y+b*y+c) fprintf(file,"#");
                else fprintf(file," ");
            }
            fprintf(file,"\n");
        }    
            
    }
    for(x=-50;x<=0;x++) fprintf(file," ");
    fprintf(file," v\n");
    fclose(file);
    printf("The graph of x= %d*(y*y) + %d*y + %d has been written to graph.txt file.\n\n",a,b,c);
}

int how_many_digit(int num)
{
    int count=0;
    if (num<0)
    {
        num=-1*num;
        count++;
    }
    //if num is negative due to negative sign, count will incremented by one
    
    do
    {  
        count++;
        // increment digit count 
 
        num /= 10;
        // remove last digit of "num"
    } while(num != 0); // run loop till num is greater than 0 
    
    return count;
}
