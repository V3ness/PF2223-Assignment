#include "helper.h"
#include <cstdlib>
#include <iostream>

namespace pf
{
    const int kRows = 3;
    const int kColumns = 5;
    char kBoard[kRows][kColumns];

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

    void CreateGameBoard()
    {
        for (int row = 0; row < kRows; ++row)
        for (int col = 0; col < kColumns; ++col)
        {
            int random_number = std::rand() % 2;
            if (random_number)
                kBoard[row][col] = '*';
            else
                kBoard[row][col] = 'r';
        }
    }

    void ShowGameBoard()
    {
        for (int row = 0; row < kRows; ++row)
        {
            for (int col = 0; col < kColumns; ++col)
            {
                std::cout << kBoard[row][col];
            }
            std::cout << std::endl;
        }
            
    }
}