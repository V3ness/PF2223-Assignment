#include "header.h"
#include <cstdlib>
#include <iostream>

namespace pf
{
    int ClearScreen()
    {
        #if defined(_WIN32)
            return std::system("cls");
        #elif defined(__linux__) || defined(__APPLE__)
            return std::system("clear");
        #endif
    }

    int Pause()
    {
        #if defined(_WIN32)
            return std::system("pause");
        #elif defined(__linux__) || defined(__APPLE__)
            return std::system(R"(read -p "Press any key to continue . . . " dummy)");
        #endif
    }
}

void Player::CreateAlien()
{
    int randomNum = rand() % 3 + 1;
    AlienHp = 100 + (randomNum * 50);
    std::cout << "\n  Alien    : Life " << AlienHp << ", Attack  " << AlienAtk;
}

void Enemy::CreateZombie()
{
    int randomHp = rand() % 2 + 1;
    int randomAtk = rand() % 2 + 1;
    ZombieHp = 100 + (randomHp * 50);
    ZombieAtk = 5 + (randomAtk * 5);
    std::cout << "\n  Zombie   : Life " << ZombieHp << ", Attack  " << ZombieAtk << ", Range " << ZombieRange;
}
