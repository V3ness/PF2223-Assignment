// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT1L
// Names: ANG KHAI PIN | LESTER LIEW JUN MIN |
// IDs: 1211101248 | 1221302721 |
// Emails: 1211101248@student.mmu.edu.my | 1221302721@student.mmu.edu.my |
// Phones: 011-57725120 | 012-9156393 |
// *********************************************************

#include "pf/header.h"
#include <algorithm>

char GSchoice;
bool GameOver = false;
int Rows = 9, Columns = 9;

void Combat();

std::vector<std::vector<char>> board; // Make the board a sort of matrix

Player Alien;
Enemy Zombie;
Map map;

template <typename T> // Overloading Operator "<<" to let std::cout print out vector. (MUST NOT TOUCH)
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    for (size_t i = v.size() - 1; i < v.size(); i++)
    {
        os << v[i];
    }
    return os;
}

void Pause()
{
    pf::Pause();
    std::cout << std::endl;
}

void ClearScreen()
{
    pf::ClearScreen();
    std::cout << std::endl;
}

void ChangeZombieSettings()
{
    Sleep(500);
    std::cout << "\nZombie Settings\n";
    std::cout << "-----------------\n";
    std::cout << "Enter number of zombies: ";
    std::cin >> Zombie.ZombieCount;
    if (Zombie.ZombieCount >= 10)
    {
        std::cout << "Number of zombies cannot exceed 9.\n";
        Sleep(3000);
        ClearScreen();
        ChangeZombieSettings();
    }
    else
    {
        std::cout << "\nSettings Updated.\n";
        Pause();
    }
}

void ChangeGameSettings()
{
    std::cout << "Board Settings\n";
    std::cout << "-----------------\n";
    std::cout << "Enter Rows    : ";
    std::cin >> Columns;
    std::cout << "Enter Columns : ";
    std::cin >> Rows;
    if (Rows % 2 == 0 || Columns % 2 == 0)
    {
        std::cout << "Please ensure that Rows and Columns are odd numbers.\n";
        Sleep(4000);
        ClearScreen();
        ChangeGameSettings();
    }
    else
    {
        ChangeZombieSettings();
    }
}

void GameSettings()
{
    std::cout << "Board Rows    : " << Rows << '\n';
    std::cout << "Board Columns : " << Columns << '\n';
    std::cout << "Zombie Count  : " << Zombie.ZombieCount;
    std::cout << "\nDo you wish to change the game settings (y/n)? => ";
    std::cin >> GSchoice;
    if (GSchoice == 'y' || GSchoice == 'Y')
    {
        ClearScreen();
        ChangeGameSettings();
    }
}

void ShowGameSettings()
{
    ClearScreen();
    std::cout << "Default Game Settings\n";
    std::cout << "-------------------------\n";
    GameSettings();
}

void makeBoard()
{
    // Initialize the gameboard with random objects and alien in middle position
    // Need to add zombie in the gameboard
    map.init(Rows, Columns);
    Zombie.ZombDist = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    Alien.InitialLanding(map, Rows, Columns);
    Zombie.ZombieLanding(map, Rows, Columns);
    pf::ClearScreen();
    map.display();
}

