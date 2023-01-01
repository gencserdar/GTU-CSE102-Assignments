#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ALPH 26
#define MAX 15
#define WORDLENGTH 10
#define WORDCOUNT 7

void setBoard(char board[][MAX], char words[][WORDLENGTH])
{
    FILE*file = fopen("wordlist.txt", "r");
    int d;
    char allwords[50][WORDLENGTH];
    char rolleddices[WORDCOUNT];

    /*MOVE ALL WORDS FROM FILE INTO A STRING*/
    for (int k=0; k<50; k++) fscanf(file,"%s",allwords[k]);
    fclose(file);

    /*ROLL DICE TO SELECT WORDS*/ 
    for (int k=0; k<WORDCOUNT; k++)
    {
        do
        {
            d=(rand() % 50);
        }while(d==rolleddices[0] || d==rolleddices[1] || d==rolleddices[2] || d==rolleddices[3] || d==rolleddices[4] || d==rolleddices[5] || d==rolleddices[6]); //to prevent having the same word twice
        rolleddices[k]=d;
    }

    /*MOVE SELECTED WORDS INTO ANOTHER STRING*/
    for (int k=0; k<WORDCOUNT; k++)
    {
        int temp= rolleddices[k];
        strcpy(words[k],allwords[temp]);
    }

    typedef enum directions {to_south, to_southwest,
                    to_west, to_northwest,
                    to_north, to_northeast,
                    to_east, to_southeast
                    }direction;
    direction way;

    /*CLEAR THE BOARD*/
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            board[i][j] = '\0';
        }
    }
    
    
    /*SET THE WORDS RANDOMLY*/
    int px,py, control, counter=0;
    while (counter<WORDCOUNT) //for each word
    {
        way= (rand() % 7); //choose the way randomly
        control=0; //i defined control to quit while loops
        int length=strlen(words[counter]);
        switch (way)
        {
            case to_south:
                while (control!=1)
                {
                    do
                    {
                        px= (rand() % MAX);
                        py= (rand() % MAX);
                    }while (length+py>MAX); //check if the word placed is inside the borders of the board
                    int controlcounter=0;
                    for ( int k=0; k<length; k++)
                    {
                        if (board[py+k][px]=='\0') controlcounter++; //for each letter, check if the letters of the word does not intersect with letters of another word
                    }
                    if (controlcounter==length) //controlcounter equals to length if word does not intersect with another word
                    {
                        for ( int k=0; k<length; k++)
                        {
                            board[py+k][px]=words[counter][k];
                        }
                        counter++; //a word is successfully placed, so counter++
                        control=1; //a word is successfully placed and does not intersect with another word so quit the while loop
                    }
                }
                break;

            case to_southwest:
                while (control!=1)
                {
                    do
                    {
                        px= (rand() % MAX);
                        py= (rand() % MAX);
                    }while (length+py>MAX || px-length<-1 );
                    int controlcounter=0;
                    for ( int k=0; k<length; k++)
                    {
                        if (board[py+k][px-k]=='\0') controlcounter++;
                    }
                    if (controlcounter==length)
                    {
                        for ( int k=0; k<length; k++)
                        {
                            board[py+k][px-k]=words[counter][k];
                        }
                        counter++;
                        control=1;
                    }
                }
                break;

            case to_west:
                while (control!=1)
                {
                    do
                    {
                        px= (rand() % MAX);
                        py= (rand() % MAX);
                    }while (px-length<-1);
                    int controlcounter=0;
                    for ( int k=0; k<length; k++)
                    {
                        if (board[py][px-k]=='\0') controlcounter++;
                    }
                    if (controlcounter==length)
                    {
                        for ( int k=0; k<length; k++)
                        {
                            board[py][px-k]=words[counter][k];
                        }
                        counter++;
                        control=1;
                    }
                }
                break;

            case to_northwest:
                while (control!=1) 
                {
                    do
                    {
                        px= (rand() % MAX);
                        py= (rand() % MAX);
                    }while (py-length<-1 || px-length<-1 );
                    int controlcounter=0;
                    for ( int k=0; k<length; k++)
                    {
                        if (board[py-k][px-k]=='\0') controlcounter++;
                    }
                    if (controlcounter==length)
                    {
                        for ( int k=0; k<length; k++)
                        {
                            board[py-k][px-k]=words[counter][k];
                        }
                        counter++;
                        control=1;
                    }
                }
                break;

            case to_north:
                while (control!=1)
                {
                    do
                    {
                        px= (rand() % MAX);
                        py= (rand() % MAX);
                    }while (py-length<-1);
                    int controlcounter=0;
                    for ( int k=0; k<length; k++)
                    {
                        if (board[py-k][px]=='\0') controlcounter++;
                    }
                    if (controlcounter==length)
                    {
                        for ( int k=0; k<length; k++)
                        {
                            board[py-k][px]=words[counter][k];
                        }
                        counter++;
                        control=1;
                    }
                }
                break;

            case to_northeast:
                while (control!=1)
                {
                    do
                    {
                        px= (rand() % MAX);
                        py= (rand() % MAX);
                    }while (py-length<-1 || length+px >MAX );
                    int controlcounter=0;
                    for ( int k=0; k<length; k++)
                    {
                        if (board[py-k][px+k]=='\0')  controlcounter++;
                    }
                    if (controlcounter==length)
                    {
                        for ( int k=0; k<length; k++)
                        {
                            board[py-k][px+k]=words[counter][k];
                        }
                        counter++;
                        control=1;
                    }
                }
                break;

            case to_east:
                while (control!=1)
                {
                    do
                    {
                        px= (rand() % MAX);
                        py= (rand() % MAX);
                    }while (length+px>MAX);
                    int controlcounter=0;
                    for ( int k=0; k<length; k++)
                    {
                        if (board[py][px+k]=='\0') controlcounter++;
                    }
                    if (controlcounter==length)
                    {   
                        for ( int k=0; k<length; k++)
                        {
                            board[py][px+k]=words[counter][k];
                        }
                        counter++;
                        control=1;
                    }
                }
                break;

            case to_southeast:
                while (control!=1)
                {
                    do
                    {
                        px= (rand() % MAX);
                        py= (rand() % MAX);
                    }while (length+py>MAX || length+px>MAX );
                    int controlcounter=0;
                    for ( int k=0; k<length; k++)
                    {
                        if (board[py+k][px+k]=='\0') controlcounter++;
                    }
                    if (controlcounter==length)
                    {
                        for ( int k=0; k<length; k++)
                        {
                            board[py+k][px+k]=words[counter][k];
                        }
                        counter++;
                        control=1;
                    }
                }
                break;
            default: printf("yeter amk");
        }
    }
} 

