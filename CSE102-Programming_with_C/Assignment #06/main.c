#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROWS 15
#define COLUMNS 30

char map[ROWS][COLUMNS];
int dice(); //dice roll function
int startGame(int, int); //function to decide who starts first
int printMap(int, int, int, int); //function to print the map
int update(int, int, int, int);

void main()
{
    char map[ROWS][COLUMNS];
    int p1x=1, p1y=1 ,p2x=3, p2y=3, start; //1,1 and 3,3 are the start coordinates for player 1 and player 2
    srand(time(NULL));

    printf("\n\n\nTo start to game, players should dice and decide who is going to start first according to it...\n");
    do
    {
        int d1= dice();
        int d2= dice();
        printf("\033[1;33mPLAYER 1... press ENTER to dice\033[0m");
        getchar();
        printf("\033[1;33mDICE: %d\033[0m\n",d1);
        printf("\033[1;34mPLAYER 2... press ENTER to dice\033[0m");
        getchar();
        printf("\033[1;34mDICE: %d\033[0m\n",d2);
        start = startGame(d1,d2);
    }while (start==0); //if dices are equal, startGame returns 0 

    switch (start) 
    {
        case 1: //startGame returns 1 if player 1 is the first player
            while (1)
            {
                /*roll dice*/
                int res;
                int d1=dice();
                int d2=dice();
                printf("\033[1;33mPLAYER 1... press ENTER to dice\033[0m");
                getchar();
                printf("\033[1;33mDICE: %d\033[0m\n",d1);
                printf("\033[1;34mPLAYER 2... press ENTER to dice\033[0m");
                getchar();
                printf("\033[1;34mDICE: %d\033[0m\n",d2);

                /*PLAYER 1*/
                /*UPPER SECTION OF THE MAP*/
                if (p1x<28 && p1y==1)
                {
                    /*PENALTY CHECK*/
                    if ((p1x+d1)==14)
                    {
                        p1x=p1x+d1-2; 
                        printf("\033[1;33mPenalty for player 1...\n\033[0m");
                    }

                    /*MOVE PLAYER UNTIL IT REACHES THE WALL*/
                    else if ((p1x+d1)<=28) p1x+=d1;

                    /*MOVE PLAYER IF IT IS TURNING*/
                    else 
                    {
                        int k=p1x+d1;
                        p1x=28;
                        p1y+=k-28;
                    }
                }
                
                /*RIGHT SECTION OFTHE MAP*/
                else if (p1x==28 && p1y<13)
                {
                    /*PENALTY CHECK*/
                    if ((p1y+d1)==7)
                    {
                        p1y-p1y+d1-2;
                        printf("\033[1;33mPenalty for player 1...\n\033[0m");
                    }

                    /*MOVE PLAYER UNTIL IT REACHES THE WALL*/
                    else if ((p1y+d1)<=13) p1y+=d1;

                    /*MOVE PLAYER IF IT IS TURNING*/
                    else
                    {
                        int k=p1y+d1;
                        p1y=13;
                        p1x-=k-13;
                    }
                }

                /*BOTTOM SECTION OF THE MAP*/
                else if (p1x>1 && p1y==13)
                {
                    /*PENALTY CHECK*/
                    if ((p1x-d1)==14)
                    {
                        p1x=p1x-d1+2;
                        printf("\033[1;33mPenalty for player 1...\n\033[0m");
                    }
                    
                    /*MOVE PLAYER UNTIL IT REACHES THE WALL*/
                    else if ((p1x-d1)>=1) p1x-=d1;

                    /*MOVE PLAYER IF IT IS TURNING*/
                    else
                    {
                        int k= p1x-d1;
                        p1x=1;
                        p1y=p1y+k-1;
                    }
                }

                /*LEFT SECTION OF THE MAP*/
                else if (p1x==1 && p1y>2)
                {
                    /*MOVE PLAYER UNTIL IT REACHES THE FINISH*/
                    if ((p1y-d1)>=2) p1y-=d1;

                    /*PLACE THE PLAYER TO FINISH LINE IF IT REACHES OR PASSES THE FINISH*/
                    else p1y=2;
                }


                /*PLAYER 2*/
                /*UPPER SECTION OF THE MAP*/
                if (p2x<26 && p2y==3)
                {
                    /*PENALTY CHECK*/
                    if ((p2x+d2)==10 || (p2x+d2==18))
                    {
                        p2x=p2x+d2-2; 
                        printf("\033[1;34mPenalty for player 2...\n\033[0m");
                    }

                    /*MOVE PLAYER UNTIL IT REACHES THE WALL*/
                    else if ((p2x+d2)<=26) p2x+=d2;

                    /*MOVE PLAYER IF IT IS TURNING*/
                    else 
                    {
                        int k=p2x+d2;
                        p2x=26;
                        p2y+=k-26;
                        if (p2y==5) p2y-=2; //check if player places on penalty point after turning 
                    }
                }

                /*RIGHT SECTION OFTHE MAP*/
                else if (p2x==26 && p2y<11)
                {
                    /*PENALTY CHECK*/
                    if ((p2y+d2)==5 || (p2y+d2)==10)
                    {
                        p2y=p2y+d2-2;
                        printf("\033[1;34mPenalty for player 2...\n\033[0m");
                    }

                    /*MOVE PLAYER UNTIL IT REACHES THE WALL*/
                    else if ((p2y+d2)<=11) p2y+=d2;

                    /*MOVE PLAYER IF IT IS TURNING*/
                    else
                    {
                        int k=p2y+d2;
                        p2y=11;
                        p2x-=k-11;
                    }
                }

                /*BOTTOM SECTION OF THE MAP*/
                else if (p2x>3 && p2y==11)
                {
                    /*PENALTY CHECK*/
                    if ((p2x-d2)==10 || (p2x-d2)==18)
                    {
                        p2x=p2x-d2+2;
                        printf("\033[1;34mPenalty for player 2...\n\033[0m");
                    }

                    /*MOVE PLAYER UNTIL IT REACHES THE WALL*/
                    else if ((p2x-d2)>=3) p2x-=d2;

                    /*MOVE PLAYER IF IT IS TURNING*/
                    else
                    {
                        int k= p2x-d2;
                        p2x=3;
                        p2y=p2y+k-3;
                    }
                }

                /*LEFT SECTION OF THE MAP*/
                else if (p2x==3 && p2y>4)
                {
                    /*IF PLAYER 1 HAS ALREADY FINISHED DONT MOVE*/
                    if (p1x==1 && p1y==2);

                    /*MOVE PLAYER UNTIL IT REACHES THE FINISH*/
                    else if ((p2y-d2)>=4) p2y-=d2;

                    /*PLACE THE PLAYER TO FINISH LINE IF IT REACHES OR PASSES THE FINISH*/
                    else p2y=4;
                }


                res=update(p1x,p1y,p2x,p2y); //update returns 1 if player 1 win, returns 2 if player 2 win, returns 0 if race is not over yet
                printMap(p1x,p1y,p2x,p2y);
                if (res==1)
                {
                    printf("\033[1;33m\n\n *** PLAYER 1 WON THE GAME ***\n\n\033[0m");
                    exit(0);
                }
                if (res==2)
                {
                    printf("\033[1;34m\n\n *** PLAYER 2 WON THE GAME ***\n\n\033[0m");
                    exit(0);
                }
            }

        /*CASE 2 IS THE SAME CODE AS CASE 1 BUT PLAYER 2 STARTS FIRST*/
        case 2: //startGame returns 2 if player 2 is the first player
           while (1)
            {
                /*roll dice*/
                int res;
                int d2=dice();
                int d1=dice();
                printf("\033[1;34mPLAYER 2... press ENTER to dice\033[0m");
                getchar();
                printf("\033[1;34mDICE: %d\033[0m\n",d2);
                printf("\033[1;33mPLAYER 1... press ENTER to dice\033[0m");
                getchar();
                printf("\033[1;33mDICE: %d\033[0m\n",d1);

                /*PLAYER 2*/
                /*UPPER SECTION OF THE MAP*/
                if (p2x<26 && p2y==3)
                {
                    /*PENALTY CHECK*/
                    if ((p2x+d2)==10 || (p2x+d2==18))
                    {
                        p2x=p2x+d2-2; 
                        printf("\033[1;34mPenalty for player 2...\n\033[0m");
                    }

                    /*MOVE PLAYER UNTIL IT REACHES THE WALL*/
                    else if ((p2x+d2)<=26) p2x+=d2;

                    /*MOVE PLAYER IF IT IS TURNING*/
                    else 
                    {
                        int k=p2x+d2;
                        p2x=26;
                        p2y+=k-26;
                        if (p2y==5) p2y-=2; //check if player places on penalty point after turning 
                    }
                }

                /*RIGHT SECTION OFTHE MAP*/
                else if (p2x==26 && p2y<11)
                {
                    /*PENALTY CHECK*/
                    if ((p2y+d2)==5 || (p2y+d2)==10)
                    {
                        p2y=p2y+d2-2;
                        printf("\033[1;34mPenalty for player 2...\n\033[0m");
                    }

                    /*MOVE PLAYER UNTIL IT REACHES THE WALL*/
                    else if ((p2y+d2)<=11) p2y+=d2;

                    /*MOVE PLAYER IF IT IS TURNING*/
                    else
                    {
                        int k=p2y+d2;
                        p2y=11;
                        p2x-=k-11;
                    }
                }

                /*BOTTOM SECTION OF THE MAP*/
                else if (p2x>3 && p2y==11)
                {
                    /*PENALTY CHECK*/
                    if ((p2x-d2)==10 || (p2x-d2)==18)
                    {
                        p2x=p2x-d2+2;
                        printf("\033[1;34mPenalty for player 2...\n\033[0m");
                    }

                    /*MOVE PLAYER UNTIL IT REACHES THE WALL*/
                    else if ((p2x-d2)>=3) p2x-=d2;

                    /*MOVE PLAYER IF IT IS TURNING*/
                    else
                    {
                        int k= p2x-d2;
                        p2x=3;
                        p2y=p2y+k-3;
                    }
                }

                /*LEFT SECTION OF THE MAP*/
                else if (p2x==3 && p2y>4)
                {
                    /*MOVE PLAYER UNTIL IT REACHES THE FINISH*/
                    if ((p2y-d2)>=4) p2y-=d2;

                    /*PLACE THE PLAYER TO FINISH LINE IF IT REACHES OR PASSES THE FINISH*/
                    else p2y=4;
                }

                /*PLAYER 1*/
                /*UPPER SECTION OF THE MAP*/
                if (p1x<28 && p1y==1)
                {
                    /*PENALTY CHECK*/
                    if ((p1x+d1)==14)
                    {
                        p1x=p1x+d1-2; 
                        printf("\033[1;33mPenalty for player 1...\n\033[0m");
                    }

                    /*MOVE PLAYER UNTIL IT REACHES THE WALL*/
                    else if ((p1x+d1)<=28) p1x+=d1;

                    /*MOVE PLAYER IF IT IS TURNING*/
                    else 
                    {
                        int k=p1x+d1;
                        p1x=28;
                        p1y+=k-28;
                    }
                }
                
                /*RIGHT SECTION OFTHE MAP*/
                else if (p1x==28 && p1y<13)
                {
                    /*PENALTY CHECK*/
                    if ((p1y+d1)==7)
                    {
                        p1y-p1y+d1-2;
                        printf("\033[1;33mPenalty for player 1...\n\033[0m");
                    }

                    /*MOVE PLAYER UNTIL IT REACHES THE WALL*/
                    else if ((p1y+d1)<=13) p1y+=d1;

                    /*MOVE PLAYER IF IT IS TURNING*/
                    else
                    {
                        int k=p1y+d1;
                        p1y=13;
                        p1x-=k-13;
                    }
                }

                /*BOTTOM SECTION OF THE MAP*/
                else if (p1x>1 && p1y==13)
                {
                    /*PENALTY CHECK*/
                    if ((p1x-d1)==14)
                    {
                        p1x=p1x-d1+2;
                        printf("\033[1;33mPenalty for player 1...\n\033[0m");
                    }
                    
                    /*MOVE PLAYER UNTIL IT REACHES THE WALL*/
                    else if ((p1x-d1)>=1) p1x-=d1;

                    /*MOVE PLAYER IF IT IS TURNING*/
                    else
                    {
                        int k= p1x-d1;
                        p1x=1;
                        p1y=p1y+k-1;
                    }
                }

                /*LEFT SECTION OF THE MAP*/
                else if (p1x==1 && p1y>2)
                {
                    /*IF PLAYER 2 HAS ALREADY FINISHED DONT MOVE*/
                    if (p2x==3 && p2y==4);

                    /*MOVE PLAYER UNTIL IT REACHES THE FINISH*/
                    else if ((p1y-d1)>=2) p1y-=d1;

                    /*PLACE THE PLAYER TO FINISH LINE IF IT REACHES OR PASSES THE FINISH*/
                    else p1y=2;
                }

                res=update(p1x,p1y,p2x,p2y); //update returns 1 if player 1 win, returns 2 if player 2 win, returns 0 if race is not over yet
                printMap(p1x,p1y,p2x,p2y);
                if (res==1)
                {
                    printf("\033[1;33m\n\n *** PLAYER 1 WON THE GAME ***\n\n\033[0m");
                    exit(0);
                }
                if (res==2)
                {
                    printf("\033[1;34m\n\n *** PLAYER 2 WON THE GAME ***\n\n\033[0m");
                    exit(0);
                }
            }
    }
}