void Map::CombatHUD()
{
    Alien.AlienCreation(Zombie.ZombieCount);
    Zombie.ZombieCreation();
    if (Alien.alienTurn == true)
    {
        std::cout << "\n->Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
        for (int i = 0; i < Zombie.ZombieCount; i++)
        {
            std::cout << '\n'
                      << "  Zombie " << i + 1 << " : Health " << Zombie.ZombHpVec[i] << ", Attack  " << Zombie.ZombAtkVec[i] << ", Range " << Zombie.ZombRngVec[i];
        }
    }
    else
    {
        switch (Zombie.n)
        {
        case 0:
            std::cout << "\n  Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
            std::cout << '\n'
            << "->Zombie " << 1 << " : Health " << Zombie.ZombHpVec[0] << ", Attack  " << Zombie.ZombAtkVec[0] << ", Range " << Zombie.ZombRngVec[0];
            for (int i = 1; i < Zombie.ZombieCount; i++)
            {
                std::cout << '\n'
                        << "  Zombie " << i + 1 << " : Health " << Zombie.ZombHpVec[i] << ", Attack  " << Zombie.ZombAtkVec[i] << ", Range " << Zombie.ZombRngVec[i];
            }
            break;
        
        case 1:
            std::cout << "\n  Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
            std::cout << '\n'
            << "  Zombie " << 1 << " : Health " << Zombie.ZombHpVec[0] << ", Attack  " << Zombie.ZombAtkVec[0] << ", Range " << Zombie.ZombRngVec[0];
            std::cout << '\n'
            << "->Zombie " << 2 << " : Health " << Zombie.ZombHpVec[1] << ", Attack  " << Zombie.ZombAtkVec[1] << ", Range " << Zombie.ZombRngVec[1];
            for (int i = 2; i < Zombie.ZombieCount; i++)
            {
                std::cout << '\n'
                          << "  Zombie " << i + 1 << " : Health " << Zombie.ZombHpVec[i] << ", Attack  " << Zombie.ZombAtkVec[i] << ", Range " << Zombie.ZombRngVec[i];
            }
            break;

        case 2:
            std::cout << "\n  Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
            std::cout << '\n'
            << "  Zombie " << 1 << " : Health " << Zombie.ZombHpVec[0] << ", Attack  " << Zombie.ZombAtkVec[0] << ", Range " << Zombie.ZombRngVec[0];
            std::cout << '\n'
            << "  Zombie " << 2 << " : Health " << Zombie.ZombHpVec[1] << ", Attack  " << Zombie.ZombAtkVec[1] << ", Range " << Zombie.ZombRngVec[1];
            std::cout << '\n'
            << "->Zombie " << 3 << " : Health " << Zombie.ZombHpVec[2] << ", Attack  " << Zombie.ZombAtkVec[2] << ", Range " << Zombie.ZombRngVec[2];
            for (int i = 3; i < Zombie.ZombieCount; i++)
            {
                std::cout << '\n'
                          << "  Zombie " << i + 1 << " : Health " << Zombie.ZombHpVec[i] << ", Attack  " << Zombie.ZombAtkVec[i] << ", Range " << Zombie.ZombRngVec[i];
            }
            break;

        case 3:
            std::cout << "\n  Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
            for (int i = 0; i < 3; i++)
            {
                std::cout << '\n'
                          << "  Zombie " << i + 1 << " : Health " << Zombie.ZombHpVec[i] << ", Attack  " << Zombie.ZombAtkVec[i] << ", Range " << Zombie.ZombRngVec[i];
            }
            std::cout << '\n'
            << "->Zombie " << 4 << " : Health " << Zombie.ZombHpVec[3] << ", Attack  " << Zombie.ZombAtkVec[3] << ", Range " << Zombie.ZombRngVec[3];
            for (int i = 4; i < Zombie.ZombieCount; i++)
            {
                std::cout << '\n'
                          << "  Zombie " << i + 1 << " : Health " << Zombie.ZombHpVec[i] << ", Attack  " << Zombie.ZombAtkVec[i] << ", Range " << Zombie.ZombRngVec[i];
            }
            break;

        case 4:
            std::cout << "\n  Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
            for (int i = 0; i < 4; i++)
            {
                std::cout << '\n'
                          << "  Zombie " << i + 1 << " : Health " << Zombie.ZombHpVec[i] << ", Attack  " << Zombie.ZombAtkVec[i] << ", Range " << Zombie.ZombRngVec[i];
            }
            std::cout << '\n'
            << "->Zombie " << 5 << " : Health " << Zombie.ZombHpVec[4] << ", Attack  " << Zombie.ZombAtkVec[4] << ", Range " << Zombie.ZombRngVec[4];
            for (int i = 5; i < Zombie.ZombieCount; i++)
            {
                std::cout << '\n'
                          << "  Zombie " << i + 1 << " : Health " << Zombie.ZombHpVec[i] << ", Attack  " << Zombie.ZombAtkVec[i] << ", Range " << Zombie.ZombRngVec[i];
            }
            break;

        case 5:
            std::cout << "\n  Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
            for (int i = 0; i < 5; i++)
            {
                std::cout << '\n'
                          << "  Zombie " << i + 1 << " : Health " << Zombie.ZombHpVec[i] << ", Attack  " << Zombie.ZombAtkVec[i] << ", Range " << Zombie.ZombRngVec[i];
            }
            std::cout << '\n'
            << "->Zombie " << 6 << " : Health " << Zombie.ZombHpVec[5] << ", Attack  " << Zombie.ZombAtkVec[5] << ", Range " << Zombie.ZombRngVec[5];
            for (int i = 6; i < Zombie.ZombieCount; i++)
            {
                std::cout << '\n'
                          << "  Zombie " << i + 1 << " : Health " << Zombie.ZombHpVec[i] << ", Attack  " << Zombie.ZombAtkVec[i] << ", Range " << Zombie.ZombRngVec[i];
            }
            break;

        case 6:
            std::cout << "\n  Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
            for (int i = 0; i < 6; i++)
            {
                std::cout << '\n'
                          << "  Zombie " << i + 1 << " : Health " << Zombie.ZombHpVec[i] << ", Attack  " << Zombie.ZombAtkVec[i] << ", Range " << Zombie.ZombRngVec[i];
            }
            std::cout << '\n'
            << "->Zombie " << 7 << " : Health " << Zombie.ZombHpVec[6] << ", Attack  " << Zombie.ZombAtkVec[6] << ", Range " << Zombie.ZombRngVec[6];
            for (int i = 7; i < Zombie.ZombieCount; i++)
            {
                std::cout << '\n'
                          << "  Zombie " << i + 1 << " : Health " << Zombie.ZombHpVec[i] << ", Attack  " << Zombie.ZombAtkVec[i] << ", Range " << Zombie.ZombRngVec[i];
            }
            break;

        case 7:
            std::cout << "\n  Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
            for (int i = 0; i < 7; i++)
            {
                std::cout << '\n'
                          << "  Zombie " << i + 1 << " : Health " << Zombie.ZombHpVec[i] << ", Attack  " << Zombie.ZombAtkVec[i] << ", Range " << Zombie.ZombRngVec[i];
            }
            std::cout << '\n'
            << "->Zombie " << 8 << " : Health " << Zombie.ZombHpVec[7] << ", Attack  " << Zombie.ZombAtkVec[7] << ", Range " << Zombie.ZombRngVec[7];
            for (int i = 8; i < Zombie.ZombieCount; i++)
            {
                std::cout << '\n'
                          << "  Zombie " << i + 1 << " : Health " << Zombie.ZombHpVec[i] << ", Attack  " << Zombie.ZombAtkVec[i] << ", Range " << Zombie.ZombRngVec[i];
            }
            break;

        case 8:
            std::cout << "\n  Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
            for (int i = 0; i < 8; i++)
            {
                std::cout << '\n'
                          << "  Zombie " << i + 1 << " : Health " << Zombie.ZombHpVec[i] << ", Attack  " << Zombie.ZombAtkVec[i] << ", Range " << Zombie.ZombRngVec[i];
            }
            std::cout << '\n'
            << "->Zombie " << 9 << " : Health " << Zombie.ZombHpVec[8] << ", Attack  " << Zombie.ZombAtkVec[8] << ", Range " << Zombie.ZombRngVec[8];
            for (int i = 9; i < Zombie.ZombieCount; i++)
            {
                std::cout << '\n'
                          << "  Zombie " << i + 1 << " : Health " << Zombie.ZombHpVec[i] << ", Attack  " << Zombie.ZombAtkVec[i] << ", Range " << Zombie.ZombRngVec[i];
            }
            break;
        
        default:
            break;
        }
    }
}

