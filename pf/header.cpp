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
            int z = 49 + i;

            map_.setZomPos(randomX, randomY, z);
            ZombPosX.push_back(randomX);
            ZombPosY.push_back(randomY);
        }
        else
        {
            EPosX_ = randomX;
            EPosY_ = randomY;
            int z = 49 + i;

            map_.setZomPos(randomX, randomY, z);
            ZombPosX.push_back(randomX);
            ZombPosY.push_back(randomY);
        }
    }
}

void Map::rockItem(Map &map_, int x, int y)
{
    char rockItems[] = {'h', 'p', '^', 'v', '<', '>', ' ', ' ', ' ', ' ', ' ', ' '};
    int noOfItems = 12;
    itemsNo = rand() % noOfItems;
    char replacedItem = rockItems[itemsNo];
    map_.setObject(x, y, replacedItem);
}

void Map::rockEffect()
{
    std::cout << "\n\nAlien hit rock!" << std::endl;
    if (itemsNo == 0)
    {
        std::cout << "Alien discovers health pack!\n"
                  << std::endl;
    }
    else if (itemsNo == 1)
    {
        std::cout << "Alien discovers pod!\n"
                  << std::endl;
    }
    else if (itemsNo == 2)
    {
        std::cout << "Alien discovers arrow 'UP'!\n"
                  << std::endl;
    }
    else if (itemsNo == 3)
    {
        std::cout << "Alien discovers arrow 'DOWN'!\n"
                  << std::endl;
    }
    else if (itemsNo == 4)
    {
        std::cout << "Alien discovers arrow 'LEFT'!\n"
                  << std::endl;
    }
    else if (itemsNo == 5)
    {
        std::cout << "Alien discovers arrow 'RIGHT'!\n"
                  << std::endl;
    }
    else if (itemsNo == 6)
    {
        std::cout << "Alien discovers an empty space!\n"
                  << std::endl;
    }
}

void healthEffect(int AlienHp, int MaxAlienHp)
{
    if (AlienHp < MaxAlienHp)
    {
        std::cout << "\n\nAlien has miraculously gained 20 health through the power of healthpack!\n"
                  << std::endl;
        AlienHp = AlienHp + 20;
    }
    else
    {
        std::cout << "\n\nAlien is still healthy. There's no need for recover.\n"
                  << std::endl;
    }
}

