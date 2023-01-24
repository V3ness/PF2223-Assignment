#ifndef PF_HELPER_H
#define PF_HELPER_H

namespace pf
{
    int ClearScreen();
    int Pause();
}

class Player
{
    public:
        int AlienAtk = 0;
        int randomNum = rand() % 3 + 1;
        int AlienHp = 100 + (randomNum * 50);
};

class Enemy
{
    public:
        int randomHp = rand() % 2 + 1;
        int randomAtk = rand() % 2 + 1;
        int randomRng = rand() % 5 + 1;
        int ZombieHp = 100 + (randomHp * 50);
        int ZombieAtk = 5 + (randomAtk * 5);
        int ZombieRange = randomRng;
        void ZombieCreation();
};

char randomiseItems(char x);

#endif