void printBoard(char board[][MAX])
{
    char alphabet[ALPH] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };

    /*in this part i colored the random letters but not the words so you can easily find words and track my code, and colored 'X's for a better look*/
    for (int i = 0; i < MAX; i++)   
    {
        for (int j = 0; j < MAX; j++)
        {   
            //if does not intersect with a word, fill with random letters
            if (board[i][j]=='\0')
            {
                board[i][j] = alphabet[rand() % ALPH];
                printf("\033[0;33m%c \033[0m",board[i][j]);
            } 
            //if it is a 'X' print it with color 
            else if (board[i][j]=='X')
            {
                printf("\033[0;33m%c \033[0m",board[i][j]);
            }
            //print the words
            else printf("%c ",board[i][j]);
        }
        printf("\n");
    }    
}

int playGame(int mistake, char board[][MAX], int points,char words[][WORDLENGTH])
{
    int x,y,control=0;
    char str[WORDLENGTH], compare[WORDLENGTH];
    
    //win condition
    if (points==14) return -1;

    printf("Enter the word and then the coordinates.(in order=>  word,x,y)\n");
    
    do
    {
        scanf("%s", str);
        getchar();
        if (strlen(str)>7) printf("\n The word you entered is too long, enter again.\n\n");
    }while(strlen(str)>7);
    //terminate the program by entering ':q'
    if (strcmp(str,":q")==0) return -2;
    
    scanf("%d %d",&x, &y);
    /*CHECK IF THE GIVEN WORD IS FOUND*/
    /*EACH FOR LOOP CHECKS FOR EACH DIRECTION SO THERE ARE 8 FOR LOOPS SEARCHING THE WORD*/
    for (int k=0; k<strlen(str); k++)
    {
        compare[k]=board[y+k][x];
        if (k==strlen(str)-1) //when the compare word is set
        {
            compare[k+1]='\0';
            if (strcmp(compare,str)==0)//if input matches the compare word
            {
            	 for (int t=0;t<WORDCOUNT;t++)
            	 {
            	     if(strcmp(str,words[t])==0) //if input matches with one of the randomly chosen words from the file
            	     {
                	  for (int k=0; k<strlen(str); k++)
                	  {
                    	      board[y+k][x]='X'; //place X instead of letters of the found word
                	  }
                         control=1;//control equals to 1 if the word is found
                     }
            	 }
            }
         }
    }

    for (int k=0; k<strlen(str); k++)
    {
        compare[k]=board[y-k][x];
        if (k==strlen(str)-1)
        {
            compare[k+1]='\0';
            if (strcmp(compare,str)==0)
            {
                for (int t=0;t<WORDCOUNT;t++)
            	 {
            	     if(strcmp(str,words[t])==0)
            	     {
                         for (int k=0; k<strlen(str); k++)
                	  {
                    	      board[y-k][x]='X';
                	  }
                	  control=1;
                     }
                 }
            }
        }
    }

    for (int k=0; k<strlen(str); k++)
    {
        compare[k]=board[y][x+k];
        if (k==strlen(str)-1)
        {
            compare[k+1]='\0';
            if (strcmp(compare,str)==0)
            {
                for (int t=0;t<WORDCOUNT;t++)
            	 {
            	     if(strcmp(str,words[t])==0)
            	     {
                         for (int k=0; k<strlen(str); k++)
                	  {
                    	      board[y][x+k]='X';
                	  }
                	  control=1;
                     }
                 }
            }
        }
    }

    for (int k=0; k<strlen(str); k++)
    {
        compare[k]=board[y][x-k];
        if (k==strlen(str)-1)
        {
            compare[k+1]='\0';
            if (strcmp(compare,str)==0)
            {
                for (int t=0;t<WORDCOUNT;t++)
            	 {
            	     if(strcmp(str,words[t])==0)
            	     {
                         for (int k=0; k<strlen(str); k++)
                	  {
                    	      board[y][x-k]='X';
                	  }
                	  control=1;
                     }
                 }
            }
        }
    }
    for (int k=0; k<strlen(str); k++)
    {
        compare[k]=board[y+k][x+k];
        if (k==strlen(str)-1)
        {
            compare[k+1]='\0';
            if (strcmp(compare,str)==0)
            {
                for (int t=0;t<WORDCOUNT;t++)
            	 {
            	     if(strcmp(str,words[t])==0)
            	     {
                         for (int k=0; k<strlen(str); k++)
                	  {
                    	      board[y+k][x+k]='X';
                	  }
                	  control=1;
                     }
                 }
            }
        }
    }
    for (int k=0; k<strlen(str); k++)
    {
        compare[k]=board[y-k][x-k];
        if (k==strlen(str)-1)
        {
            compare[k+1]='\0';
            if (strcmp(compare,str)==0)
            {
                for (int t=0;t<WORDCOUNT;t++)
            	 {
            	     if(strcmp(str,words[t])==0)
            	     {
                         for (int k=0; k<strlen(str); k++)
                	  {
                    	      board[y-k][x-k]='X';
                	  }
                	  control=1;
                     }
                 }
            }
        }
    }
    for (int k=0; k<strlen(str); k++)
    {
        compare[k]=board[y+k][x-k];
        if (k==strlen(str)-1)
        {
            compare[k+1]='\0';
            if (strcmp(compare,str)==0)
            {
                for (int t=0;t<WORDCOUNT;t++)
            	 {
            	     if(strcmp(str,words[t])==0)
            	     {
                         for (int k=0; k<strlen(str); k++)
                	  {
                    	      board[y+k][x-k]='X';
                	  }
                	  control=1;
                     }
                 }
            }
        }
    }
    for (int k=0; k<strlen(str); k++)
    {
        compare[k]=board[y-k][x+k];
        if (k==strlen(str)-1)
        {
            compare[k+1]='\0';
            if (strcmp(compare,str)==0)
            {
                for (int t=0;t<WORDCOUNT;t++)
            	 {
            	     if(strcmp(str,words[t])==0)
            	     {
                         for (int k=0; k<strlen(str); k++)
                	  {
                    	      board[y-k][x+k]='X';
                	  }
                	  control=1;
                     }
                 }
            }
        }
    }
    if (control==1) return mistake;
    else if (control==0)
    {
        mistake++;
        return mistake;
    }
    else return -2;
}
int main() 
{
    int mistake=0,test,points=0;
    char board[MAX][MAX];
    char words[WORDCOUNT][WORDLENGTH];
    srand(time(NULL));
    setBoard(board,words);

    while(mistake<3)
    {
        printBoard(board);
        test=mistake;
        mistake=playGame(mistake,board,points,words);
        if (test==mistake) //test equals to mistake if the answer is correct
        {
            points=points+2;
            printf("\nFound! You got 2 points. Your total points: %d\n",points);
        }
        else if (mistake>test && mistake !=3) //if mistake is 3 this means game is over and player lost. 
        {
            printf("\nWrong choice! You have only %d lefts.\n",3-mistake);
        }
        else if (mistake==-1) //playGame returns -1 if player won 
        {
            printf("\nGame Over, you won!\nYour total points: %d\n",points);
            return 0;
        }
        else if (mistake==-2) //playGame returns -2 if player quit game by entering :q
        {
            printf("\nQuitting the game...\nYour total points: %d\n",points);
            return 0;
        }
    }
    printf("\nGame Over, you lost!\nYour total points: %d\n",points); //if player didnt win or terminate the program and mistake reached 3, this means player lost the game.
    return 0;
}