void HelpCommand()
{
    std::cout << "\nCommands";
    std::cout << "\n1. up        - Move up.";
    std::cout << "\n2. down      - Move down.";
    std::cout << "\n3. left      - Move left.";
    std::cout << "\n4. right     - Move right.";
    std::cout << "\n5. arrow     - Change the direction of an arrow.";
    std::cout << "\n6. help      - Display these user commands.";
    std::cout << "\n7. save      - Save the game.";
    std::cout << "\n8. load      - Load a game.";
    std::cout << "\n9. quit      - Quit the game.\n";
    pf::Pause();
    pf::ClearScreen();
    map.display();
    Combat();
}

void ArrowCommand()
{
    int Arow, Acolumn;
    std::string Adirec;
    char ch;
    std::cout << "\nEnter row, column, and direction: ";
    std::cin >> Arow >> Acolumn >> Adirec;

    std::for_each(Adirec.begin(), Adirec.end(), [](char &c)
                  { c = ::tolower(c); });

    ch = map.getObject(Acolumn, Arow);
    if (ch == '^' || ch == 'v' || ch == '<' || ch == '>')
    {
        if (Adirec == "up")
        {
            map.setObject(Acolumn, Arow, '^');
            std::cout << "Arrow object changed from " << ch << " to ^." << std::endl;
            pf::Pause();
            pf::ClearScreen();
            map.display();
            Combat();
        }
        else if (Adirec == "down")
        {
            map.setObject(Acolumn, Arow, 'v');
            std::cout << "Arrow object changed from " << ch << " to V." << std::endl;
            pf::Pause();
            pf::ClearScreen();
            map.display();
            Combat();
        }
        else if (Adirec == "left")
        {
            map.setObject(Acolumn, Arow, '<');
            std::cout << "Arrow object changed from " << ch << " to <." << std::endl;
            pf::Pause();
            pf::ClearScreen();
            map.display();
            Combat();
        }
        else if (Adirec == "right")
        {
            map.setObject(Acolumn, Arow, '>');
            std::cout << "Arrow object changed from " << ch << " to >." << std::endl;
            pf::Pause();
            pf::ClearScreen();
            map.display();  
            Combat();
        }
        else
        {
            std::cout << "Invalid direction." << std::endl;
            pf::Pause();
            pf::ClearScreen();
            map.display();
            Combat();
        }    
    }
    else
    {
        std::cout << "Please ensure that the position contains an arrow object." << std::endl;
        pf::Pause();
        pf::ClearScreen();
        map.display();
        Combat();
    }
}

