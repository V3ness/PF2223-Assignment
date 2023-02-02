// Randomise with srand<time>
// 6 options "h, v, ^, <, >, p, ' '"

#include "header.h"

char randomiseItems(char x)
{
    int randomNum = rand() % 10 + 1; // Can't randomise letters, so assigning each one number with a letter
    switch (randomNum)               // 4 assigned to space to make the chances of " " increase.
    {
    case 1:
        x = 'h'; // h is Health (+20 health to Alien)
        break;

    case 2:
        x = 'v'; // Arrows (v ^ < >) changes movement for alien
        break;

    case 3:
        x = '^'; // Arrows (v ^ < >) changes movement for alien
        break;

    case 4:
        x = '<'; // Arrows (v ^ < >) changes movement for alien
        break;

    case 5:
        x = '>'; // Arrows (v ^ < >) changes movement for alien
        break;

    case 6:
        x = 'p';
        break;

    case 7:
        x = ' ';
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


