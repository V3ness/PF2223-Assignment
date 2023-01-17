// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT1L
// Names: ANG KHAI PIN | LESTER LIEW JUN MIN |
// IDs: 1211101248 | 1221302721 |
// Emails: 1211101248@student.mmu.edu.my | 1221302721@student.mmu.edu.my |
// Phones: 011-57725120 | 012-9156393 |
// *********************************************************

#include "pf/helper.h"

class Zombie
{
public:



};

#include <iostream>
#include <windows.h>

char GSchoice;
int Rows = 3, Columns = 9;

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

void CreateGameBoard()
{
    ClearScreen();
    int kColumns = (Columns * 2) + 1;
    int XCount = 1;
    std::cout.width(10 + Columns);
    std::cout << ".: Alien vs Zombie :." << std::endl;
    for (int x = 0; x < Rows; x++)
    {
        std::cout << "  ";
        for (int y = 0; y < kColumns; y++)
        {
            if (y % 2 == 0)
            {
                std::cout << "+";
            }
            else
            {
                std::cout << "-";
            }
        }
        std::cout << std::endl;
        std::cout << XCount << " ";
        XCount++;
        for (int y = 0; y < kColumns; y++)
        {
            if (y % 2 == 0)
            {
                std::cout << "|";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "  ";
    for (int y = 0; y < kColumns; y++)
    {
        if (y % 2 == 0)
        {
            std::cout << '+';
        }
        else
        {
            std::cout << '-';
        }
    }
    std::cout << std::endl;
    std::cout << "  ";
    int YCount = 1;
    for (int x = 0; x < kColumns; x++) //Display Columns Numbers
    { 
        if (x % 2 == 1)
        {
            std::cout << YCount;
            YCount += 1;
        }
        else
        {
            std::cout << " ";
        }
    }
}

void ChangeGameSettings()
{
    std::cout << "Board Settings\n";
    std::cout << "-----------------\n";
    std::cout << "Enter Rows    : ";
    std::cin >> Rows;
    std::cout << "Enter Columns : ";
    std::cin >> Columns;
    if (Rows % 2 == 0 || Columns % 2 == 0)
    {
        std::cout << "Please ensure that Rows and Columns are odd numbers.\n";
        Sleep(4000);
        ClearScreen();
        ChangeGameSettings();
    }
    else
    {
        Sleep(500);
        std::cout << "\nZombie Settings\n";
        std::cout << "-----------------\n";
        std::cout << "Enter number of zombies: " << '\n';
        // std::cin >> kZombieCount;
        std::cout << "\nSettings Updated.\n";
        Pause();
    }
}

void GameSettings()
{
    std::cout << "Board Rows    : " << Rows << '\n';
    std::cout << "Board Columns : " << Columns << '\n';
    std::cout << "Zombie Count  :" << '\n';
    // std::cin >> kZombieCount;
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

int main()
{
    ShowGameSettings();
    CreateGameBoard();
}
