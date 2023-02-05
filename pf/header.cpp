#include "header.h"
#include <cstdlib>
#include <iostream>
#include <ctime>

void Map::init(int rows1, int columns1)
{
    rows_ = rows1;
    columns_ = columns1;
    rows = rows_;
    columns = columns_;
    char randobjects[] = {' ', ' ', ' ', ' ', ' ', 'r', 'h', 'v', '^', '<', '>', 'p'};
    int noOfObjects = 12; // number of objects in the objects array
    // create dynamic 2D array using vector
    map_.resize(columns_); // create empty rows
    for (int i = 0; i < columns_; ++i)
    {
        map_[i].resize(rows_); // resize each row
    }
    // put random characters into the vector array
    for (int i = 0; i < columns_; ++i)
    {
        for (int j = 0; j < rows_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = randobjects[objNo];
        }
    }
}

void Map::display() const
{
    std::cout << ".: Alien vs Zombie :." << std::endl;

    // Prints out each row
    for (int i = 0; i < columns_; ++i)
    {
        // Displays border for top row
        std::cout << "  ";
        for (int j = 0; j < rows_; ++j)
        {
            std::cout << "+-";
        }
        std::cout << "+" << std::endl;
        // Displays Row Number
        std::cout << std::setw(2) << (i + 1);
        // Displays the vector contents and border in between them
        for (int j = 0; j < rows_; ++j)
        {
            std::cout << "|" << map_[i][j];
        }
        std::cout << "|" << std::endl;
    }
    // Display the border for the last row
    std::cout << "  ";
    for (int j = 0; j < rows_; ++j)
    {
        std::cout << "+"
                  << "-";
    }
    std::cout << "+" << std::endl;
    // display column number
    std::cout << "  ";
    for (int j = 0; j < rows_; ++j)
    {
        int digit = (j + 1) / 10;
        std::cout << " ";
        if (digit == 0)
            std::cout << " ";
        else
            std::cout << digit;
    }
    std::cout << std::endl;
    std::cout << "  ";
    for (int j = 0; j < rows_; ++j)
    {
        std::cout << " " << (j + 1) % 10;
    }
    std::cout << std::endl;
}

void replaceDot(Map &map_, int rows, int columns)
{
    Map map;
    for (int i = 1; i < columns + 1; i++)
    {
        for (int j = 1; j < rows + 1; j++)
        {
            char x = map_.getObject(i, j);
            if (x == '.')
            {
                char rockItems[] = {'h', 'p', '^', 'v', '<', '>', ' ', 'r', ' ', ' ', ' ', ' '};
                int noOfItems = 12;
                int itemsNo = rand() % noOfItems;
                char replacedItem = rockItems[itemsNo];
                map_.setObject(i, j, replacedItem);
            }
        }
    }
    pf::ClearScreen();
    map_.display();
    map.CombatHUD();
    std::cout << "\n\nAlien's turn ends. The trail is reset.\n\n";
    pf::Pause();
}

char Map::getObject(int x, int y) const
{
    return map_[y - 1][x - 1];
}

void Map::setObject(int x, int y, char ch)
{
    map_[y - 1][x - 1] = ch;
}

void Map::setZomPos(int x, int y, int z)
{
    map_[y - 1][x - 1] = z;
}

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

void Player::AlienCreation()
{
    int AlienAtk = 0;
    int randomNum = rand() % 3 + 1;
    int const AlienHp = 100 + (randomNum * 50);
    int const MaxAlienHp = AlienHp;
    AlienHpVec.push_back(AlienHp);
}

void Player::InitialLanding(Map &map_, float x, float y)
{
    float middleX, middleY;
    // Get middle positions based on the size of map
    middleX = ceil(x / 2);
    middleY = ceil(y / 2);
    posX_ = middleX;
    posY_ = middleY;
    posX = posX_;
    posY = posY_;

    map_.setObject(middleX, middleY, AlienSymbol);
}

