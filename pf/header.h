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
    int itemsNo;
    void rockItem(Map &map_, int x, int y);
    void rockEffect();
    void init(int rows, int columns);
    void display() const;
    char getObject(int x, int y) const;
    void setObject(int x, int y, char ch);
    void setZomPos(int x, int y, int z);
    void CombatHUD();
};

class Enemy;

class Player
{
    char AlienSymbol = 'A';
    int posX_, posY_;

    public:
        char prevObj;
        bool hitObject;
        bool hitBarrier;
        bool hitZombie;
        bool alienTurn;
        int AlienZomb;
        int prevX;
        int prevY;
        int posX;
        int posY;
        int AlienAtk = 0;
        int AlienHp;
        std::vector<int> AlienHpVec;
        std::vector<int> AlienMaxHpVec;
        void AlienCreation(int ZombCount);
        void InitialLanding(Map &map_, float x, float y);
        void AlienMove(Map &map_, std::string inp, int x, int y);
        void AlienPlacement(Map &map_);
        void upPos(Map &map_);
        void downPos(Map &map_);
        void leftPos(Map &map_);
        void rightPos(Map &map_);
        void PrintAlienMoveUp();
        void PrintAlienMoveDown();
        void PrintAlienMoveLeft();
        void PrintAlienMoveRight();
        void AlienAttack(int zombieNum, Enemy &Zombie);
        void healthEffect();
};

class Enemy
{
    int EPosX_, EPosY_;

public:
    bool hitBorder;
    bool hitObject;
    bool hitAlien;
    int PrevX;
    int PrevY;
    int randomHp = rand() % 2 + 1;
    int randomAtk = rand() % 2 + 1;
    int randomRng = rand() % 5 + 1;
    int ZombieCount = 1;
    int ZombieHp = 50 + (randomHp * 50);
    int ZombieAtk = 5 + (randomAtk * 5);
    int ZombieRange = randomRng;
    int count = 49; // use to display zombie on the gameboard
    int n = 0; // use to display zombie no. on the HUD
    std::vector<int> ZombPosX; // vector to store each zombie's position x
    std::vector<int> ZombPosY; // vector to store each zombie's position y
    std::vector<int> ZombHpVec;
    std::vector<int> ZombAtkVec;
    std::vector<int> ZombRngVec;
    std::vector<int> ZombDist;
    void ZombieCreation();
    void ZombieLanding(Map &map_, int x, int y);
    void ZombieMove(Map &map_, int x, int y);
    void ZombieAttack(int zombieNum, Player &Alien, Map &map_);
    void upPos(Map &map_, int x);
    void downPos(Map &map_, int x);
    void leftPos(Map &map_, int x);
    void rightPos(Map &map_, int x);
    void ZombieDefeated(int zombieNum, Map &map_, int x, int y);
};

void replaceDot(Map &map_, int rows, int columns);

char randomiseItems(char x);

#endif