int dice()
{
    return ((rand() % 6) + 1); //random value between = [1,6]
}

int printMap(int p1x, int p1y, int p2x, int p2y)
{
    for (int k=0; k<ROWS; k++)
    {
        for (int j=0; j<COLUMNS; j++ )
        {
            if (map[k][j]=='\0') printf(" "); //if empty print space
            else
            {
                //print penalty points
                if ((k==1 && j==14) || (k==7 && j==28) || (k==13 && j==14) || (k==3 && j==10) || (k==3 && j==18) || (k==5 && j==26) || (k==10 && j==26) || (k==11 && j==10) || (k==11 && j==18)) 
                {
                    printf("\033[1;31m%c\033[0m",map[k][j]);
                }

                //print finish lines, print player number in green if finished
                else if ((k==2 && j==1) || (k==4 && j==3)) printf("\033[;32m%c\033[0m",map[k][j]);

                //print player locations
                else if ((k==p1y && j==p1x) || (k==p2y && j== p2x))
                {
                    if ((k==p1y && j==p1x)) printf("\033[1;33m%c\033[0m",map[k][j]);
                    else if ((k==p2y && j== p2x)) printf("\033[1;34m%c\033[0m",map[k][j]);
                }

                //print borders
                else
                {
                    printf("%c",map[k][j]);
                }
            }
        }
        printf("\n");
    }
}