void podEffect() // after implement zombies, needs to put in zombies
{
    std::cout << "\n\nAlien has encountered a pod that deals 10 damage to the nearest zombie!\n"
              << std::endl;
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

void PrintAlienMoveUp()
{
    std::cout << "\n\nAlien sees an arrow in front of it and it pulls the alien UPWARDS.\n"
    << std::endl;
}

void PrintAlienMoveDown()
{
    std::cout << "\n\nAlien sees an arrow and a force has pulled upon him DOWNWARDS.\n"
    << std::endl;
}

void PrintAlienMoveLeft()
{
    std::cout << "\n\nThe force has recognised the alien and decided LEFT was his path.\n"
    << std::endl;
}

void PrintAlienMoveRight()
{
    std::cout << "\n\nAlien went to the RIGHT because it wanted to be right.\n"
    << std::endl;
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
                case '1':
                    hitZombie = true;
                    break;
                
                case '2':
                    hitZombie = true;
                    break;

                case '3':
                    hitZombie = true;
                    break;
                
                case '4':
                    hitZombie = true;
                    break;

                case '5':
                    hitZombie = true;
                    break;
                
                case '6':
                    hitZombie = true;
                    break;

                case '7':
                    hitZombie = true;
                    break;

                case '8':
                    hitZombie = true;
                    break;
                
                case '9':
                    hitZombie = true;
                    break;

                case 'r':                               // Special Case: Rock will stop the alien and change into a random object
                    map.rockItem(map_, posX, posY - 1); // Randomises item on the rock
                    prevObj = 'r';                      // Sets prev object to r so that the arrows won't glitch out
                    hitObject = true;                   // This will make the movement code loop with the same direction unless it is true, which in this case, stops.
                    pf::ClearScreen();                  // Duh
                    map_.display();                     // Duh
                    map.CombatHUD();                    // Duh
                    map.rockEffect();                   // Rock item will reveal and print out which item discover
                    pf::Pause();                        // Duh
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
                        std::cout << "\n\nAlien sees no obstacle in front of it and walks gracefully towards it.\n"
                                  << std::endl;
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
                        PrintAlienMoveUp();
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
                        PrintAlienMoveDown();
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
                        PrintAlienMoveLeft();
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
                        PrintAlienMoveRight();
                        pf::Pause();
                        inp = "right";
                        AlienMove(map_, "right", map_.rows, map_.columns);
                        break;
                    }

                default:
                    break;
                }
            }
        } while (hitBarrier == false && hitObject == false && hitZombie == false);
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
                case '1':
                    hitZombie = true;
                    break;
                
                case '2':
                    hitZombie = true;
                    break;

                case '3':
                    hitZombie = true;
                    break;
                
                case '4':
                    hitZombie = true;
                    break;

                case '5':
                    hitZombie = true;
                    break;
                
                case '6':
                    hitZombie = true;
                    break;

                case '7':
                    hitZombie = true;
                    break;

                case '8':
                    hitZombie = true;
                    break;
                
                case '9':
                    hitZombie = true;
                    break;

                case 'r':
                    hitObject = true;
                    prevObj = 'r';
                    map.rockItem(map_, posX, posY + 1);
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    map.rockEffect();
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
                        std::cout << "\n\nAlien sees no obstacle in front of it and walks gracefully towards it.\n"
                                  << std::endl;
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
                        PrintAlienMoveUp();
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
                        PrintAlienMoveDown();
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
                        PrintAlienMoveLeft();
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
                        PrintAlienMoveRight();
                        pf::Pause();
                        AlienMove(map_, "right", map_.rows, map_.columns);
                        break;
                    }

                default:
                    break;
                }
            }
        } while (hitBarrier == false && hitObject == false && hitZombie == false);
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
                case '1':
                    hitZombie = true;
                    break;
                
                case '2':
                    hitZombie = true;
                    break;

                case '3':
                    hitZombie = true;
                    break;
                
                case '4':
                    hitZombie = true;
                    break;

                case '5':
                    hitZombie = true;
                    break;
                
                case '6':
                    hitZombie = true;
                    break;

                case '7':
                    hitZombie = true;
                    break;

                case '8':
                    hitZombie = true;
                    break;
                
                case '9':
                    hitZombie = true;
                    break;

                case 'r':
                    hitObject = true;
                    prevObj = 'r';
                    map.rockItem(map_, posX - 1, posY);
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    map.rockEffect();
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
                        std::cout << "\n\nAlien sees no obstacle in front of it and walks gracefully towards it.\n"
                                  << std::endl;
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
                        PrintAlienMoveUp();
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
                        PrintAlienMoveDown();
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
                        PrintAlienMoveLeft();
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
                        PrintAlienMoveRight();
                        pf::Pause();
                        inp = "right";
                        AlienMove(map_, "right", map_.rows, map_.columns);
                        break;
                    }

                default:
                    break;
                }
            }
        } while (hitBarrier == false && hitObject == false && hitZombie == false);
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
                case '1':
                    hitZombie = true;
                    break;
                
                case '2':
                    hitZombie = true;
                    break;

                case '3':
                    hitZombie = true;
                    break;
                
                case '4':
                    hitZombie = true;
                    break;

                case '5':
                    hitZombie = true;
                    break;
                
                case '6':
                    hitZombie = true;
                    break;

                case '7':
                    hitZombie = true;
                    break;

                case '8':
                    hitZombie = true;
                    break;
                
                case '9':
                    hitZombie = true;
                    break;                    

                case 'r':
                    hitObject = true;
                    prevObj = 'r';
                    map.rockItem(map_, posX + 1, posY);
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    map.rockEffect();
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
                        std::cout << "\n\nAlien sees no obstacle in front of it and walks gracefully towards it.\n"
                                  << std::endl;
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
                        PrintAlienMoveUp();
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
                        PrintAlienMoveDown();
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
                        PrintAlienMoveLeft();
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
                        PrintAlienMoveRight();
                        pf::Pause();
                        inp = "right";
                        AlienMove(map_, "right", map_.rows, map_.columns);
                        break;
                    }

                default:
                    break;
                }
            }
        } while (hitBarrier == false && hitObject == false && hitZombie == false);
    }
}

void Player::AlienPlacement(Map &map_)
{
}

void Enemy::upPos(Map &map_, int x)
{
    PrevX = ZombPosX[n];
    PrevY = ZombPosY[n];
    ZombPosX[n] = ZombPosX[n];
    ZombPosY[n] = ZombPosY[n] - 1;
    map_.setObject(PrevX, PrevY, ' ');
    map_.setZomPos(ZombPosX[n], ZombPosY[n], x);
}

