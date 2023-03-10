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
#include <fstream>
#include <numeric>
#include <filesystem>


char GSchoice;
bool GameOver = false;
int Rows, Columns;

void Combat();
int main();

std::vector<std::vector<char>> board; // Make the board a sort of matrix

Player Alien;
Enemy Zombie;
Map map;
Encdec encdec;


template <typename T> // Overloading Operator "<<" to let std::cout print out vector. (MUST NOT TOUCH)
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    for (size_t i = v.size() - 1; i < v.size(); i++)
    {
        os << v[i];
    }
    return os;
}

void Encdec::encrypt()
{
    std::fstream fin, fout;
 
    fin.open(map.filenameN, std::fstream::in);
    fout.open(map.filenameN + ".txt", std::fstream::out);
 
    while (fin >> std::noskipws >> c) {
        int temp = (c + key);
        fout << (char)temp;
    }
 
    fin.close();
    fout.close();
    std::filesystem::remove(map.filenameN);
}
 
// Definition of decryption function
void Encdec::decrypt()
{
    std::fstream fin;
    std::fstream fout;
    fin.open(map.filenameN + ".txt", std::fstream::in);
    fout.open(map.filenameN, std::fstream::out);
 
    while (fin >> std::noskipws >> c) {
 
        int temp = (c - key);
        fout << (char)temp;
    }
 
    fin.close();
    fout.close();
}

void difficultyChooser()
{
    char diffinput;
    std::cout << "\nChoose Your Desired Difficulty [E -> Easy | N -> Normal | H -> Hard] => ";
    std::cin >> diffinput;
    if (diffinput == 'e' || diffinput == 'E')
    {
        std::cout << "\nYou chose Easy mode, you may change the amount of rows and columns according to your liking.\n" << std::endl;
        pf::Pause();
        Rows = 15;
        Columns = 15;
        Zombie.ZombieCount = 1;
    }
    else if (diffinput == 'n' || diffinput == 'N')
    {
        std::cout << "\nYou chose Normal mode, you may change the amount of rows and columns according to your liking.\n" << std::endl;
        pf::Pause();
        Rows = 9;
        Columns = 9;
        Zombie.ZombieCount = 2;
    }
    else if (diffinput == 'h' || diffinput == 'H')
    {
        std::cout << "\nYou chose Hard mode, you may change the amount of rows and columns according to your liking.\n" << std::endl;
        pf::Pause();
        Rows = 5;
        Columns = 5;
        Zombie.ZombieCount = 2;
    }
    else
    {
        std::cout << "\nInvalid Input.\n" << std::endl;
        pf::Pause();
        pf::ClearScreen();
        difficultyChooser();
    }
    
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
    else if (Zombie.ZombieCount <= 0)
    {
        std::cout << "Really bro? You wanna win without even trying your best? GGWP bro" << std::endl;
        std::cout << "Here, let me let you win, by closing the game. Thanks for playing!\n\n";
        pf::Pause();
        exit(0);
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
    if (Rows <= 0 || Columns <= 0)
    {
        std::cout << "\nDid you... did you just tried to cheat the system by doing a whoopsies?\n";
        std::cout << "Please no. no. no. no. no. no. You can't do that.\n";
        Sleep(500);
        std::cout << "We can't have that here, it's dangerous!\n";
        Sleep(1000);
        std::cout << "\nThere is a reason why my love partner times me is equal to 0,\n";
        Sleep(1000);
        std::cout << "Because: ";
        Sleep(500);
        std::cout << "They. ";
        Sleep(500);
        std::cout << "Dont. ";
        Sleep(500);
        std::cout << "Exist.\n\n";
        Sleep(350);
        std::cout << "-Lester Liew, 19/2/2023\n\n\n";
        pf::Pause();
        pf::ClearScreen();
        ChangeGameSettings();
    }
    else if (Rows % 2 == 0 || Columns % 2 == 0)
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
        std::cout << "\n\n->Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
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
            std::cout << "\n\n  Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
            std::cout << '\n'
                      << "->Zombie " << 1 << " : Health " << Zombie.ZombHpVec[0] << ", Attack  " << Zombie.ZombAtkVec[0] << ", Range " << Zombie.ZombRngVec[0];
            for (int i = 1; i < Zombie.ZombieCount; i++)
            {
                std::cout << '\n'
                          << "  Zombie " << i + 1 << " : Health " << Zombie.ZombHpVec[i] << ", Attack  " << Zombie.ZombAtkVec[i] << ", Range " << Zombie.ZombRngVec[i];
            }
            break;

        case 1:
            std::cout << "\n\n  Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
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
            std::cout << "\n\n  Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
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
            std::cout << "\n\n  Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
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
            std::cout << "\n\n  Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
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
            std::cout << "\n\n  Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
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
            std::cout << "\n\n  Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
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
            std::cout << "\n\n  Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
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
            std::cout << "\n\n  Alien    : Health " << Alien.AlienHpVec[0] << ", Attack  " << Alien.AlienAtk;
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
        std::cout << "\nGoodbye. Have a nice day!" << std::endl;
        pf::Pause();
        pf::ClearScreen();
        exit(0);
    }
    else
    {
        pf::ClearScreen();
        map.display();
        Combat();
    }
}

