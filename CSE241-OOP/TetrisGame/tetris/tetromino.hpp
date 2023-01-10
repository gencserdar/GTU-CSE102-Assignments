#include <iostream>
#include <vector>
#ifndef TETROMINO
#define TETROMINO
using namespace std;

enum tetro{
    I='I',O='O',T='T',J='J',L='L',S='S',Z='Z'
};

namespace Game{
    class Tetromino{
        public:
            Tetromino();
            Tetromino(tetro tShape);
            char** getVec() const;
            void rotate(char dir, int amount);
            void setTetro(tetro shape);
            ~Tetromino();
        private:
            tetro tetroEnum;
            char** tetroVec;
    };
}
#endif