void Enemy::ZombieLanding(Map &map_, int x, int y)
{
    Player Alien;
    Map map;
    float randomX, randomY;
    for (int i = 0; i < ZombieCount; i++)
    {
        randomX = rand() % x + 1;
        randomY = rand() % y + 1;
        if (randomX == Alien.posX && randomY == Alien.posY)
        {
            randomX = rand() % x + 1;
            randomY = rand() % y + 1;
            EPosX_ = randomX;
            EPosY_ = randomY;
            PosX = EPosX_;
            PosY = EPosY_;
            int z = 49 + i;

            map_.setZomPos(randomX, randomY, z);
        }
        else
        {
            EPosX_ = randomX;
            EPosY_ = randomY;
            PosX = EPosX_;
            PosY = EPosY_;
            int z = 49 + i;

            map_.setZomPos(randomX, randomY, z);
        }
    }
}

void rockItem(Map &map_, int x, int y)
{
    char rockItems[] = {'h', 'p', '^', 'v', '<', '>', ' '};
    int noOfItems = 7;
    int itemsNo = rand() % noOfItems;
    char replacedItem = rockItems[itemsNo];
    map_.setObject(x, y, replacedItem);
}

void rockEffect()
{
    std::cout << "\n\nAlien hit rock!\n" << std::endl;
}

void healthEffect(int AlienHp, int MaxAlienHp)
{
    if (AlienHp < MaxAlienHp)
    {
        std::cout << "\n\nYour Alien has miraculously gained 20 health through the power of healthpack!\n" << std::endl;
        AlienHp = AlienHp + 20;
    }
    else
    {
        std::cout << "\n\nYour Alien is still healthy. There's no need for recover.\n" << std::endl;
    }
}

void podEffect() // after implement zombies, needs to put in zombies
{
    std::cout << "\n\nYour Alien has encountered a pod that deals 10 damage to the nearest zombie!\n" << std::endl;
}

void Player::upPos(Map &map_)
{
    prevX = posX;
    prevY = posY;
    posX = posX;
    posY = posY - 1;
    map_.setObject(prevX, prevY, '.');
    map_.setObject(posX, posY, 'A');
}

void Player::downPos(Map &map_)
{
    prevX = posX;
    prevY = posY;
    posX = posX;
    posY = posY + 1;
    map_.setObject(prevX, prevY, '.');
    map_.setObject(posX, posY, 'A');
}

void Player::leftPos(Map &map_)
{
    prevX = posX;
    prevY = posY;
    posX = posX - 1;
    posY = posY;
    map_.setObject(prevX, prevY, '.');
    map_.setObject(posX, posY, 'A');
}

void Player::rightPos(Map &map_)
{
    prevX = posX;
    prevY = posY;
    posX = posX + 1;
    posY = posY;
    map_.setObject(prevX, prevY, '.');
    map_.setObject(posX, posY, 'A');
}

