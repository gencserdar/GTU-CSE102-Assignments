#include "tetris.cpp"
#include "tetromino.cpp"
#define BOARDSIZE 10

int main(){
    Game::Tetris playground(BOARDSIZE,BOARDSIZE);
    
    Game::Tetromino i((tetro)'I');
    playground+=i.getVec();
    i.rotate('r',1);
    playground.move(i.getVec(),'r',1);

    Game::Tetromino o((tetro)'O');
    playground+=o.getVec();
    i.rotate('r',2);
    playground.move(o.getVec(),'l',2);

    Game::Tetromino j((tetro)'J');
    playground+=j.getVec();
    j.rotate('r',3);
    playground.move(j.getVec(),'r',3);
  
    Game::Tetromino l((tetro)'L');
    playground+=l.getVec();
    l.rotate('r',4);
    playground.move(l.getVec(),'l',1);
 
    Game::Tetromino z((tetro)'Z');
    playground+=z.getVec();
    z.rotate('l',1);
    playground.move(z.getVec(),'r',1);
  
    Game::Tetromino s((tetro)'S');
    playground+=s.getVec();
    s.rotate('l',2);
    playground.move(s.getVec(),'l',1);
 
    Game::Tetromino t((tetro)'T');
    playground+=t.getVec();
    t.rotate('l',3);
    playground.move(t.getVec(),'r',1);

    Game::Tetromino tt((tetro)'T');
    tt.rotate('l',4);
    if(!(playground+=tt.getVec())){
        cout <<endl<<"-------------------------------"<< endl<<"Welcome to my Tetris game."<<endl<<"-------------------------------"<< endl;
    }
    
    return 0;
}