int startGame(int p1, int p2)
{
    if (p1>p2)
    {
        printf("\n *** PLAYER 1 will start the game... ***\n");
        return 1;
    }
    else if (p1<p2)
    {
        printf("\n *** PLAYER 2 will start the game... ***\n");
        return 2;
    }
    else
    {
        printf("\nSame dice value... Please try again.\n");
        return 0;
    }
}

int update(int p1x, int p1y, int p2x, int p2y)
{
     /*CLEAN THE STRING*/
    //after passing the string to the function string is not empty and it prints random characters, so clean first.
    for (int k=0; k<ROWS; k++)
    {
        for (int j=0; j<COLUMNS; j++ )
        {
            map[k][j]='\0'; 
        }
    }

    /*SET PENALTY POINTS*/
    map[1][14]='X', map[7][28]='X', map[13][14]='X';
    map[3][10]='X', map[3][18]='X', map[5][26]='X', map[10][26]='X', map[11][10]='X', map[11][18]='X';

    /*SET FINISH LINE*/
    map[2][1]='-', map[4][3]='-';

    /*SET PLAYER LOCATION*/
    map[p1y][p1x]='1', map[p2y][p2x]='2';

    /*SET TOP ROWS*/
    for (int k=0; k<6; k=k+2)
    {
        for (int j=k; j<COLUMNS-k; j++)
        {
            map[k][j]='.';
        }
    }

    /*SET LOWER ROWS*/
    for (int k=10; k<15; k=k+2)
    {
        for (int j=14-k; j<COLUMNS+k-14; j++ )
        {
            map[k][j]='.';
        }
    }
    
    /*SET LEFT COLUMNS*/
    for (int k=0; k<5; k=k+2)
    {
        for (int j=k+1; j< ROWS-k-1; j++)
        {
            map[j][k]=':';
        }
    }

    /*SET RIGHT COLUMNS*/
    for (int k=25; k<30; k=k+2)
    {
        for (int j=COLUMNS-k; j<k-15; j++)
        {
            map[j][k]=':';
        }
    }

    if (p1x==1 && p1y==2) return 1; //player 1 win
    else if (p2x==3 && p2y==4) return 2; //player 2 win 
    else return 0; //if race is not over
}