void Player::AlienMove(Map &map_, std::string inp, int x, int y)
{
    Map map;
    Enemy Zombie;
    if (inp == "up")
    {
        do
        {
            if (posY == 1)
            {
                prevObj = 'q';     // Resets prev object to q
                hitBarrier = true; // Stops alien from moving out of gameboard
            }
            else
            {
                hitBarrier = false;
                char objectOnTop;
                if (posY != 0)
                {
                    objectOnTop = map_.getObject(posX, posY - 1); // Get the object on top
                }
                switch (objectOnTop) // Switches depending on the object on top of alien
                {
                case 'r':                           // Special Case: Rock will stop the alien and change into a random object
                    rockItem(map_, posX, posY - 1); // Randomises item on the rock
                    prevObj = 'r';                  // Sets prev object to r so that the arrows won't glitch out
                    hitObject = true;               // This will make the movement code loop with the same direction unless it is true, which in this case, stops.
                    pf::ClearScreen();              // Duh
                    map_.display();                 // Duh
                    map.CombatHUD();                // Duh
                    rockEffect();                   // It's just an output of alien hitting a rock, we should remove it sometime soon
                    pf::Pause();                    // Duh
                    break;

                case 'p':
                    if (prevObj == 'r') // If the object before was a rock,
                    {                   // this code ensures it will continue forward to step on 'p'
                        prevObj = 'q';  // as it will reset the prevObj variable
                        break;          // to let the alien through
                    }
                    else
                    {
                        podEffect();             // It will deal damage to the nearest zombie
                        if (hitBarrier == false) // This is a redundant code to check if hitbarrier is false, but just to be safe
                        {
                            upPos(map_); // Moves the alien upwards
                        }
                        prevObj = 'p';
                        hitObject = false;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        podEffect();
                        pf::Pause();
                        inp = "up"; // Just to ensure the alien will still go up
                        break;
                    }

                case 'h':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            upPos(map_);
                        }
                        prevObj = 'h';
                        hitObject = false;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        healthEffect(AlienHp, MaxAlienHp);
                        pf::Pause();
                        inp = "up";
                        break;
                    }

                case ' ':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            upPos(map_);
                        }
                        prevObj = ' ';
                        hitObject = false;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nAlien sees no obstacle in front of it and walks gracefully towards it.\n" << std::endl;
                        pf::Pause();
                        inp = "up";
                        break;
                    }

                case '^':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            upPos(map_);
                        }
                        hitObject = true;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nAlien sees an arrow in front of it and it pulls the alien upwards.\n" << std::endl;
                        pf::Pause();
                        inp = "up";
                        AlienMove(map_, "up", map_.rows, map_.columns);
                        break;
                    }

                case 'v':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            upPos(map_);
                        }
                        hitObject = true;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nAlien sees an arrow and a force has pulled upon him downwards\n" << std::endl;
                        pf::Pause();
                        inp = "down";
                        AlienMove(map_, "down", map_.rows, map_.columns);
                        break;
                    }

                case '<':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            upPos(map_);
                        }
                        hitObject = true;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nThe force has recognised the alien and decided left was his path.\n" << std::endl;
                        pf::Pause();
                        inp = "left";
                        AlienMove(map_, "left", map_.rows, map_.columns);
                        break;
                    }

                case '>':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            upPos(map_);
                        }
                        hitObject = true;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nAlien went to the right because it wanted to be right.\n" << std::endl;
                        pf::Pause();
                        inp = "right";
                        AlienMove(map_, "right", map_.rows, map_.columns);
                        break;
                    }

                default:
                    break;
                }
            }
        } while (hitBarrier == false && hitObject == false);
    }
    if (inp == "down")
    {
        do
        {
            if (posY == map_.columns)
            {
                prevObj = 'q';
                hitBarrier = true;
            }
            else
            {
                hitBarrier = false;
                char objectOnTop;
                if (posY != y)
                {
                    objectOnTop = map_.getObject(posX, posY + 1);
                }
                switch (objectOnTop)
                {
                case 'r':
                    hitObject = true;
                    prevObj = 'r';
                    rockItem(map_, posX, posY + 1);
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    rockEffect();
                    pf::Pause();
                    break;

                case 'p':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            downPos(map_);
                        }
                        prevObj = 'p';
                        hitObject = false;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        podEffect();
                        pf::Pause();
                        inp = "down";
                        break;
                    }

                case 'h':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false) // add if statements for prevobj = r later
                        {
                            downPos(map_);
                        }
                        prevObj = 'h';
                        hitObject = false;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        healthEffect(AlienHp, MaxAlienHp);
                        pf::Pause();
                        inp = "down";
                        break;
                    }

                case ' ':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            downPos(map_);
                        }
                        prevObj = ' ';
                        hitObject = false;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nAlien sees no obstacle in front of it and walks gracefully towards it.\n" << std::endl;
                        pf::Pause();
                        inp = "down";
                        break;
                    }

                case '^':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            downPos(map_);
                        }
                        hitObject = true;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nAlien sees an arrow in front of it and it pulls the alien upwards.\n" << std::endl;
                        pf::Pause();
                        inp = "up";
                        AlienMove(map_, "up", map_.rows, map_.columns);
                        break;
                    }

                case 'v':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            downPos(map_);
                        }
                        hitObject = true;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nAlien sees an arrow and a force has pulled upon him downwards.\n" << std::endl;
                        pf::Pause();
                        inp = "down";
                        AlienMove(map_, "down", map_.rows, map_.columns);
                        break;
                    }

                case '<':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            downPos(map_);
                        }
                        hitObject = true;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nThe force has recognised the alien and decided left was his path.\n" << std::endl;
                        pf::Pause();
                        inp = "left";
                        AlienMove(map_, "left", map_.rows, map_.columns);
                        break;
                    }

                case '>':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            downPos(map_);
                        }
                        hitObject = true;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nAlien went to the right because it wanted to be right.\n" << std::endl;
                        pf::Pause();
                        AlienMove(map_, "right", map_.rows, map_.columns);
                        break;
                    }

                default:
                    break;
                }
            }
        } while (hitBarrier == false && hitObject == false);
    }
    if (inp == "left")
    {
        do
        {
            if (posX == 1)
            {
                std::cout << "hA" << std::endl;
                prevObj = 'q';
                hitBarrier = true;
                break;
            }
            else
            {
                hitBarrier = false;
                char objectOnTop;
                if (posX != 0)
                {
                    objectOnTop = map_.getObject(posX - 1, posY);
                }
                switch (objectOnTop)
                {
                case 'r':
                    hitObject = true;
                    prevObj = 'r';
                    rockItem(map_, posX - 1, posY);
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    rockEffect();
                    pf::Pause();
                    break;

                case 'p':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            leftPos(map_);
                        }
                        hitObject = false;
                        prevObj = 'p';
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        podEffect();
                        pf::Pause();
                        inp = "left";
                        break;
                    }

                case 'h':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            leftPos(map_);
                        }
                        prevObj = 'h';
                        hitObject = false;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        healthEffect(AlienHp, MaxAlienHp);
                        pf::Pause();
                        inp = "left";
                        break;
                    }

                case ' ':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            leftPos(map_);
                        }
                        prevObj = ' ';
                        hitObject = false;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nAlien sees no obstacle in front of it and walks gracefully towards it.\n" << std::endl;
                        pf::Pause();
                        inp = "left";
                        break;
                    }

                case '^':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            leftPos(map_);
                        }
                        hitObject = true;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nAlien sees an arrow in front of it and it pulls the alien upwards.\n" << std::endl;
                        pf::Pause();
                        inp = "up";
                        AlienMove(map_, "up", map_.rows, map_.columns);
                        break;
                    }

                case 'v':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            leftPos(map_);
                        }
                        hitObject = true;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nAlien sees an arrow and a force has pulled upon him downwards.\n" << std::endl;
                        pf::Pause();
                        inp = "down";
                        AlienMove(map_, "down", map_.rows, map_.columns);
                        break;
                    }

                case '<':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            leftPos(map_);
                        }
                        hitObject = true;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nThe force has recognised the alien and decided left was his path.\n" << std::endl;
                        pf::Pause();
                        inp = "left";
                        AlienMove(map_, "left", map_.rows, map_.columns);
                        break;
                    }

                case '>':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            leftPos(map_);
                        }
                        hitObject = true;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nAlien went to the right because it wanted to be right.\n" << std::endl;
                        pf::Pause();
                        inp = "right";
                        AlienMove(map_, "right", map_.rows, map_.columns);
                        break;
                    }

                default:
                    break;
                }
            }
        } while (hitBarrier == false && hitObject == false);
    }
    if (inp == "right")
    {
        do
        {
            if (posX == map_.rows)
            {
                prevObj = 'q';
                hitBarrier = true;
                break;
            }
            else
            {
                hitBarrier = false;
                char objectOnTop;
                if (posX != x)
                {
                    objectOnTop = map_.getObject(posX + 1, posY);
                }
                switch (objectOnTop)
                {

                case 'r':
                    hitObject = true;
                    prevObj = 'r';
                    rockItem(map_, posX + 1, posY);
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    rockEffect();
                    pf::Pause();
                    break;

                case 'p':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            rightPos(map_);
                        }
                        prevObj = 'p';
                        hitObject = false;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        podEffect();
                        pf::Pause();
                        inp = "right";
                        break;
                    }

                case 'h':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            rightPos(map_);
                        }
                        prevObj = 'h';
                        hitObject = false;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        healthEffect(AlienHp, MaxAlienHp);
                        pf::Pause();
                        inp = "right";
                        break;
                    }

                case ' ':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            rightPos(map_);
                        }
                        prevObj = ' ';
                        hitObject = false;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nAlien sees no obstacle in front of it and walks gracefully towards it.\n" << std::endl;
                        pf::Pause();
                        inp = "left";
                        break;
                    }

                case '^':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            rightPos(map_);
                        }
                        hitObject = true;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nAlien sees an arrow in front of it and it pulls the alien upwards.\n" << std::endl;
                        pf::Pause();
                        inp = "up";
                        AlienMove(map_, "up", map_.rows, map_.columns);
                        break;
                    }

                case 'v':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            rightPos(map_);
                        }
                        hitObject = true;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nAlien sees an arrow and a force has pulled upon him downwards.\n" << std::endl;
                        pf::Pause();
                        inp = "down";
                        AlienMove(map_, "down", map_.rows, map_.columns);
                        break;
                    }

                case '<':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            rightPos(map_);
                        }
                        hitObject = true;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nThe force has recognised the alien and decided left was his path.\n" << std::endl;
                        pf::Pause();
                        inp = "left";
                        AlienMove(map_, "left", map_.rows, map_.columns);
                        break;
                    }

                case '>':
                    if (prevObj == 'r')
                    {
                        prevObj = 'q';
                        break;
                    }
                    else
                    {
                        if (hitBarrier == false)
                        {
                            rightPos(map_);
                        }
                        hitObject = true;
                        pf::ClearScreen();
                        map_.display();
                        map.CombatHUD();
                        std::cout << "\n\nAlien went to the right because it wanted to be right.\n" << std::endl;
                        pf::Pause();
                        inp = "right";
                        AlienMove(map_, "right", map_.rows, map_.columns);
                        break;
                    }

                default:
                    break;
                }
            }
        } while (hitBarrier == false && hitObject == false);
    }
}

