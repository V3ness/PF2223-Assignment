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
#include <iostream>
#include <windows.h>
#include <time.h>
#include <vector>
#include <iterator>
#include <string>
#include <cmath>

char GSchoice;
int Rows = 3, Columns = 9;
std::vector<std::vector<char>> board; // Make the board a sort of matrix
int kColumns = (Columns * 2) + 1;
int XCount = 1;


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

void CreateGameBoard() //Edit here for zombie and alien (at the end)
{
    ClearScreen();
    char h, x;
    srand(time(NULL));
    ///For Testing Purposes////////////////////////////////
    // std::cout << "How many rows do you want? => ";
    // std::cin >> Rows;
    // std::cout << "How many columns do you want? => ";
    // std::cin >> Columns;
    ///////////////////////////////////////////////////////
    int kColumns = (Columns * 2) + 1;
    int XCount = 1;
    std::cout.width(12 + Columns);
    std::cout << ".: Alien vs Zombie :." << std::endl;
    for (int x = 0; x < Rows; x++)
    {
        std::cout << "   ";
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
        if (XCount > 9)
        {
            std::cout << " ";
        }
        else
        {
            std::cout << "  ";
        }
        std::cout << XCount << " "; //Display Rows Numbers
        XCount++;
        for (int y = 0; y < kColumns; y++)
        {
            board.push_back(std::vector<char>());
            if (y % 2 == 0)
            {
                std::cout << "|";
            }
            else
            {
                h = randomiseItems(x);
                board[y].push_back(h);
                std::cout << board[y];
            }
        }
        std::cout << std::endl;
    }
    std::cout << "   ";
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
    std::cout << "   ";
    std::vector<int> YCountSecondHalf;
    int YCount = 1;
    for (int x = 0; x < kColumns; x++) // Display Columns Numbers
    {
        if (x % 2 == 1)
        {
            // std::cout << YCount;

            if (YCount > 9)
            {
                int YCount1 = YCount % 10;           // Splits the 2nd digit out
                int YCount2 = YCount / 10 % 10;      // Splits the 1st digit out
                std::cout << YCount2;                // Prints out the 1st digit
                YCountSecondHalf.push_back(YCount1); // Push the 2nd digits into a vector
                YCount += 1;
            }
            else
            {
                std::cout << YCount;
                YCount += 1;
            }
        }
        else
        {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "                      ";
    if (YCount > 10)
    {
        for (size_t i = 0; i < YCount - 10; i++) // Displays 2nd half of the double digits
        {
            std::cout << YCountSecondHalf[i] << " ";
        }
    }
    board[Columns][(Rows/2)] = {'A'};
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

void RefreshGameBoard() //RefreshGameBoard is just refresh, no need to edit this
{
    ClearScreen();
    ///For Testing Purposes////////////////////////////////
    // std::cout << "How many rows do you want? => ";
    // std::cin >> Rows;
    // std::cout << "How many columns do you want? => ";
    // std::cin >> Columns;
    ///////////////////////////////////////////////////////
    std::cout << "   .: Alien vs Zombie :." << std::endl;
    std::cout << std::endl;
    int kColumns = (Columns * 2) + 1;
    XCount= 1;
    for (int x = 0; x < Rows; x++)
    {
        std::cout << "   ";
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
        std::cout << XCount;        
        if (XCount > 9)
        {
            std::cout << " ";
        }
        else
        {
            std::cout << "  ";
        }
        XCount++;
        for (int y = 0; y < kColumns; y++)
        {
            board.push_back(std::vector<char>());
            if (y % 2 == 0)
            {
                std::cout << "|";
            }
            else
            {
                std::cout << board[y][x];
            }
        }
        std::cout << std::endl;
    }
    std::cout << "   ";
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
    std::cout << "   ";
    std::vector<int> YCountSecondHalf;
    int YCount = 1;
    YCountSecondHalf.clear();
    for (int x = 0; x < kColumns; x++) // Display Columns Numbers
    {
        if (x % 2 == 1)
        {
            if (YCount > 9)
            {
                int YCount1 = YCount % 10;           // Splits the 2nd digit out
                int YCount2 = YCount / 10 % 10;      // Splits the 1st digit out
                std::cout << YCount2;                // Prints out the 1st digit
                YCountSecondHalf.push_back(YCount1); // Push the 2nd digits into a vector
                YCount += 1;
            }
            else
            {
                std::cout << YCount;
                YCount += 1;
            }
        }
        else
        {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "                      ";
    if (YCount > 10)
    {
        for (size_t i = 0; i < YCount - 10; i++) // Displays 2nd half of the double digits
        {
            std::cout << YCountSecondHalf[i] << " ";
        }
    }
}

void ShowAlienHUD()
{
    std::cout << "\n->Alien    : Life " << Alien.AlienHp << ", Attack  " << Alien.AlienAtk;
}

void ShowZombieHUD()
{
    std::cout << "\n  Zombie   : Life " << Zombie.ZombieHp << ", Attack  " << Zombie.ZombieAtk << ", Range " << Zombie.ZombieRange;
}

int main()
{
    ShowGameSettings();
    CreateGameBoard();
    ShowAlienHUD();
    ShowZombieHUD();
    // RefreshGameBoard();
}
