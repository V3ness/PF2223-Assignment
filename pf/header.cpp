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
    posX = posX_;
    posY = posY_;

    map_.setObject(middleX, middleY, AlienSymbol);
}

void rockItem(Map &map_, int x, int y)
{
    char rockItems[] = {'h', 'p', '^', 'v', '<', '>', ' '};
    int noOfItems = 7;
    int itemsNo = rand() % noOfItems;
    char replacedItem = rockItems[itemsNo];
    map_.setObject(x, y, replacedItem);
    std::cout << replacedItem;
}

// void Player::AlienMove(Map &map_, std::string inp, int x, int y)
// {
//     if (inp == "Up" || inp == "up" || inp == "UP")
//     {
//             if (newPosY_ == 1)
//             {
//                 hitBarrier = true;
//             }
//             else
//             {
//                 hitBarrier = false;
//                 if (map_.getObject(posX_, posY_ - 1) != ' ')
//                 {
//                     hitObject = true;
//                     std::cout << "Alien stumbles upon a rock.\n" << "Alien finds a ";
//                     rockItem(map_, posX_, posY_ - 1);
//                     std::cout << " underneath the rock." << std::endl;
//                 }
//                 else
//                 {
//                     hitObject = false;
//                     newPosX_ = posX_;
//                     newPosY_ = posY_ - 1;
//                     std::cout << "Alien finds an empty space.\n" << "It keeps on going." << std::endl;
//                     pf::Pause();
//                     // pf::ClearScreen();
//                 }
//         }
//         if (inp == "down" || inp == "Down" || inp == "DOWN")
//         {
//             if (newPosY_ == y)
//             {
//                 hitBarrier = true;
//             }
//             else
//             {
//                 hitBarrier = false;
//                 if (map_.getObject(posX_, posY_ + 1) != ' ')
//                 {
//                     hitObject = true;
//                 }
//                 else
//                 {
//                     hitObject = false;
//                     newPosX_ = posX_;
//                     newPosY_ = posY_ + 1;
//                     std::cout << "Alien finds an empty space.\n" << "It keeps on going." << std::endl;
//                     pf::Pause();
//                     // pf::ClearScreen();
//                 }
//             }
//         }
//         if (inp == "Left" || inp == "left" || inp == "LEFT")
//         {
//             if (newPosX_ == 1)
//             {
//                 hitBarrier = true;
//             }
//             else
//             {
//                 hitBarrier = false;
//                 if (map_.getObject(posX_ - 1, posY_) != ' ')
//                 {
//                     hitObject = true;
//                 }
//                 else
//                 {
//                     hitObject = false;
//                     newPosX_ = posX_ - 1;
//                     newPosY_ = posY_;
//                     std::cout << "Alien finds an empty space.\n" << "It keeps on going." << std::endl;
//                     pf::Pause();
//                     // pf::ClearScreen();
//                 }
//             }
//         }
//         if (inp == "Right" || inp == "right" || inp == "RIGHT")
//         {
//             if (newPosX_ == x)
//             {
//                 hitBarrier = true;
//             }
//             else
//             {
//                 hitBarrier = false;
//                 if (map_.getObject(posX_ + 1, posY_) != ' ')
//                 {
//                     hitObject = true;
//                     //Randomise the rock objects
//                 }
//                 else
//                 {
//                     hitObject = false;
//                     newPosX_ = posX_ + 1;
//                     newPosY_ = posY_;
//                     std::cout << "Alien finds an empty space.\n" << "It keeps on going." << std::endl;
//                     pf::Pause();
//                     // pf::ClearScreen();
//                 }
//             }
//         } 
//     } 
// }

