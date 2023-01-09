// *********************************************************
// demo.cpp
//
// This program is intended to demonstrate helper functions 
//   and/or classes in the "pf" folder.
//
// This program will be updated if more helper functions
//   and/or classes are given from time to time.
//
// Do not modify/use this program to do your assignment.
//   Instead, use "main.cpp".
// 
// To compile this program, type the following in the terminal
//
// For CMD or PowerShell (in Windows)
//
//              g++ pf\*.cpp demo.cpp -DDEMO
//
// For Bash (in MacOS or Linux)
//
//              g++ pf/*.cpp demo.cpp -DDEMO
//
// *********************************************************

// Prepend "pf/" to filename to include source code in
//   the "pf"  folder.
#include "pf/helper.h"
#include <iostream>
using namespace std;

void DemoPause()
{
    cout << "Pausing Now" << endl;
    pf::Pause();
    cout << endl;
}

void DemoClearScreen()
{
    cout << "Pausing and Clearing Screen Now" << endl;
    pf::Pause();
    pf::ClearScreen();
    cout << endl;
}

void DemoCreateGameBoard()
{
    cout << "Create Game Board" << endl;
    pf::CreateGameBoard();
    pf::ShowGameBoard();
}

#ifdef DEMO
int main()
{
    cout << "===== Begin Demo =====" << endl;
    
    // DemoPause();
    // DemoClearScreen();
    DemoCreateGameBoard();

    cout << "===== End Demo =====" << endl;
}
#endif