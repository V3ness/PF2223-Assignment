#include "header.h"
#include <cstdlib>
#include <iostream>
#include <ctime>

void Map::init(int rows, int columns)
{
    rows_ = rows;
    columns_ = columns;
    char randobjects[] = {' ', ' ', ' ', ' ', ' ', ' ', 'h', 'v', '^', '<', '>', 'p'};
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
    std:: cout << ".: Alien vs Zombie :." << std::endl;

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
        std::cout << "+" << "-";
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

char Map::getObject(int x, int y) const
{
    return map_[y - 1][x - 1];
}

void Map::setObject(int x, int y, char ch)
{
    map_[y - 1][x - 1] = ch;
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

void Player::InitialLanding(Map &map_, float x, float y)
{
    float middleX, middleY;
    //Get middle positions based on the size of map
    middleX = ceil(x / 2);
    middleY = ceil(y / 2);
    posX_ = middleX;
    posY_ = middleY;

    map_.setObject(middleX, middleY, AlienSymbol);
}

void Player::AlienMove(Map &map_, std::string inp, int x, int y)
{
        if (inp == "Up" || inp == "up" || inp == "UP")
        {
            if (newPosY_ == 1)
            {
                hitBarrier = true;
            }
            else
            {
                hitBarrier = false;
                if (map_.getObject(posX_, posY_ - 1) == 'r')
                {
                    hitObject = true;
                }
                if (map_.getObject(posX_, posY_ - 1) == '^')
                {
                    hitObject = false;
                    newPosX_ = posX_;
                    newPosY_ = posY_ - 1;
                    inp = "up";
                    do
                    {
                        AlienMove(map_, inp, x, y);
                        AlienPlacement(map_);
                        pf::ClearScreen();
                        map_.display();
                        if (hitBarrier == true)
                        {
                            std::cout << "Alien hit the barrier!" << std::endl;
                            pf::Pause();
                        }
                        if (hitObject == true)
                        {
                            std::cout << "Alien hit an object!" << std::endl;
                            pf::Pause();
                        }
                    } while (hitBarrier == false && hitObject == false);
                }
                if (map_.getObject(posX_, posY_ - 1) == 'v')
                {
                    hitObject = false;
                    newPosX_ = posX_;
                    newPosY_ = posY_ - 1;
                    inp = "down";
                    do
                    {
                        AlienMove(map_, inp, x, y);
                        AlienPlacement(map_);
                        pf::ClearScreen();
                        map_.display();
                        if (hitBarrier == true)
                        {
                            std::cout << "Alien hit the barrier!" << std::endl;
                            pf::Pause();
                        }
                        if (hitObject == true)
                        {
                            std::cout << "Alien hit an object!" << std::endl;
                            pf::Pause();
                        }
                    } while (hitBarrier == false && hitObject == false);
                }
                if (map_.getObject(posX_, posY_ - 1) == '<')
                {
                    hitObject = false;
                    newPosX_ = posX_;
                    newPosY_ = posY_ - 1;
                    inp = "left";
                    do
                    {
                        AlienMove(map_, inp, x, y);
                        AlienPlacement(map_);
                        pf::ClearScreen();
                        map_.display();
                        if (hitBarrier == true)
                        {
                            std::cout << "Alien hit the barrier!" << std::endl;
                            pf::Pause();
                        }
                        if (hitObject == true)
                        {
                            std::cout << "Alien hit an object!" << std::endl;
                            pf::Pause();
                        }
                    } while (hitBarrier == false && hitObject == false);
                }
                if (map_.getObject(posX_, posY_ - 1) == '>')
                {
                    hitObject = false;
                    newPosX_ = posX_;
                    newPosY_ = posY_ - 1;
                    inp = "right";
                    do
                    {
                        AlienMove(map_, inp, x, y);
                        AlienPlacement(map_);
                        pf::ClearScreen();
                        map_.display();
                        if (hitBarrier == true)
                        {
                            std::cout << "Alien hit the barrier!" << std::endl;
                            pf::Pause();
                        }
                        if (hitObject == true)
                        {
                            std::cout << "Alien hit an object!" << std::endl;
                            pf::Pause();
                        }
                    } while (hitBarrier == false && hitObject == false);
                }
                // //
                else
                {
                    hitObject = false;
                    newPosX_ = posX_;
                    newPosY_ = posY_ - 1;
                }
            }
        }
        if (inp == "down" || inp == "Down" || inp == "DOWN")
        {
            if (newPosY_ == y)
            {
                hitBarrier = true;
            }
            else
            {
                hitBarrier = false;
                if (map_.getObject(posX_, posY_ + 1) == 'r')
                {
                    hitObject = true;
                }
                if (map_.getObject(posX_, posY_ + 1) == '^')
                {
                    hitObject = false;
                    newPosX_ = posX_;
                    newPosY_ = posY_ + 1;
                    inp = "up";
                    do
                    {
                        AlienMove(map_, inp, x, y);
                        AlienPlacement(map_);
                        pf::ClearScreen();
                        map_.display();
                        if (hitBarrier == true)
                        {
                            std::cout << "Alien hit the barrier!" << std::endl;
                            pf::Pause();
                        }
                        if (hitObject == true)
                        {
                            std::cout << "Alien hit an object!" << std::endl;
                            pf::Pause();
                        }
                    } while (hitBarrier == false && hitObject == false);
                }
                if (map_.getObject(posX_, posY_ + 1) == 'v')
                {
                    hitObject = false;
                    newPosX_ = posX_;
                    newPosY_ = posY_ + 1;
                    inp = "down";
                    do
                    {
                        AlienMove(map_, inp, x, y);
                        AlienPlacement(map_);
                        pf::ClearScreen();
                        map_.display();
                        if (hitBarrier == true)
                        {
                            std::cout << "Alien hit the barrier!" << std::endl;
                            pf::Pause();
                        }
                        if (hitObject == true)
                        {
                            std::cout << "Alien hit an object!" << std::endl;
                            pf::Pause();
                        }
                    } while (hitBarrier == false && hitObject == false);
                }
                if (map_.getObject(posX_, posY_ + 1) == '<')
                {
                    hitObject = false;
                    newPosX_ = posX_;
                    newPosY_ = posY_ + 1;
                    inp = "left";
                    do
                    {
                        AlienMove(map_, inp, x, y);
                        AlienPlacement(map_);
                        pf::ClearScreen();
                        map_.display();
                        if (hitBarrier == true)
                        {
                            std::cout << "Alien hit the barrier!" << std::endl;
                            pf::Pause();
                        }
                        if (hitObject == true)
                        {
                            std::cout << "Alien hit an object!" << std::endl;
                            pf::Pause();
                        }
                    } while (hitBarrier == false && hitObject == false);
                }
                if (map_.getObject(posX_, posY_ + 1) == '>')
                {
                    hitObject = false;
                    newPosX_ = posX_;
                    newPosY_ = posY_ + 1;
                    inp = "right";
                    do
                    {
                        AlienMove(map_, inp, x, y);
                        AlienPlacement(map_);
                        pf::ClearScreen();
                        map_.display();
                        if (hitBarrier == true)
                        {
                            std::cout << "Alien hit the barrier!" << std::endl;
                            pf::Pause();
                        }
                        if (hitObject == true)
                        {
                            std::cout << "Alien hit an object!" << std::endl;
                            pf::Pause();
                        }
                    } while (hitBarrier == false && hitObject == false);
                }
                else
                {
                    hitObject = false;
                    newPosX_ = posX_;
                    newPosY_ = posY_ + 1;
                }
            }
        }
        if (inp == "Left" || inp == "left" || inp == "LEFT")
        {
            if (newPosX_ == 1)
            {
                hitBarrier = true;
            }
            else
            {
                hitBarrier = false;
                if (map_.getObject(posX_ - 1, posY_) == 'r')
                {
                    hitObject = true;
                }
                if (map_.getObject(posX_ - 1, posY_) == '^')
                {
                    hitObject = false;
                    newPosX_ = posX_-1;
                    newPosY_ = posY_;
                    AlienPlacement(map_);
                    inp = "up";
                    do
                    {
                        AlienMove(map_, inp, x, y);
                        AlienPlacement(map_);
                        pf::ClearScreen();
                        map_.display();
                        if (hitBarrier == true)
                        {
                            std::cout << "Alien hit the barrier!" << std::endl;
                            pf::Pause();
                        }
                        if (hitObject == true)
                        {
                            std::cout << "Alien hit an object!" << std::endl;
                            pf::Pause();
                        }
                    } while (hitBarrier == false && hitObject == false);
                }
                if (map_.getObject(posX_ - 1, posY_) == 'v')
                {
                    hitObject = false;
                    newPosX_ = posX_-1;
                    newPosY_ = posY_;
                    AlienPlacement(map_);
                    inp = "down";
                    do
                    {
                        AlienMove(map_, inp, x, y);
                        AlienPlacement(map_);
                        pf::ClearScreen();
                        map_.display();
                        if (hitBarrier == true)
                        {
                            std::cout << "Alien hit the barrier!" << std::endl;
                            pf::Pause();
                        }
                        if (hitObject == true)
                        {
                            std::cout << "Alien hit an object!" << std::endl;
                            pf::Pause();
                        }
                    } while (hitBarrier == false && hitObject == false);
                }
                if (map_.getObject(posX_ - 1, posY_) == '<')
                {
                    hitObject = false;
                    newPosX_ = posX_-1;
                    newPosY_ = posY_;
                    AlienPlacement(map_);
                    inp = "left";
                    do
                    {
                        AlienMove(map_, inp, x, y);
                        AlienPlacement(map_);
                        pf::ClearScreen();
                        map_.display();
                        if (hitBarrier == true)
                        {
                            std::cout << "Alien hit the barrier!" << std::endl;
                            pf::Pause();
                        }
                        if (hitObject == true)
                        {
                            std::cout << "Alien hit an object!" << std::endl;
                            pf::Pause();
                        }
                    } while (hitBarrier == false && hitObject == false);
                }
                if (map_.getObject(posX_ - 1, posY_) == '>')
                {
                    hitObject = false;
                    newPosX_ = posX_-1;
                    newPosY_ = posY_;
                    AlienPlacement(map_);
                    inp = "right";
                    do
                    {
                        AlienMove(map_, inp, x, y);
                        AlienPlacement(map_);
                        pf::ClearScreen();
                        map_.display();
                        if (hitBarrier == true)
                        {
                            std::cout << "Alien hit the barrier!" << std::endl;
                            pf::Pause();
                        }
                        if (hitObject == true)
                        {
                            std::cout << "Alien hit an object!" << std::endl;
                            pf::Pause();
                        }
                    } while (hitBarrier == false && hitObject == false);
                }
                else
                {
                    hitObject = false;
                    newPosX_ = posX_ - 1;
                    newPosY_ = posY_;
                }
            }
        }
        if (inp == "Right" || inp == "right" || inp == "RIGHT")
        {
            if (newPosX_ == x)
            {
                hitBarrier = true;
            }
            else
            {
                hitBarrier = false;
                if (map_.getObject(posX_ + 1, posY_) == 'r')
                {
                    hitObject = true;
                }
                else
                {
                    hitObject = false;
                    newPosX_ = posX_ + 1;
                    newPosY_ = posY_;
                }
            }
        }    
}

void Player::AlienPlacement(Map &map_)
{
    if (hitBarrier == false && hitObject == false)
    {
        map_.setObject(newPosX_, newPosY_, AlienSymbol);
        map_.setObject(posX_, posY_, '.');
        posX_ = newPosX_;
        posY_ = newPosY_;
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
        std::cout << '\n' << "  Zombie " << i + 1 << " : Life " << ZombieHp << ", Attack  " << ZombieAtk << ", Range " << ZombieRange;
    }
}

// int main()
// {
//     srand(1);
//     Map m1;
//     Player alien;
//     int irows, icolumns;
//     std::cout << "Enter Rows: ";
//     std::cin >> icolumns; 
//     std::cout << "Enter Columns: ";
//     std::cin >> irows;
//     m1.init(irows, icolumns);
//     alien.InitialLanding(m1, irows, icolumns);
//     // pf::ClearScreen();
//     m1.display();
//     alien.newPosX_ = alien.posX_;
//     alien.newPosY_ = alien.posY_;
//     std::cout << "Which Direction? ";
//     std::string userInput;
//     std::cin >> userInput;
//     do
//     {
//         alien.AlienMove(m1, userInput, irows, icolumns);
//         alien.AlienPlacement(m1);
//         // pf::ClearScreen();
//         m1.display();
//         if (alien.hitBarrier == true)
//         {
//             std::cout << "Alien hit the barrier!" << std::endl;
//             pf::Pause();
//         }
//         if (alien.hitObject == true)
//         {
//             std::cout << "Alien hit an object!" << std::endl;
//             pf::Pause();
//         }
//     } while (alien.hitBarrier == false && alien.hitObject == false);
    
//     std::cout << "Which Direction? ";
//     std::cin >> userInput;
//     do
//     {
//         alien.AlienMove(m1, userInput, irows, icolumns);
//         alien.AlienPlacement(m1);
//         // pf::ClearScreen();
//         m1.display();
//         if (alien.hitBarrier == true)
//         {
//             std::cout << "Alien hit the barrier!" << std::endl;
//             pf::Pause();
//         }
//         if (alien.hitObject == true)
//         {
//             std::cout << "Alien hit an object!" << std::endl;
//             pf::Pause();
//         }
//     } while (alien.hitBarrier == false && alien.hitObject == false);
    
// }