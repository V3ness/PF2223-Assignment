#ifndef PF_HELPER_H
#define PF_HELPER_H

#include <iostream>
#include <windows.h>
#include <time.h>
#include <vector>
#include <iterator>
#include <string>
#include <cmath>
#include <iomanip>

namespace pf
{
    int ClearScreen();
    int Pause();
}

class Map
{
    std::vector<std::vector<char>> map_;
    int rows_, columns_;

public:
    int rows, columns;
    void init(int rows, int columns);
    void display() const;
    char getObject(int x, int y) const;
    void setObject(int x, int y, char ch);

};

class Player
{
    char AlienSymbol = 'A';

    public:
        bool hitObject;
        bool hitBarrier;
        int posX_, posY_;
        int newPosX_;
        int newPosY_;
        int AlienAtk = 0;
        int randomNum = rand() % 3 + 1;
        int AlienHp = 100 + (randomNum * 50);
        void InitialLanding(Map &map_, float x, float y);
        void AlienMove(Map &map_, std::string inp, int x, int y);
        void AlienPlacement(Map &map_);

};



class Enemy
{
    int EPosX_, EPosY_;

public:
    int randomHp = rand() % 2 + 1;
    int randomAtk = rand() % 2 + 1;
    int randomRng = rand() % 5 + 1;
    int ZombieCount;
    int ZombieHp = 100 + (randomHp * 50);
    int ZombieAtk = 5 + (randomAtk * 5);
    int ZombieRange = randomRng;
    std::vector<int> ZombHpVec;
    std::vector<int> ZombAtkVec;
    std::vector<int> ZombRngVec;
    void ZombieCreation();
};

char randomiseItems(char x);

#endif


//TO DO: SETTLE HOW THE FUCK DO I PUT IN THE ALIEN AND MAKE IT MOVE
//       MERGE MAIN AND HEADER OR ELSE ITS GONNA LOOK NASTY