void Player::AlienPlacement(Map &map_)
{
}

void Enemy::upPos(Map &map_)
{
    PrevX = PosX;
    PrevY = PosY;
    PosX = PosX;
    PosY = PosY - 1;
    map_.setObject(PrevX, PrevY, ' ');
    map_.setZomPos(PosX, PosY, 49);
}

void Enemy::downPos(Map &map_)
{
    PrevX = PosX;
    PrevY = PosY;
    PosX = PosX;
    PosY = PosY + 1;
    map_.setObject(PrevX, PrevY, ' ');
    map_.setZomPos(PosX, PosY, 49);
}

void Enemy::leftPos(Map &map_)
{
    PrevX = PosX;
    PrevY = PosY;
    PosX = PosX - 1;
    PosY = PosY;
    map_.setObject(PrevX, PrevY, ' ');
    map_.setZomPos(PosX, PosY, 49);
}

void Enemy::rightPos(Map &map_)
{
    PrevX = PosX;
    PrevY = PosY;
    PosX = PosX + 1;
    PosY = PosY;
    map_.setObject(PrevX, PrevY, ' ');
    map_.setZomPos(PosX, PosY, 49);
}

void PrintZombMoveUp()
{
    std::cout << "\n\nZombie moves up.\n\n";
}

void PrintZombMoveDown()
{
    std::cout << "\n\nZombie moves down.\n\n";
}

