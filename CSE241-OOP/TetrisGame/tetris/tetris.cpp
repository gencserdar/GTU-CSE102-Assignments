#include "tetris.hpp"
#define N 4
#define SLEEP_TIME 50000

Game::Tetris::Tetris(){}; //Tetris default constructor

Game::Tetris::Tetris(int h, int w){ //Tetris constructor
    h=h+2;
    w=w+2;
    //dynamically allocate the board and set values, **board is stored in Tetris class private
    board = new char*[h]; 
    for(int i = 0; i < h; ++i)
        board[i] = new char[w];

    for(int i=0; i<h; i++){
        for(int j=0; j<w; j++){
            if(i==0 || i==h-1) board[i][j]='*';
            else if(j==0 || j==w-1) board[i][j]='*';
            else board[i][j]=' ';
        }
    }
    
    height=h; //height of board, stored in Tetris class private
    width=w; //width of board, stored in Tetris class private
    center=findCenter(); //horizontal center index of board, stored in Tetris class private
}

inline int Game::Tetris::findCenter() const{ //find the horizontal center index of board
    if (width%2==0) return width/2;
    else return (width+1) /2 -1;
}

inline void Game::Tetris::draw() const{ //draw the board
    for (int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
    
bool Game::Tetris::operator+=(char** tetromino){ //overloaded operator "+=" will add tetromino to tetris board
    ind_x=center-1;
    for(int y=0; y<N; y++){
        for (int x = 0; x <N; x++){
            if(tetromino[y][x]!= ' '){ //do not do the proccess for spaces in tetromino matrix
                if(board[y+1][ind_x+x] !=' ') return false; //if cant add return false
                else board[y+1][ind_x+x] = tetromino[y][x];
            }
        }
    }
    system("clear");
    draw(); //draw the board with tetromino added on top
    usleep(SLEEP_TIME); //sleep 50ms
    for(int y=0; y<N; y++){
        for (int x = 0; x <N; x++){
            if(tetromino[y][x]!= ' '){ //do not do the proccess for spaces in tetromino matrix
                board[y+1][ind_x+x] = ' ';
            }
        }
    }
    return true; //return true if successful
}

bool Game::Tetris::checkRight(char** tetromino) const{ //check if the tetromino matrix can be moved to right

    for(int y=0; y<N; y++){
        for (int x = 0; x <N; x++){
            if(tetromino[y][x]!= ' '){
                if(board[ind_y+y+1][ind_x+x+1] != ' ') return false;
            }
        }
    }
    return true;
}

bool Game::Tetris::checkLeft(char** tetromino) const{ //check if the tetromino matrix can be moved to left

    for(int y=0; y<N; y++){
        for (int x = 0; x <N; x++){
            if(tetromino[y][x]!= ' '){
                if(board[ind_y+y+1][ind_x+x+1] != ' ') return false;
            }
        }
    }
    return true;
}

bool Game::Tetris::checkBottom(char **tetromino) const{ //check if the tetromino matrix can be moved to bottom
    for(int y=0; y<N; y++){
        for (int x = 0; x <N; x++){
            if(tetromino[y][x]!= ' '){
                if(board[ind_y+y+2][ind_x+x+1] != ' ') return false;
            }
        }
    }
    return true;
}

void Game::Tetris::animate(char** tetromino){ //animates the tetromino piece until it reaches its position which is asked from the user
    for(int j=0; j<=ind_y; j++){ 
        for(int y=0; y<N; y++){
            for (int x = 0; x <N; x++){
                if(tetromino[y][x]!= ' '){
                    if(board[j+y+1][ind_x+x+1]== ' ')
                        board[j+y+1][ind_x+x+1] = tetromino[y][x];
                }
            }
        }

        draw();
        usleep(SLEEP_TIME);
        if(j!=ind_y){ //erase the placed tetrominos until tetromino reaches its fitted position
            system ("clear");
            for(int y=0; y<N; y++){
                for (int x = 0; x <N; x++){
                    if(tetromino[y][x]!= ' ' )
                        board[j+y+1][ind_x+x+1] = ' ';
                }
            }
        }
    }
    
}

char Game::Tetris::roll() const{ //random tetromino
    int roll = (rand() % 7) + 1; //random number between 1 and 7
    switch(roll){
        case 1:
            return('I');
            break;
        case 2:
            return('O');
            break;
        case 3:
            return('T');
            break;
        case 4:
            return('J');
            break;
        case 5:
            return('L');
            break;
        case 6:
            return('S');
            break;
        case 7:
            return('Z');
            break;
    }
    return('Q'); //if failed return Q and exit program
}

bool Game::Tetris::move(char** tetromino, char dir, int amount){//function that checks if the tetromino can be moved to the index entered. calls animate function
    //and places if it can be moved
    ind_x=center-2;
    switch(dir){
        case 'r':
        case 'R':
            for (int i=0;i<amount; i++){
                ind_x++;
                if(!checkRight(tetromino)) return false; //if cant go to right until the desired index, return false. this will end the game.
            }
            break;
        case 'l':
        case 'L':
            for (int i=0;i<amount; i++){
                ind_x--;
                if(!checkLeft(tetromino)) return false; //if cant go to left until the desired index, return false. this will end the game.
            }
            break;
    }
    while(checkBottom(tetromino)) ind_y++; //go to bottom as deep as possible
    animate(tetromino);
    ind_y=0; //reset y index after the placing proccess is done
    return true;
}

Game::Tetris::~Tetris(){ //user defined destructor to remove dynamically-allocated data
    for(int i = 0; i < height; ++i){
        delete[] board[i];   
        board[i]=nullptr;
    }
    delete[] board;
    board=nullptr;
}
