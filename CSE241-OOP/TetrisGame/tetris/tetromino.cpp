#include "tetromino.hpp"

Game::Tetromino::Tetromino(){}; //Tetromino default constructor

Game::Tetromino::Tetromino(tetro tShape){ //Tetromino constructor
    setTetro(tShape);
};

inline char** Game::Tetromino::getVec() const{return tetroVec;}

void Game::Tetromino::setTetro(tetro shape){ //set the tetromino piece that is requested by the user
    tetroEnum=shape; //shape is not being stored so enum values are stored inside tetroEnum which is declared in private section of Tetromino class

    //dynamically allocate tetroVec and set its shape
    tetroVec = new char*[N];
    for(int i = 0; i < N; ++i)
        tetroVec[i] = new char[N];

    switch(shape){
        case tetro::I:
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    if(i==0) tetroVec[i][j]='I';
                    else tetroVec[i][j]=' ';
                }
            }
            break;
        case tetro::O:
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    if(j<2 && i<2) tetroVec[i][j]='O';
                    else tetroVec[i][j]=' ';
                }
            }
            break;
        case tetro::T:
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    if((i==0 && j<3) || (i<2 && j==1)) tetroVec[i][j]='T';
                    else tetroVec[i][j]=' ';
                }
            }
            break;
        case tetro::J:
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    if((i<3 && j==1) || (i==2 && j==0)) tetroVec[i][j]='J';
                    else tetroVec[i][j]=' ';
                }
            }
            break;
        case tetro::L:
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    if((i<3 && j==0) || (i==2 && j==1)) tetroVec[i][j]='L';
                    else tetroVec[i][j]=' ';
                }
            }
            break;
        case tetro::S:
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    if((i==1 && j<2) || (i==0 && j==1) || (i==0 && j==2)) tetroVec[i][j]='S';
                    else tetroVec[i][j]=' ';
                }
            }
            break;
        case tetro::Z:
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    if((i==0 && j<2) || (i==1 && j==1) || (i==1 && j==2)) tetroVec[i][j]='Z';
                    else tetroVec[i][j]=' ';
                }
            }
            break;
    }
}