void healthEffect(int AlienHp)
{
    std::cout << "Your Alien has miraculously gained 20 health through the power of healthpack!" << std::endl;
    AlienHp = AlienHp + 20;
    if (AlienHp > 100)
    {
        AlienHp = 100;
    }
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
    if (inp == "up" || inp == "UP" || inp == "Up")
    {
        do
        {
            if (posY == 1) //CHANGE THIS TO Y
            {
                hitBarrier = true;
            }
            else
            {
                hitBarrier = false;
                char objectOnTop;
                if (posY != 0)
                {
                    objectOnTop = map_.getObject(posX, posY - 1);
                }
                switch (objectOnTop)
                {
                case 'h':
                    healthEffect(AlienHp);
                    if (hitBarrier == false)
                    {
                        upPos(map_);
                    } //print out screen and clear it
                    pf::ClearScreen();
                    map_.display();
                    pf::Pause();
                    break;

                case ' ':
                    if (hitBarrier == false)
                    {
                        upPos(map_);
                    }
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nAlien sees no obstacle in front of it and walks gracefully towards it." << std::endl;
                    pf::Pause();
                    break;

                case '^':
                    if (hitBarrier == false)
                    {
                        upPos(map_);
                    }
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nAlien sees an arrow in front of it and it pulls the alien upwards." << std::endl;
                    pf::Pause();
                    break;
                
                case 'v':
                    if (hitBarrier == false)
                    {
                        upPos(map_);
                    }
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nAlien sees an arrow and a force has pulled upon him downwards" << std::endl;
                    pf::Pause();
                    inp = "down";
                    break;

                    //continue
                case '<':
                    if (hitBarrier == false)
                    {
                        upPos(map_);
                    }
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nThe force has recognised the alien and decided left was his path." << std::endl;
                    pf::Pause();
                    inp = "left";
                    break;

                case '>':
                    if (hitBarrier == false)
                    {
                        upPos(map_);
                    }
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nAlien went to the right because it wanted to be right." << std::endl;
                    pf::Pause();
                    inp = "right";
                    break;

                default:
                    break;
                }
            }
        }
        while (hitBarrier == false && hitObject == false);
    }
    if (inp == "down" || inp == "DOWN" || inp == "Down")
    {
        do
        {
            if (posY == y)
            {
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
                case 'h':
                    healthEffect(AlienHp);
                    if (hitBarrier == false)
                    {
                        downPos(map_);
                    }
                    pf::ClearScreen();
                    map_.display();
                    pf::Pause();
                    break;

                case ' ':
                    if (hitBarrier == false)
                    {
                        downPos(map_);
                    }
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nAlien sees no obstacle in front of it and walks gracefully towards it." << std::endl;
                    pf::Pause();
                    break;

                case '^':
                    if (hitBarrier == false)
                    {
                        downPos(map_);
                    }
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nAlien sees an arrow in front of it and it pulls the alien upwards." << std::endl;
                    pf::Pause();
                    inp = "up";
                    break;
                
                case 'v':
                    if (hitBarrier == false)
                    {
                        downPos(map_);
                    }
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nAlien sees an arrow and a force has pulled upon him downwards" << std::endl;
                    pf::Pause();
                    break;

                    //continue
                case '<':
                    if (hitBarrier == false)
                    {
                        downPos(map_);
                    }
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nThe force has recognised the alien and decided left was his path." << std::endl;
                    pf::Pause();
                    inp = "left";
                    break;

                case '>':
                    if (hitBarrier == false)
                    {
                        downPos(map_);
                    }
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nAlien went to the right because it wanted to be right." << std::endl;
                    pf::Pause();
                    inp = "right";
                    break;

                default:
                    break;
                }
            }
        }
        while (hitBarrier == false && hitObject == false);

    }
    if (inp == "left" || inp == "LEFT" || inp == "Left")
    {
        do
        {
            if (posX == 1)
            {
                hitBarrier = true;
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
                case 'h':
                    healthEffect(AlienHp);
                    if (hitBarrier == false)
                    {
                        leftPos(map_);
                    }
                    pf::ClearScreen();
                    map_.display();
                    pf::Pause();
                    break;

                case ' ':
                    if (hitBarrier == false)
                    {
                        leftPos(map_);
                    }
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nAlien sees no obstacle in front of it and walks gracefully towards it." << std::endl;
                    pf::Pause();
                    break;

                case '^':
                    if (hitBarrier == false)
                    {
                        leftPos(map_);
                    }
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nAlien sees an arrow in front of it and it pulls the alien upwards." << std::endl;
                    pf::Pause();
                    inp = "up";
                    break;
                
                case 'v':
                    if (hitBarrier == false)
                    {
                        leftPos(map_);
                    }
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nAlien sees an arrow and a force has pulled upon him downwards" << std::endl;
                    pf::Pause();
                    inp = "down";
                    break;

                case '<':
                    if (hitBarrier == false)
                    {
                        leftPos(map_);
                    }                
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nThe force has recognised the alien and decided left was his path." << std::endl;
                    pf::Pause();
                    break;

                case '>':
                    if (hitBarrier == false)
                    {
                        leftPos(map_);
                    }
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nAlien went to the right because it wanted to be right." << std::endl;
                    hitObject = true;
                    pf::Pause();
                    inp = "right";
                    break;

                default:
                    break;
                }
            }
        }
        while (hitBarrier == false && hitObject == false);
    }
    if (inp == "right" || inp == "RIGHT" || inp == "Right")
    {
        do
        {
            if (posX == x)
            {
                hitBarrier = true;
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
                case 'h':
                    healthEffect(AlienHp);
                    if (hitBarrier == false)
                    {
                        rightPos(map_);
                    }
                    pf::ClearScreen();
                    map_.display();
                    pf::Pause();
                    break;

                case ' ':
                    if (hitBarrier == false)
                    {
                        rightPos(map_);
                    }
                    pf::ClearScreen();
                    map_.display();
                    hitObject = false;
                    std::cout << "\nAlien sees no obstacle in front of it and walks gracefully towards it." << std::endl;
                    pf::Pause();
                    break;

                case '^':
                    if (hitBarrier == false)
                    {
                        rightPos(map_);
                    }
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nAlien sees an arrow in front of it and it pulls the alien upwards." << std::endl;
                    hitObject = true;
                    pf::Pause();
                    inp = "up";
                    break;
                
                case 'v':
                    if (hitBarrier == false)
                    {
                        rightPos(map_);
                    }
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nAlien sees an arrow and a force has pulled upon him downwards" << std::endl;
                    pf::Pause();
                    inp = "down";
                    break;

                case '<':
                    if (hitBarrier == false)
                    {
                        rightPos(map_);
                    }
                    hitObject = true;
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nThe force has recognised the alien and decided left was his path." << std::endl;
                    pf::Pause();
                    inp = "right";             
                    break;

                case '>':
                    if (hitBarrier == false)
                    {
                        rightPos(map_);
                    }
                    pf::ClearScreen();
                    map_.display();
                    std::cout << "\nAlien went to the right because it wanted to be right." << std::endl;
                    pf::Pause();
                    break;

                default:
                    break;
                }
            }
        }
        while (hitBarrier == false && hitObject == false);
    }
}