void Enemy::downPos(Map &map_, int x)
{
    PrevX = ZombPosX[n];
    PrevY = ZombPosY[n];
    ZombPosX[n] = ZombPosX[n];
    ZombPosY[n] = ZombPosY[n] + 1;
    map_.setObject(PrevX, PrevY, ' ');
    map_.setZomPos(ZombPosX[n], ZombPosY[n], x);
}

void Enemy::leftPos(Map &map_, int x)
{
    PrevX = ZombPosX[n];
    PrevY = ZombPosY[n];
    ZombPosX[n] = ZombPosX[n] - 1;
    ZombPosY[n] = ZombPosY[n];
    map_.setObject(PrevX, PrevY, ' ');
    map_.setZomPos(ZombPosX[n], ZombPosY[n], x);
}

void Enemy::rightPos(Map &map_, int x)
{
    PrevX = ZombPosX[n];
    PrevY = ZombPosY[n];
    ZombPosX[n] = ZombPosX[n] + 1;
    ZombPosY[n] = ZombPosY[n];
    map_.setObject(PrevX, PrevY, ' ');
    map_.setZomPos(ZombPosX[n], ZombPosY[n], x);
}

void PrintZombMoveUp(int i)
{
    std::cout << "\n\nZombie " << i + 1 << " moves up.\n\n";
}

void PrintZombMoveDown(int i)
{
    std::cout << "\n\nZombie " << i + 1 << " moves down.\n\n";
}

void PrintZombMoveLeft(int i)
{
    std::cout << "\n\nZombie " << i + 1 << " moves left.\n\n";
}