bool repeatLoad;

void loadGame(std::string fileName, Map &map, Player &alien, Enemy &zombie) // Add file name here to customise it
{
    int pX, pY, HpVec, AtkVec, RngVec, Def;
    std::ifstream inFile(fileName);
    inFile >> map.rows >> map.columns;
    inFile >> alien.posX >> alien.posY;
    inFile >> zombie.ZombieCount >> pX >> pY >> HpVec >> AtkVec >> RngVec >> Def;
    zombie.ZombPosX.resize(pX);
    zombie.ZombPosY.resize(pY);
    zombie.ZombHpVec.resize(HpVec);
    zombie.ZombAtkVec.resize(AtkVec);
    zombie.ZombRngVec.resize(RngVec);
    zombie.Defeated.resize(Def);
    for (int i = 0; i < zombie.ZombieCount; i++)
    {
        int x;
        inFile >> zombie.ZombPosX[i] >> zombie.ZombPosY[i] >> zombie.ZombHpVec[i] >> zombie.ZombAtkVec[i] >> zombie.ZombRngVec[i] >> x;
        zombie.Defeated[i] = x;
    }
    inFile >> alien.AlienHpVec[0] >> alien.AlienAtk;
    map.init(map.rows, map.columns);
    for (int i = 0; i < map.columns; i++)
    {
        for (int j = 0; j < map.rows; j++)
        {
            inFile >> std::noskipws >> map.map_[i][j];
        }
    }
    inFile.close();
    std::filesystem::remove(map.filenameN);
    std::cout << "Game loaded successfully. \n\nThere might be certain areas in which the data is wrong, \nPlease write load again until the data is consistent\n"
              << std::endl;
    pf::Pause();
    pf::ClearScreen();
    map.display();
    Combat();
}

void saveGame(std::string fileName, Map &map, Player &alien, Enemy &zombie)
{
    std::ofstream outFile(fileName);
    outFile << map.rows << " " << map.columns << std::endl;
    outFile << alien.posX << " " << alien.posY << std::endl;
    outFile << zombie.ZombieCount << " " << zombie.ZombPosX.size() << " " << zombie.ZombPosY.size() << " "<< zombie.ZombHpVec.size() 
            << " " << zombie.ZombAtkVec.size() << " " << zombie.ZombRngVec.size() << " " << zombie.Defeated.size() << std::endl;
    for (int i = 0; i < zombie.ZombieCount; i++)
    {
        outFile << zombie.ZombPosX[i] << " " << zombie.ZombPosY[i] << " " << zombie.ZombHpVec[i]
                << " " << zombie.ZombAtkVec[i] << " " << zombie.ZombRngVec[i] << " " << zombie.Defeated[i] << std::endl;
    }
    outFile << alien.AlienHpVec[0] << " " << alien.AlienAtk;
    for (int i = 0; i < map.columns; i++)
    {
        for (int j = 0; j < map.rows; j++)
        {
            outFile << map.map_[i][j];
        }
    }
    outFile.close();
    encdec.encrypt();
    std::cout << "Game saved successfully." << std::endl;
    pf::Pause();
    pf::ClearScreen();
    map.display();
    Combat();
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
    else if (userInput == "save")
    {
        std::string fileName;
        std::cout << "Please name your file (There is no need for .txt extension at the end): ";
        std::cin >> fileName;
        map.filenameN = fileName;
        saveGame(fileName, map, Alien, Zombie);
    }
    else if (userInput == "load")
    {
        std::string fileName;
        map.filenameN = fileName;
        char choice;
        std::cout << "Do you want to save the current game? (y/n)> ";
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            std::cout << "Please name your file (There is no need for .txt extension at the end): ";
            std::cin >> fileName;
            saveGame(fileName, map, Alien, Zombie);
        }
        else if (choice == 'n' || choice == 'N')
        {
            std::cout << "Please insert the name of your save file (There is no need for .txt extension at the end): ";
            std::cin >> fileName;
            map.filenameN = fileName;
            if (std::filesystem::exists(fileName + ".txt"))
            {
                encdec.decrypt();
                loadGame(fileName, map, Alien, Zombie);
            }
            else
            {
                std::cout << "No such file exists? Are you sure you entered the correct file name?\n";
                pf::Pause();
                pf::ClearScreen();
                map.display();
                Combat();
            }
        }
        else
        {
            std::cout << "\nInvalid Input." << std::endl;
            pf::Pause();
            pf::ClearScreen();
            map.display();
            Combat();
        }
    }
    else if (userInput == "up" || userInput == "down" || userInput == "left" || userInput == "right")
    {
        do
        {
            Alien.AlienMove(map, Zombie, Alien, userInput, Rows, Columns);
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
                          << "\nAlien attack Zombie " << Alien.AlienZomb << "." << std::endl;
                Alien.AlienAttack(Alien.AlienZomb, Zombie, userInput, map, Alien);
            }
        } while (Alien.hitBarrier == false && Alien.hitObject == false && Alien.hitZombie == false);
    }
    else
    {
        std::cout << "Oops! Invalid Input." << std::endl;
        pf::Pause();
        pf::ClearScreen();
        map.display();
        Combat();
    }
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

