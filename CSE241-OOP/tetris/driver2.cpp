#include "tetris.cpp"
#include "tetromino.cpp"

int main(){
    int width,height,count;
    char tInput,dir;
    cout << "Enter the size of board (height,width)" << endl;
    cin >> height >> width;
    Game::Tetris playground(height,width); //create Tetris object
    while (true){
        cout << "Enter the tetromino type(I,O,T,J,L,S,Z) or Operation(R: for random, Q: to quit) " << endl;
        do{
            cin >> tInput;
            if (tInput!='O' && tInput!='J' && tInput!='T' && tInput!='I' && tInput!='L' && tInput!='Z' && tInput!='S'&& tInput!='R'&& tInput!='Q') {
                cout << "You can only enter the following inputs (CAPITALIZED ONLY) : I,O,T,J,L,S,Z,R,Q" << endl;
            }
            else break;
        }while (true);
        if (tInput=='Q') exit(0);
        else if (tInput=='R'){
            tInput=playground.roll(); //get random tetromino
        }
        if (tInput=='Q') exit(1); //if error occures while roll function, tInput will be equal to Q and program will terminate with exit status 1
        Game::Tetromino t((tetro)tInput); //create a Tetromino object and send the enum parameter to the constructor
        
        if (!(playground+=t.getVec()))break; //if cant add tetromino to top middle, end the game
    
        cout << "Enter which direction to rotate.(l,r)"<<endl;
        cin >> dir;

        cout << "Enter the amount of rotation to be applied"<<endl;
        cin >> count;

        t.rotate(dir,count);
                
        cout << "Enter which direction to move.(l,r)"<<endl;
        cin >> dir;

        cout << "How many units do you want to move?"<<endl;
        cin >> count;

        if(!playground.move(t.getVec(),dir,count)){ //if cant move to the index entered, end the game
            cout<<endl<<"----------------------------------------------"<<endl<<"You cant move to this index."<<endl<<"----------------------------------------------"<<endl;
            break;
        }
    }
    cout <<endl<<"----------------------------------------------"<<endl<< "******************GAME  OVER******************" <<endl<<"----------------------------------------------"<<endl;
    return 0;
}