#include <iostream>
#include <vector>
#include "tetromino.hpp"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#ifndef TETRIS
#define TETRIS
using namespace std;

namespace Game{
    class Tetris{
        public:
            Tetris();
            Tetris(int h,int w);
            int findCenter() const;
            void draw() const;
            bool operator+=(char** tetromino);
            bool checkRight(char** tetromino) const;
            bool checkLeft(char** tetromino) const;
            bool checkBottom(char** tetromino) const;
            void animate(char** tetromino);
            char roll() const;
            bool move(char** tetromino, char dir, int amount);
            ~Tetris();
        private:
            char** board;
            int width,height,center,ind_x=0,ind_y=0;
    };
}
#endif