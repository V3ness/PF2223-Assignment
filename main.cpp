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
    Alien.InitialLanding(map, Rows, Columns);
    Zombie.ZombieLanding(map, Rows, Columns);
    pf::ClearScreen();
    map.display();
}

void CombatHUD()
{
    Zombie.ZombieCreation();
    std::cout << "\n->Alien    : Health " << Alien.AlienHp << ", Attack  " << Alien.AlienAtk;
    for (int i = 0; i < Zombie.ZombieCount; i++)
    {
        std::cout << '\n'
                  << "  Zombie " << i + 1 << " : Health " << Zombie.ZombHpVec[i] << ", Attack  " << Zombie.ZombAtkVec[i] << ", Range " << Zombie.ZombRngVec[i];
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
}

void PlayerMovement()
{
    std::cout << std::endl;
    std::cout << "<Command> => ";
    std::string userInput;
    std::cin >> userInput;
    std::for_each(userInput.begin(), userInput.end(), [](char &c)
                  { c = ::tolower(c); });

    if (userInput == "help")
    {
        HelpCommand();
    }
    do
    {
            Alien.AlienMove(map, userInput, Rows, Columns);
            Alien.AlienPlacement(map);
            // pf::ClearScreen();
            // map.display();
            if (Alien.hitBarrier == true)
            {
                std::cout << "Alien hit the barrier!" << std::endl;
                pf::Pause();
            }
    } while (Alien.hitBarrier == false && Alien.hitObject == false);
}

void EnemyMovement()
{
    std::cout << "Zombie's turn bitch" << std::endl;
}

void Combat()
{
    if (Alien.AlienHp >= 0)
    {
        CombatHUD();
        PlayerMovement();
        replaceDot(map, Rows, Columns);
        for (int i = 0; i < Zombie.ZombieCount; i++)
        {
            if (Zombie.ZombHpVec[i] >= 1)
            {
                EnemyMovement();
                Combat();
            }
        }
    }
}

int main()
{
    srand(1);
    ShowGameSettings();
    pf::ClearScreen();
    makeBoard();

    Combat();
}