void podEffect()
{
    int distance;
    for (int i = 0; i < Zombie.ZombieCount; i++)
    {
        distance = CalcZombDistance(i);
        // std::cout << "\nZombie " << i + 1 << " Distance : " << distance << std::endl;
        Zombie.ZombDist[i] = distance;
        Zombie.nearestZomb = CompareZombDistance();
    }
    Zombie.ZombHpVec[Zombie.nearestZomb - 1] = Zombie.ZombHpVec[Zombie.nearestZomb - 1] - 10;
}

void podMessage()
{
    std::cout << "\n\nAlien has encountered a pod that deals 10 damage to the nearest zombie, "
              << "which is Zombie " << Zombie.nearestZomb
              << std::endl;
    if (Zombie.ZombHpVec[Zombie.nearestZomb - 1] <= 0)
    {
        map.setObject(Zombie.ZombPosX[Zombie.nearestZomb - 1], Zombie.ZombPosY[Zombie.nearestZomb - 1], ' ');
        std::cout << "Alien has defeated zombie " << Zombie.nearestZomb << "." << std::endl;
        Zombie.ZombHpVec[Zombie.nearestZomb - 1] = 0;
        Zombie.Defeated[Zombie.nearestZomb - 1] = true;
    }
    else
    {
        std::cout << "Zombie " << Zombie.nearestZomb << " is stil alive. " << std::endl;
        std::cout << "Health left: " << Zombie.ZombHpVec[Zombie.nearestZomb - 1] << "\n\n";
    }
}

void gameover(Player &Alien, Enemy &Zombie)
{
    char choice;
    std::cout << "Play again? (y/n)> ";
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y')
    {
        map.lastroundX = map.rows;
        map.lastroundY = map.columns;
        Alien.AlienHpVec.clear();
        Alien.AlienMaxHpVec.clear();
        Zombie.ZombPosX.clear();
        Zombie.ZombPosY.clear();
        Zombie.ZombHpVec.clear();
        Zombie.ZombAtkVec.clear();
        Zombie.ZombRngVec.clear();
        Zombie.ZombDist.clear();
        Zombie.count = 49;
        Zombie.n = 0;
        map.map_.clear();
        pf::ClearScreen();
        main();
    }
    else if (choice == 'n' || choice == 'N')
    {
        std::cout << "Goodbye. Have a nice day!" << std::endl;
        pf::Pause();
        pf::ClearScreen();
        exit(0);
    }
    else
    {
        std::cout << "\nInvalid input" << std::endl;
        gameover(Alien, Zombie);
    }
}

void EnemyMovement()
{
    Alien.AlienAtk = 0;
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
        if ((Zombie.Defeated.end() == std::find(Zombie.Defeated.begin(), Zombie.Defeated.end(), false)))
        {
            pf::ClearScreen();
            map.display();
            map.CombatHUD();
            std::cout << "\n\nYou won!\n";
            gameover(Alien, Zombie);
        }
        map.CombatHUD();
        for (int i = 0; i < Zombie.ZombieCount; i++)
        {
            distance = CalcZombDistance(i);
            // std::cout << "\nZombie " << i + 1 << " Distance : " << distance << std::endl;
            Zombie.ZombDist[i] = distance;
            Zombie.nearestZomb = CompareZombDistance();
        }
        // std::cout << "Nearest Zombie is: " << CompareZombDistance() << std::endl;
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
        // resets the zombie value on both gameboard and HUD
        Zombie.n = 0;
        Alien.alienTurn = true;
        Combat();
    }
}

int main()
{
    // srand(time(NULL));
    Alien.AlienHpVec.clear();
    Alien.AlienMaxHpVec.clear();
    Zombie.ZombPosX.clear();
    Zombie.ZombPosY.clear();
    Zombie.ZombHpVec.clear();
    Zombie.ZombAtkVec.clear();
    Zombie.ZombRngVec.clear();
    Zombie.ZombDist.clear();
    Zombie.Defeated.clear();
    Alien.alienTurn = true;
    srand(1); // set fixed random value
    difficultyChooser();
    ShowGameSettings();
    pf::ClearScreen();
    makeBoard();
    Zombie.Defeated.resize(Zombie.ZombieCount, false);

    Combat();
}
