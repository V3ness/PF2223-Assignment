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
        int AlienHp, AlienAtk = 0;
        void CreateAlien();
};

class Enemy
{
    public:
        int ZombieHp, ZombieAtk, ZombieRange;
        void CreateZombie();
};

char randomiseItems(char x);

#endif