void Player::AlienPlacement(Map &map_)
{

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
//     pf::ClearScreen();
//     m1.display();
//     std::cout << "Which Direction? ";
//     std::string userInput;
//     std::cin >> userInput;
//     do
//     {
//         alien.AlienMove(m1, userInput, irows, icolumns);
//         alien.AlienPlacement(m1);
//         pf::ClearScreen();
//         m1.display();
//         if (alien.hitBarrier == true)
//         {
//             std::cout << "\nAlien hit the barrier!" << std::endl;
//             pf::Pause();
//         }
//     }
//     while (alien.hitBarrier == false);
//     alien.hitObject = false;
//     std::cout << "Which Direction? ";
//     std::cin >> userInput;
//     do
//     {
//         alien.AlienMove(m1, userInput, irows, icolumns);
//         alien.AlienPlacement(m1);
//         pf::ClearScreen();
//         m1.display();
//         if (alien.hitBarrier == true)
//         {
//             std::cout << "\nAlien hit the barrier!" << std::endl;
//             pf::Pause();
//         }
//     }
//     while (alien.hitBarrier == false);
//     std::cout << "Which Direction? ";
//     std::cin >> userInput;
//     do
//     {
//         alien.AlienMove(m1, userInput, irows, icolumns);
//         alien.AlienPlacement(m1);
//         pf::ClearScreen();
//         m1.display();
//         if (alien.hitBarrier == true)
//         {
//             std::cout << "\nAlien hit the barrier!" << std::endl;
//             pf::Pause();
//         }
//     }
//     while (alien.hitBarrier == false);
// }
