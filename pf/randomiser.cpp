// Randomise with srand<time>
// 6 options "h, v, ^, <, >, p, ' '"

#include <iostream>
#include <time.h>
#include <vector>
#include <iterator>
#include <string>
#include <cmath>

char randomiseItems(char x)
{
    int randomNum = rand() % 10 + 1; // Can't randomise letters, so assigning each one number with a letter
    switch (randomNum)               // 4 assigned to space to make the chances of " " increase.
    {
    case 1:
        x = 'h';
        break;

    case 2:
        x = 'v';
        break;

    case 3:
        x = '^';
        break;

    case 4:
        x = '<';
        break;

    case 5:
        x = '>';
        break;

    case 6:
        x = ' ';
        break;

    case 7:
        x = 'p';
        break;

    case 8:
        x = ' ';
        break;

    case 9:
        x = ' ';
        break;

    case 10:
        x = ' ';
        break;
    }
    return x;
}

template <typename T> // Overloading Operator "<<" to let std::cout print out vector. (MUST NOT TOUCH)
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{

    for (size_t i = v.size() - 1; i < v.size(); i++)
    {
        os << v[i];
    }
    return os;
}

int main()
{
    char h, x;
    int Rows, Columns;
    srand(time(NULL));
    Rows = 3;
    Columns = 17;
    // For Testing Purposes
    std::cout << "How many rows do you want? => ";
    std::cin >> Rows;
    std::cout << "How many columns do you want? => ";
    ///////////////////////////////////////////////////////
    std::cin >> Columns;
    int kColumns = (Columns * 2) + 1;
    int XCount = 1;
    std::cout.width(10 + Columns);
    std::cout << "   .: Alien vs Zombie :." << std::endl;
    std::cout << std::endl;
    std::vector<std::vector<char>> board; // Make the board a sort of matrix
    board.clear();
    //     // board.push_back(h);
    // }
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
    std::vector<int> YCountSecondHalf;
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
    std::cout << "                     ";
    if (YCount > 10)
    {
        for (size_t i = 0; i < YCount - 10; i++) // Displays 2nd half of the double digits
        {
            std::cout << YCountSecondHalf[i] << " ";
        }
    }
}