void QuitCommand()
{
    char ans;
    std::cout << "\nAre you sure? (y/n): ";
    std::cin >> ans;
    if (ans == 'y' || ans == 'Y')
    {
        std::cout << "\n\nGoodbye!" << std::endl;
        pf::Pause();
        pf::ClearScreen();
        exit(0);
    }
    else
    {
        Combat();
    }
}

void PlayerMovement()
{
    Alien.alienTurn = true;
    std::cout << std::endl;
    std::cout << "\n<Command> => ";
    std::string userInput;
    std::cin >> userInput;
    std::for_each(userInput.begin(), userInput.end(), [](char &c)
                  { c = ::tolower(c); });

    if (userInput == "help")
    {
        HelpCommand();
    }
    else if (userInput == "arrow")
    {
        ArrowCommand();
    }
    else if (userInput == "quit")
    {
        QuitCommand();
    }
    
    do
    {
        Alien.AlienMove(map, userInput, Rows, Columns);
        Alien.AlienPlacement(map);
        if (Alien.hitBarrier == true)
        {
            pf::ClearScreen();
            map.display();
            map.CombatHUD();
            std::cout << "\n"
                      << "\nAlien hit the barrier!\n"
                      << std::endl;
            pf::Pause();
        }
        if (Alien.hitZombie == true)
        {
            pf::ClearScreen();
            map.display();
            map.CombatHUD();
            std::cout << "\n"
                      << "\nAlien hit Zombie " << Alien.AlienZomb
                      << "\n" << std::endl;
            pf::Pause();
        }
    } while (Alien.hitBarrier == false && Alien.hitObject == false && Alien.hitZombie == false);
}

int CalcZombDistance(int i)
{
    int distance;
    distance = (abs(Alien.posX - Zombie.ZombPosX[i]) + abs(Alien.posY - Zombie.ZombPosY[i]));
    return distance;
}

int CompareZombDistance() // Use this to calculate the nearest Zombie
{
    int x;
    int nearest = 5000;
    int nearestZomb = 0;
    for (int i = 0; i < Zombie.ZombieCount; i++)
    {
        x = Zombie.ZombDist.at(i);
        if (x < nearest)
        {
            nearest = x;
            nearestZomb = i + 1;
        }
    }
    
    return nearestZomb;
}

void EnemyMovement()
{
    Zombie.ZombieMove(map, Rows, Columns);
    pf::ClearScreen();
    map.display();
    map.CombatHUD();
    Zombie.ZombDist.at(Zombie.n) = CalcZombDistance(Zombie.n);
    Zombie.ZombieAttack(Zombie.n, Alien, map);
    pf::ClearScreen();
    map.display();
    map.CombatHUD();
    std::cout << "\n\nZombie " << Zombie.n + 1 << "'s turns ends.\n"
              << std::endl;
    pf::Pause();
    pf::ClearScreen();
    map.display();
    Zombie.n++;
}

void Combat()
{
    int distance;
    if (Alien.AlienHp >= 0)
    {
        map.CombatHUD();
        for (int i = 0; i < Zombie.ZombieCount; i++)
        {
            distance = CalcZombDistance(i);
            std::cout << "\nZombie " << i + 1 << " Distance : " << distance << std::endl;
            Zombie.ZombDist[i] = distance;
        }
        std::cout << "Nearest Zombie is: " << CompareZombDistance() << std::endl;
        Alien.hitObject = false;
        Alien.hitZombie = false;
        PlayerMovement();
        replaceDot(map, Columns, Rows);
        for (int i = 0; i < Zombie.ZombieCount; i++)
        {
            Alien.alienTurn = false;
            if (Zombie.ZombHpVec[i] >= 1)
            {
                EnemyMovement();
                Zombie.count = 49;
            }
        }
        //resets the zombie value on both gameboard and HUD
        Zombie.n = 0; //works
        Alien.alienTurn = true;
        Combat();
    }
}



int main()
{
    // srand(time(NULL));
    Alien.alienTurn = true;
    srand(1); // set fixed random value
    ShowGameSettings();
    pf::ClearScreen();
    makeBoard();
    
    Combat();
    
}