void PrintZombMoveLeft()
{
    std::cout << "\n\nZombie moves left.\n\n";
}

void PrintZombMoveRight()
{
    std::cout << "\n\nZombie moves right.\n\n";
}

void Enemy::ZombieMove(Map &map_, int x, int y)
{
    Map map;
    int randDir;
    randDir = rand() % 4;
    // 0 = up, 1 = down, 2 = left, 3 = right
    if (randDir == 0)
    {
        do
        {
            if (PosY == 1)
            {
                hitBorder = true;
                ZombieMove(map_, x, y);
            }
            else
            {
                hitBorder = false;
                char nxtObj;
                if (PosY != 0)
                {
                    nxtObj = map_.getObject(PosX, PosY - 1);
                }
                switch (nxtObj)
                {
                case 'A':
                    hitAlien = true;
                    randDir = rand() % 4;
                    break;

                case 'r':
                    upPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveUp();
                    pf::Pause();
                    break;

                case 'p':
                    upPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveUp();
                    pf::Pause();
                    break;

                case 'h':
                    upPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveUp();
                    pf::Pause();
                    break;

                case ' ':
                    upPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveUp();
                    pf::Pause();
                    break;

                case '^':
                    upPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveUp();
                    pf::Pause();
                    break;

                case 'V':
                    upPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveUp();
                    pf::Pause();
                    break;

                case '<':
                    upPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveUp();
                    pf::Pause();
                    break;

                case '>':
                    upPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveUp();
                    pf::Pause();
                    break;

                default:
                    break;
                }
            }
        } while (hitBorder == false && hitAlien == false && hitObject == false);
    }
    if (randDir == 1)
    {
        do
        {
            if (PosY == y)
            {
                hitBorder = true;
                ZombieMove(map_, x, y);
            }
            else
            {
                hitBorder = false;
                char nxtObj;
                if (PosY != 0)
                {
                    nxtObj = map_.getObject(PosX, PosY + 1);
                }
                switch (nxtObj)
                {
                case 'A':
                    hitAlien = true;
                    randDir = rand() % 4;
                    break;

                case 'r':
                    downPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveDown();
                    pf::Pause();
                    break;

                case 'p':
                    downPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveDown();
                    pf::Pause();
                    break;

                case 'h':
                    downPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveDown();
                    pf::Pause();
                    break;

                case ' ':
                    downPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveDown();
                    pf::Pause();
                    break;

                case '^':
                    downPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveDown();
                    pf::Pause();
                    break;

                case 'V':
                    downPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveDown();
                    pf::Pause();
                    break;

                case '<':
                    downPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveDown();
                    pf::Pause();
                    break;

                case '>':
                    downPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveDown();
                    pf::Pause();
                    break;

                default:
                    break;
                }
            }
        } while (hitBorder == false && hitAlien == false && hitObject == false);
    }
    if (randDir == 2)
    {
        do
        {
            if (PosX == 1)
            {
                hitBorder = true;
                ZombieMove(map_, x, y);
            }
            else
            {
                hitBorder = false;
                char nxtObj;
                if (PosY != 0)
                {
                    nxtObj = map_.getObject(PosX - 1, PosY);
                }
                switch (nxtObj)
                {
                case 'A':
                    hitAlien = true;
                    randDir = rand() % 4;
                    break;

                case 'r':
                    leftPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveLeft();
                    pf::Pause();
                    break;

                case 'p':
                    leftPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveLeft();
                    pf::Pause();
                    break;

                case 'h':
                    leftPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveLeft();
                    pf::Pause();
                    break;

                case ' ':
                    leftPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveLeft();
                    pf::Pause();
                    break;

                case '^':
                    leftPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveLeft();
                    pf::Pause();
                    break;

                case 'V':
                    leftPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveLeft();
                    pf::Pause();
                    break;

                case '<':
                    leftPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveLeft();
                    pf::Pause();
                    break;

                case '>':
                    leftPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveLeft();
                    pf::Pause();
                    break;

                default:
                    break;
                }
            }
        } while (hitBorder == false && hitAlien == false && hitObject == false);
    }
    if (randDir == 3)
    {
        do
        {
            if (PosX == x)
            {
                hitBorder = true;
                ZombieMove(map_, x, y);
            }
            else
            {
                hitBorder = false;
                char nxtObj;
                if (PosY != 0)
                {
                    nxtObj = map_.getObject(PosX + 1, PosY);
                }
                switch (nxtObj)
                {
                case 'A':
                    hitAlien = true;
                    randDir = rand() % 4;
                    break;

                case 'r':
                    rightPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveRight();
                    pf::Pause();
                    break;

                case 'p':
                    rightPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveRight();
                    pf::Pause();
                    break;

                case 'h':
                    rightPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveRight();
                    pf::Pause();
                    break;

                case ' ':
                    rightPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveRight();
                    pf::Pause();
                    break;

                case '^':
                    rightPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveRight();
                    pf::Pause();
                    break;

                case 'V':
                    rightPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveRight();
                    pf::Pause();
                    break;

                case '<':
                    rightPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveRight();
                    pf::Pause();
                    break;

                case '>':
                    rightPos(map_);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveRight();
                    pf::Pause();
                    break;

                default:
                    break;
                }
            }
        } while (hitBorder == false && hitAlien == false && hitObject == false);
    }
}

void Enemy::ZombieCreation()
{
    for (int i = 0; i < ZombieCount; i++)
    {
        int randomHp = rand() % 2 + 1;
        int randomAtk = rand() % 2 + 1;
        int randomRng = rand() % 5 + 1;
        int ZombieHp = 100 + (randomHp * 50);
        int ZombieAtk = 5 + (randomAtk * 5);
        int ZombieRange = randomRng;
        ZombHpVec.push_back(ZombieHp);
        ZombAtkVec.push_back(ZombieAtk);
        ZombRngVec.push_back(ZombieRange);
    }
}