void PrintZombMoveRight(int i)
{
    std::cout << "\n\nZombie " << i + 1 << " moves right.\n\n";
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
            if (ZombPosY[n] == 1)
            {
                hitBorder = true;
                ZombieMove(map_, x, y);
            }
            else
            {
                hitBorder = false;
                char nxtObj;
                if (ZombPosY[n] != 0)
                {
                    nxtObj = map_.getObject(ZombPosX[n], ZombPosY[n] - 1);
                }
                switch (nxtObj)
                {
                case '1':
                    hitAlien = true;
                    break;
                
                case '2':
                    hitAlien = true;
                    break;

                case '3':
                    hitAlien = true;
                    break;
                
                case '4':
                    hitAlien = true;
                    break;

                case '5':
                    hitAlien = true;
                    break;
                
                case '6':
                    hitAlien = true;
                    break;

                case '7':
                    hitAlien = true;
                    break;

                case '8':
                    hitAlien = true;
                    break;
                
                case '9':
                    hitAlien = true;
                    break;

                case 'A':
                    hitAlien = true;
                    randDir = rand() % 4;
                    break;

                case 'r':
                    count = count + n;
                    upPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveUp(n);
                    pf::Pause();
                    break;

                case 'p':
                    count = count + n;
                    upPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveUp(n);
                    pf::Pause();
                    break;

                case 'h':
                    count = count + n;
                    upPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveUp(n);
                    pf::Pause();
                    break;

                case ' ':
                    count = count + n;
                    upPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveUp(n);
                    pf::Pause();
                    break;

                case '^':
                    count = count + n;
                    upPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveUp(n);
                    pf::Pause();
                    break;

                case 'v':
                    count = count + n;
                    upPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveUp(n);
                    pf::Pause();
                    break;

                case '<':
                    count = count + n;
                    upPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveUp(n);
                    pf::Pause();
                    break;

                case '>':
                    count = count + n;
                    upPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveUp(n);
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
            if (ZombPosY[n] == y)
            {
                hitBorder = true;
                ZombieMove(map_, x, y);
            }
            else
            {
                hitBorder = false;
                char nxtObj;
                if (ZombPosY[n] != 0)
                {
                    nxtObj = map_.getObject(ZombPosX[n], ZombPosY[n] + 1);
                }
                switch (nxtObj)
                {
                case '1':
                    hitAlien = true;
                    break;
                
                case '2':
                    hitAlien = true;
                    break;

                case '3':
                    hitAlien = true;
                    break;
                
                case '4':
                    hitAlien = true;
                    break;

                case '5':
                    hitAlien = true;
                    break;
                
                case '6':
                    hitAlien = true;
                    break;

                case '7':
                    hitAlien = true;
                    break;

                case '8':
                    hitAlien = true;
                    break;
                
                case '9':
                    hitAlien = true;
                    break;
                
                case 'A':
                    hitAlien = true;
                    randDir = rand() % 4;
                    break;

                case 'r':
                    count = count + n;
                    downPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveDown(n);
                    pf::Pause();
                    break;

                case 'p':
                    count = count + n;
                    downPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveDown(n);
                    pf::Pause();
                    break;

                case 'h':
                    count = count + n;
                    downPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveDown(n);
                    pf::Pause();
                    break;

                case ' ':
                    count = count + n;
                    downPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveDown(n);
                    pf::Pause();
                    break;

                case '^':
                    count = count + n;
                    downPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveDown(n);
                    pf::Pause();
                    break;

                case 'v':
                    count = count + n;
                    downPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveDown(n);
                    pf::Pause();
                    break;

                case '<':
                    count = count + n;
                    downPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveDown(n);
                    pf::Pause();
                    break;

                case '>':
                    count = count + n;
                    downPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveDown(n);
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
            if (ZombPosX[n] == 1)
            {
                hitBorder = true;
                ZombieMove(map_, x, y);
            }
            else
            {
                hitBorder = false;
                char nxtObj;
                if (ZombPosY[n] != 0)
                {
                    nxtObj = map_.getObject(ZombPosX[n] - 1, ZombPosY[n]);
                }
                switch (nxtObj)
                {
                case '1':
                    hitAlien = true;
                    break;
                
                case '2':
                    hitAlien = true;
                    break;

                case '3':
                    hitAlien = true;
                    break;
                
                case '4':
                    hitAlien = true;
                    break;

                case '5':
                    hitAlien = true;
                    break;
                
                case '6':
                    hitAlien = true;
                    break;

                case '7':
                    hitAlien = true;
                    break;

                case '8':
                    hitAlien = true;
                    break;
                
                case '9':
                    hitAlien = true;
                    break;
                
                case 'A':
                    hitAlien = true;
                    randDir = rand() % 4;
                    break;

                case 'r':
                    count = count + n;
                    leftPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveLeft(n);
                    pf::Pause();
                    break;

                case 'p':
                    count = count + n;
                    leftPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveLeft(n);
                    pf::Pause();
                    break;

                case 'h':
                    count = count + n;
                    leftPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveLeft(n);
                    pf::Pause();
                    break;

                case ' ':
                    count = count + n;
                    leftPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveLeft(n);
                    pf::Pause();
                    break;

                case '^':
                    count = count + n;
                    leftPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveLeft(n);
                    pf::Pause();
                    break;

                case 'v':
                    count = count + n;
                    leftPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveLeft(n);
                    pf::Pause();
                    break;

                case '<':  
                    count = count + n;
                    leftPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveLeft(n);
                    pf::Pause();
                    break;

                case '>':
                    count = count + n;
                    leftPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveLeft(n);
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
            if (ZombPosX[n] == x)
            {
                hitBorder = true;
                ZombieMove(map_, x, y);
            }
            else
            {
                hitBorder = false;
                char nxtObj;
                if (ZombPosY[n] != 0)
                {
                    nxtObj = map_.getObject(ZombPosX[n] + 1, ZombPosY[n]);
                }
                switch (nxtObj)
                {
                case '1':
                    hitAlien = true;
                    break;
                
                case '2':
                    hitAlien = true;
                    break;

                case '3':
                    hitAlien = true;
                    break;
                
                case '4':
                    hitAlien = true;
                    break;

                case '5':
                    hitAlien = true;
                    break;
                
                case '6':
                    hitAlien = true;
                    break;

                case '7':
                    hitAlien = true;
                    break;

                case '8':
                    hitAlien = true;
                    break;
                
                case '9':
                    hitAlien = true;
                    break;

                case 'A':
                    hitAlien = true;
                    randDir = rand() % 4;
                    break;

                case 'r':
                    count = count + n;
                    rightPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveRight(n);
                    pf::Pause();
                    break;

                case 'p':
                    count = count + n;
                    rightPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveRight(n);
                    pf::Pause();
                    break;

                case 'h':
                    count = count + n;
                    rightPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveRight(n);
                    pf::Pause();
                    break;

                case ' ':
                    count = count + n;
                    rightPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveRight(n);
                    pf::Pause();
                    break;

                case '^':
                    count = count + n;
                    rightPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveRight(n);
                    pf::Pause();
                    break;

                case 'v':
                    count = count + n;
                    rightPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveRight(n);
                    pf::Pause();
                    break;

                case '<':
                    count = count + n;
                    rightPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveRight(n);
                    pf::Pause();
                    break;

                case '>':
                    count = count + n;
                    rightPos(map_, count);
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    map.CombatHUD();
                    PrintZombMoveRight(n);
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