void Game::Tetromino::rotate(char dir, int amount){ //rotate vector
    if (dir=='R') dir = 'r';
    else if(dir=='L') dir ='l';

    //calculate which is the direction wanted to be rotated
    if (amount%4==2) dir='o';
    else if (amount%4==0) dir='f';
    else if (dir=='r' && amount%4==1) dir='r';
    else if (dir=='r' && amount%4==3) dir='l';
    else if (dir=='l' && amount%4==1) dir='l';
    else if (dir=='l' && amount%4==3) dir='r';

    //delete default shape, reallocate tetroVec and set rotated shape
    for(int i = 0; i < N; ++i){
        delete[] tetroVec[i];
    }
    delete[] tetroVec;

    tetroVec = new char*[N];
    for(int i = 0; i < N; ++i)
        tetroVec[i] = new char[N];

    switch(tetroEnum){
        case tetro::I:
            if(dir=='l' || dir=='r'){
                tetroVec[0][0]='I';
                tetroVec[1][0]='I';
                tetroVec[2][0]='I';
                tetroVec[3][0]='I';
                tetroVec[0][1]=' ';
                tetroVec[1][1]=' ';
                tetroVec[2][1]=' ';
                tetroVec[3][1]=' ';
                tetroVec[0][2]=' ';
                tetroVec[1][2]=' ';
                tetroVec[2][2]=' ';
                tetroVec[3][2]=' ';
                tetroVec[0][3]=' ';
                tetroVec[1][3]=' ';
                tetroVec[2][3]=' ';
                tetroVec[3][3]=' ';
            }
            else if(dir=='f' || dir=='o'){
                tetroVec[0][0]='I';
                tetroVec[1][0]=' ';
                tetroVec[2][0]=' ';
                tetroVec[3][0]=' ';
                tetroVec[0][1]='I';
                tetroVec[1][1]=' ';
                tetroVec[2][1]=' ';
                tetroVec[3][1]=' ';
                tetroVec[0][2]='I';
                tetroVec[1][2]=' ';
                tetroVec[2][2]=' ';
                tetroVec[3][2]=' ';
                tetroVec[0][3]='I';
                tetroVec[1][3]=' ';
                tetroVec[2][3]=' ';
                tetroVec[3][3]=' ';
            }
            break;
        case tetro::O:
            tetroVec[0][0]='O';
            tetroVec[1][0]='O';
            tetroVec[2][0]=' ';
            tetroVec[3][0]=' ';
            tetroVec[0][1]='O';
            tetroVec[1][1]='O';
            tetroVec[2][1]=' ';
            tetroVec[3][1]=' ';
            tetroVec[0][2]=' ';
            tetroVec[1][2]=' ';
            tetroVec[2][2]=' ';
            tetroVec[3][2]=' ';
            tetroVec[0][3]=' ';
            tetroVec[1][3]=' ';
            tetroVec[2][3]=' ';
            tetroVec[3][3]=' ';
            break;
        case tetro::T:
            if(dir=='l')
            {
                tetroVec[0][0]='T';
                tetroVec[1][0]='T';
                tetroVec[2][0]='T';
                tetroVec[3][0]=' ';
                tetroVec[0][1]=' ';
                tetroVec[1][1]='T';
                tetroVec[2][1]=' ';
                tetroVec[3][1]=' ';
                tetroVec[0][2]=' ';
                tetroVec[1][2]=' ';
                tetroVec[2][2]=' ';
                tetroVec[3][2]=' ';
                tetroVec[0][3]=' ';
                tetroVec[1][3]=' ';
                tetroVec[2][3]=' ';
                tetroVec[3][3]=' ';
            }
            else if(dir=='r'){
                tetroVec[0][0]=' ';
                tetroVec[1][0]='T';
                tetroVec[2][0]=' ';
                tetroVec[3][0]=' ';
                tetroVec[0][1]='T';
                tetroVec[1][1]='T';
                tetroVec[2][1]='T';
                tetroVec[3][1]=' ';
                tetroVec[0][2]=' ';
                tetroVec[1][2]=' ';
                tetroVec[2][2]=' ';
                tetroVec[3][2]=' ';
                tetroVec[0][3]=' ';
                tetroVec[1][3]=' ';
                tetroVec[2][3]=' ';
                tetroVec[3][3]=' ';
            }
            else if(dir=='f'){
                tetroVec[0][0]='T';
                tetroVec[1][0]=' ';
                tetroVec[2][0]=' ';
                tetroVec[3][0]=' ';
                tetroVec[0][1]='T';
                tetroVec[1][1]='T';
                tetroVec[2][1]=' ';
                tetroVec[3][1]=' ';
                tetroVec[0][2]='T';
                tetroVec[1][2]=' ';
                tetroVec[2][2]=' ';
                tetroVec[3][2]=' ';
                tetroVec[0][3]=' ';
                tetroVec[1][3]=' ';
                tetroVec[2][3]=' ';
                tetroVec[3][3]=' ';
            }
            else if(dir=='o'){
                tetroVec[0][0]=' ';
                tetroVec[1][0]='T';
                tetroVec[2][0]=' ';
                tetroVec[3][0]=' ';
                tetroVec[0][1]='T';
                tetroVec[1][1]='T';
                tetroVec[2][1]=' ';
                tetroVec[3][1]=' ';
                tetroVec[0][2]=' ';
                tetroVec[1][2]='T';
                tetroVec[2][2]=' ';
                tetroVec[3][2]=' ';
                tetroVec[0][3]=' ';
                tetroVec[1][3]=' ';
                tetroVec[2][3]=' ';
                tetroVec[3][3]=' ';
            }
            break;
        case tetro::J:
            if(dir=='r'){
                tetroVec[0][0]='J';
                tetroVec[1][0]='J';
                tetroVec[2][0]=' ';
                tetroVec[3][0]=' ';
                tetroVec[0][1]=' ';
                tetroVec[1][1]='J';
                tetroVec[2][1]=' ';
                tetroVec[3][1]=' ';
                tetroVec[0][2]=' ';
                tetroVec[1][2]='J';
                tetroVec[2][2]=' ';
                tetroVec[3][2]=' ';
                tetroVec[0][3]=' ';
                tetroVec[1][3]=' ';
                tetroVec[2][3]=' ';
                tetroVec[3][3]=' ';
            }
            else if(dir=='o'){
                tetroVec[0][0]='J';
                tetroVec[1][0]='J';
                tetroVec[2][0]='J';
                tetroVec[3][0]=' ';
                tetroVec[0][1]='J';
                tetroVec[1][1]=' ';
                tetroVec[2][1]=' ';
                tetroVec[3][1]=' ';
                tetroVec[0][2]=' ';
                tetroVec[1][2]=' ';
                tetroVec[2][2]=' ';
                tetroVec[3][2]=' ';
                tetroVec[0][3]=' ';
                tetroVec[1][3]=' ';
                tetroVec[2][3]=' ';
                tetroVec[3][3]=' ';
            }
            else if(dir=='l'){
                tetroVec[0][0]='J';
                tetroVec[1][0]=' ';
                tetroVec[2][0]=' ';
                tetroVec[3][0]=' ';
                tetroVec[0][1]='J';
                tetroVec[1][1]=' ';
                tetroVec[2][1]=' ';
                tetroVec[3][1]=' ';
                tetroVec[0][2]='J';
                tetroVec[1][2]='J';
                tetroVec[2][2]=' ';
                tetroVec[3][2]=' ';
                tetroVec[0][3]=' ';
                tetroVec[1][3]=' ';
                tetroVec[2][3]=' ';
                tetroVec[3][3]=' ';
            }
            else if(dir=='f'){
                tetroVec[0][0]=' ';
                tetroVec[1][0]=' ';
                tetroVec[2][0]='J';
                tetroVec[3][0]=' ';
                tetroVec[0][1]='J';
                tetroVec[1][1]='J';
                tetroVec[2][1]='J';
                tetroVec[3][1]=' ';
                tetroVec[0][2]=' ';
                tetroVec[1][2]=' ';
                tetroVec[2][2]=' ';
                tetroVec[3][2]=' ';
                tetroVec[0][3]=' ';
                tetroVec[1][3]=' ';
                tetroVec[2][3]=' ';
                tetroVec[3][3]=' ';
            }
            break;
        case tetro::L:
            if(dir=='l'){
                tetroVec[0][0]=' ';
                tetroVec[1][0]='L';
                tetroVec[2][0]=' ';
                tetroVec[3][0]=' ';
                tetroVec[0][1]=' ';
                tetroVec[1][1]='L';
                tetroVec[2][1]=' ';
                tetroVec[3][1]=' ';
                tetroVec[0][2]='L';
                tetroVec[1][2]='L';
                tetroVec[2][2]=' ';
                tetroVec[3][2]=' ';
                tetroVec[0][3]=' ';
                tetroVec[1][3]=' ';
                tetroVec[2][3]=' ';
                tetroVec[3][3]=' ';
            }
            else if(dir=='r'){
                tetroVec[0][0]='L';
                tetroVec[1][0]='L';
                tetroVec[2][0]=' ';
                tetroVec[3][0]=' ';
                tetroVec[0][1]='L';
                tetroVec[1][1]=' ';
                tetroVec[2][1]=' ';
                tetroVec[3][1]=' ';
                tetroVec[0][2]='L';
                tetroVec[1][2]=' ';
                tetroVec[2][2]=' ';
                tetroVec[3][2]=' ';
                tetroVec[0][3]=' ';
                tetroVec[1][3]=' ';
                tetroVec[2][3]=' ';
                tetroVec[3][3]=' ';
            }
            else if(dir=='o'){
                tetroVec[0][0]='L';
                tetroVec[1][0]=' ';
                tetroVec[2][0]=' ';
                tetroVec[3][0]=' ';
                tetroVec[0][1]='L';
                tetroVec[1][1]='L';
                tetroVec[2][1]='L';
                tetroVec[3][1]=' ';
                tetroVec[0][2]=' ';
                tetroVec[1][2]=' ';
                tetroVec[2][2]=' ';
                tetroVec[3][2]=' ';
                tetroVec[0][3]=' ';
                tetroVec[1][3]=' ';
                tetroVec[2][3]=' ';
                tetroVec[3][3]=' ';
            }
            else if(dir=='f'){
                tetroVec[0][0]='L';
                tetroVec[1][0]='L';
                tetroVec[2][0]='L';
                tetroVec[3][0]=' ';
                tetroVec[0][1]=' ';
                tetroVec[1][1]=' ';
                tetroVec[2][1]='L';
                tetroVec[3][1]=' ';
                tetroVec[0][2]=' ';
                tetroVec[1][2]=' ';
                tetroVec[2][2]=' ';
                tetroVec[3][2]=' ';
                tetroVec[0][3]=' ';
                tetroVec[1][3]=' ';
                tetroVec[2][3]=' ';
                tetroVec[3][3]=' ';
            }
            break;
        case tetro::S:
            if(dir=='l' || dir=='r'){
                tetroVec[0][0]='S';
                tetroVec[1][0]='S';
                tetroVec[2][0]=' ';
                tetroVec[3][0]=' ';
                tetroVec[0][1]=' ';
                tetroVec[1][1]='S';
                tetroVec[2][1]='S';
                tetroVec[3][1]=' ';
                tetroVec[0][2]=' ';
                tetroVec[1][2]=' ';
                tetroVec[2][2]=' ';
                tetroVec[3][2]=' ';
                tetroVec[0][3]=' ';
                tetroVec[1][3]=' ';
                tetroVec[2][3]=' ';
                tetroVec[3][3]=' ';
            }
            if(dir=='f' || dir=='o'){
                tetroVec[0][0]=' ';
                tetroVec[1][0]='S';
                tetroVec[2][0]=' ';
                tetroVec[3][0]=' ';
                tetroVec[0][1]='S';
                tetroVec[1][1]='S';
                tetroVec[2][1]=' ';
                tetroVec[3][1]=' ';
                tetroVec[0][2]='S';
                tetroVec[1][2]=' ';
                tetroVec[2][2]=' ';
                tetroVec[3][2]=' ';
                tetroVec[0][3]=' ';
                tetroVec[1][3]=' ';
                tetroVec[2][3]=' ';
                tetroVec[3][3]=' ';
            }
            break;
        case tetro::Z:
            if(dir=='l'|| dir=='r'){
                tetroVec[0][0]=' ';
                tetroVec[1][0]='Z';
                tetroVec[2][0]='Z';
                tetroVec[3][0]=' ';
                tetroVec[0][1]='Z';
                tetroVec[1][1]='Z';
                tetroVec[2][1]=' ';
                tetroVec[3][1]=' ';
                tetroVec[0][2]=' ';
                tetroVec[1][2]=' ';
                tetroVec[2][2]=' ';
                tetroVec[3][2]=' ';
                tetroVec[0][3]=' ';
                tetroVec[1][3]=' ';
                tetroVec[2][3]=' ';
                tetroVec[3][3]=' ';
            }
            if(dir=='f' || dir=='o'){
                tetroVec[0][0]='Z';
                tetroVec[1][0]=' ';
                tetroVec[2][0]=' ';
                tetroVec[3][0]=' ';
                tetroVec[0][1]='Z';
                tetroVec[1][1]='Z';
                tetroVec[2][1]=' ';
                tetroVec[3][1]=' ';
                tetroVec[0][2]=' ';
                tetroVec[1][2]='Z';
                tetroVec[2][2]=' ';
                tetroVec[3][2]=' ';
                tetroVec[0][3]=' ';
                tetroVec[1][3]=' ';
                tetroVec[2][3]=' ';
                tetroVec[3][3]=' ';
            }
            break;
    }
}

Game::Tetromino::~Tetromino(){  //user defined destructor to remove dynamically-allocated data
    for(int i = 0; i < N; ++i){
        delete[] tetroVec[i];
        tetroVec[i]=nullptr;
    }
    delete[] tetroVec;
    tetroVec=nullptr;
}