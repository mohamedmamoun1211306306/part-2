#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
#include <ctime>
#include <climits>
#include <string>
#include <sstream>
using namespace std;

int BOARDROWS = 5, BOARDCOLUMNS = 9;
int ZOMBIESNUM = 1, NOWTURN = 0;

struct Object
{
    char type;
    int x, y;
};

struct Alien
{
    int life;
    int attack;
    char direction = '^';
    int x, y;
};

struct Zombie
{
    char id;
    int life;
    int attack;
    int range;
    int x, y;
};

void setGameSettings();
void setBoardSettings();
vector<vector<char>> getBoard();
void makeBoard(vector<vector<char>> &board);
char getRandomObject();
void encPod(Alien &alien, vector<Zombie> &zombies);
void encHealth(Alien &alien);
void encArrow(char nextSpot, Alien &alien);
void displayBoard(vector<vector<char>> &board);
void initializeBoard(Alien &alien, vector<Zombie> &zombies, vector<vector<char>> &board);
void alienGame(Alien &alien, vector<vector<char>> &board, vector<Zombie> &zombies);
bool inputCommand(Alien &alien, vector<Zombie> &zombies, vector<vector<char>> &board);
void checkNextStops(char nextLocation, Alien &alien, vector<Zombie> &zombies);
void displayStatus(Alien &alien, vector<Zombie> &zombies);
bool checkZombieCommingMove(int newX, int newY, vector<vector<char>> &board);
void loadGame(string filename, Alien &alien, vector<Zombie> &zombies, vector<vector<char>> &board);
void saveGame(string filename, Alien &alien, vector<Zombie> &zombies, vector<vector<char>> &board);
void ChangeArrowDirection(vector<vector<char>> &board);
void gamePlay();
char boradcheck(char c);
// set the boarder with the rows and cols from user input
void setBoardSettings()
{
    system("cls");
    int tempRow = 1, tempCol = 1;
    do
    {
        if (tempRow % 2 == 0 || tempCol % 2 == 0)
        {
            cout << "Invalid input. to set the board Rows and columns must be odd numbers." << endl;
        }
        cout << "Enter rows => ";
        cin >> tempRow;
        cout << "Enter columns => ";
        cin >> tempCol;
    } while (tempRow % 2 == 0 || tempCol % 2 == 0);
    do
    {
        if (ZOMBIESNUM < 0)
        {
            cout << "Invalid input. Number of zombies must be a positive integer." << endl;
        }
        cout << "Enter number of zombies => ";
        cin >> ZOMBIESNUM;
    } while (ZOMBIESNUM <= 0);
    BOARDCOLUMNS = (tempCol * 2) + 1;
    BOARDROWS = (tempRow * 2) + 1;
    system("pause");
}
// set the Game settings in the start of the game
void setGameSettings()
{
start:
    char choice;
    cout << "Default Game Settings"
         << "\n------------------------"
         << "\nBoard Rows     :" << BOARDROWS
         << "\nBoard Columns  :" << BOARDCOLUMNS
         << "\nZombie Count   :" << ZOMBIESNUM
         << endl;

    cout << "Do you wish to change the game settings (y/n)? ";
    cin >> choice;
    if (tolower(choice) == 'y')
    {
        setBoardSettings();
    }
    else if (tolower(choice) == 'n')
    {
        BOARDCOLUMNS = (BOARDCOLUMNS * 2) + 1;
        BOARDROWS = (BOARDROWS * 2) + 1;
    }
    else
    {
        cout << "Wrong input" << endl;
        system("pause");
        system("CLS");
        goto start;
    }
}

vector<vector<char>> getBoard()
{
    vector<vector<char>> temp(BOARDROWS, vector<char>(BOARDCOLUMNS));
    return temp;
}

void makeBoard(vector<vector<char>> &board)
{

    for (int x = 0; x < BOARDCOLUMNS; x++)
    {

        for (int y = 0; y < BOARDROWS; y++)
        {
            board[x][y] = ' ';
            if (x == (BOARDCOLUMNS + 1) / 2 && y == (BOARDROWS + 1) / 2)
            {
                board[x][y] = 'A';
            }
        };
    }
}

char getRandomObject()
{
    vector<char> nonTrailObjects = {'^', 'v', '<', '>', 'h', 'p', 'r', ' '};
    int randomIndex = rand() % nonTrailObjects.size();
    return nonTrailObjects[randomIndex];
}

void initializeFrame(vector<vector<char>> &board)
{
    for (int i = 0; i < BOARDROWS; i++)
    {
        for (int j = 0; j < BOARDCOLUMNS; j++)
        {
            if (i % 2 == 0)
            {
                if (j % 2 == 0)
                {
                    board[i][j] = '+';
                }
                else
                {
                    board[i][j] = '-';
                }
            }
            else
            {
                if (j % 2 == 0)
                {
                    board[i][j] = '|';
                }
                else
                {
                    board[i][j] = ' ';
                }
            }
        }
    }
}

void placeAlien(Alien &alien, vector<vector<char>> &board)
{
    // Place the alien at the center of the board
    alien.x = BOARDROWS / 2;
    alien.y = BOARDCOLUMNS / 2;
    board[alien.x][alien.y] = 'A';
}
void displayAlien(Alien &alien, vector<vector<char>> &board)
{
    board[alien.x][alien.y] = 'A';
}
void placeObjects(vector<Object> &Objects, vector<vector<char>> &board)
{
    srand(time(NULL));
    int numberOfObjects = rand() % (BOARDROWS * BOARDCOLUMNS - 1);
    for (int i = 0; i < numberOfObjects; i++)
    {
        Object obj;
        obj.type = getRandomObject();
        obj.x = (rand() % (BOARDROWS - 1)) | 1;
        obj.y = (rand() % (BOARDCOLUMNS - 1)) | 1;

        for (int j = 0; j < Objects.size(); j++)
        {
            while (obj.x == Objects[j].x && obj.y == Objects[j].y)
            {
                obj.x = (rand() % (BOARDROWS - 1)) | 1;
                obj.y = (rand() % (BOARDCOLUMNS - 1)) | 1;
            }
        }

        board[obj.x][obj.y] = obj.type;
        Objects.push_back(obj);
    }
}

void placeZombies(vector<Zombie> &zombies, vector<vector<char>> &board)
{
    for (int i = 0; i < zombies.size(); i++)
    {
        zombies[i].x = (rand() % (BOARDROWS - 1)) | 1;
        zombies[i].y = (rand() % (BOARDCOLUMNS - 1)) | 1;
        // check if the location is not occupied by other zombies
        for (int j = 0; j < i; j++)
        {
            while (zombies[i].x == zombies[j].x && zombies[i].y == zombies[j].y)
            {
                zombies[i].x = (rand() % (BOARDROWS - 1)) | 1;
                zombies[i].y = (rand() % (BOARDCOLUMNS - 1)) | 1;
            }
        }
        board[zombies[i].x][zombies[i].y] = zombies[i].id;
    }
}

void initializeBoard(Alien &alien, vector<Zombie> &zombies, vector<vector<char>> &board)
{
    initializeFrame(board);
    srand(time(NULL));
    vector<Object> Objects;

    placeObjects(Objects, board);
    placeZombies(zombies, board);
    placeAlien(alien, board);
}

void initializeBoard(Alien &alien, vector<Zombie> &zombies, vector<Object> &Objects, vector<vector<char>> &board)
{
    makeBoard(board);
    placeObjects(Objects, board);
    placeZombies(zombies, board);
    placeAlien(alien, board);
}

void displayBoard(vector<vector<char>> &board)
{
    // print the board
    for (int i = 0; i < BOARDROWS; i++)
    {
        for (int j = 0; j < BOARDCOLUMNS; j++)
        {
            cout << board[i][j];
        }
        cout << endl;
    }
}

void initializePlayers(Alien &alien, vector<Zombie> &zombies)
{
    srand(time(NULL));
    for (int i = 0; i < ZOMBIESNUM; i++)
    {
        Zombie newZombie;
        newZombie.id = i + '1';
        newZombie.life = rand() % 80 + 20;
        newZombie.attack = rand() % 20 + 10;
        newZombie.range = rand() % (min(BOARDROWS, BOARDCOLUMNS) / 2) + 1;
        newZombie.x = rand() % BOARDROWS;
        newZombie.y = rand() % BOARDCOLUMNS;
        zombies.push_back(newZombie);
    }
    alien.life = 100;
    alien.attack = rand() % 20 + 1;
}

void checkNextStops(char nextSpot, Alien &alien, vector<Zombie> &zombies)
{
    switch (nextSpot)
    {
    case '^':
    case 'v':
    case '<':
    case '>':
        encArrow(nextSpot, alien);
        break;
    case 'h':
        // add 20 life to alien
        encHealth(alien);
        break;
    case 'p':
        // inflict damage to zombies
        encPod(alien, zombies);
        break;
    case ' ':
        cout << "This spot is empty" << endl;
        system("pause");
        break;
    }
}

void encArrow(char nextSpot, Alien &alien)
{
    alien.attack += 20;
    alien.direction = nextSpot;
    cout << "Alein changes direction to " << nextSpot << endl;
    system("pause");
}

void encHealth(Alien &alien)
{
    if (alien.life <= 100)
    {
        alien.life += 20;
    }
    cout << "\nAlein encounters a health pack"
         << "\nAlein's lifes increased by 20 "
         << endl;
    system("pause");
}

bool checkWin(vector<Zombie> &zombies)
{
    int deadZombies = 0;
    for (int i = 0; i < zombies.size(); i++)
    {
        if (zombies[i].life == 0)
        {
            deadZombies++;
        }
    }
    if (deadZombies == zombies.size())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void encPod(Alien &alien, vector<Zombie> &zombies)
{
    int minDistance = INT_MAX;
    int nearstZIndex = 0;
    for (int i = 0; i < zombies.size(); i++)
    {
        int distance = abs(alien.x - zombies[i].x) + abs(alien.y - zombies[i].y);
        if (distance < minDistance)
        {
            minDistance = distance;
            nearstZIndex = i;
        }
    }
    zombies[nearstZIndex].life -= alien.attack;
    cout << "Zombie " << nearstZIndex + 1 << " has been damaged by " << alien.attack << endl;
    if (zombies[nearstZIndex].life <= 0)
    {
        cout << "Zombie " << nearstZIndex + 1 << " has been defeated " << endl;
        zombies[nearstZIndex].attack = 0;
        zombies[nearstZIndex].life = 0;
        zombies[nearstZIndex].range = 0;
        if (checkWin(zombies))
        {
            cout << "You Win!" << endl;
            cout << "Thank You For Playing" << endl;
            system("pause");
            exit(0);
        }
    }
    system("pause");
}
void alienGame(Alien &alien, vector<vector<char>> &board, vector<Zombie> &zombies)
{

    while (true)
    {
        int nextX = alien.x;
        int nextY = alien.y;
        // calculate the next location based on the current direction
        switch (alien.direction)
        {
        case '^':
            nextX = alien.x - 2;
            break;
        case 'v':
            nextX = alien.x + 2;
            break;
        case '<':
            nextY = alien.y - 2;
            break;
        case '>':
            nextY = alien.y + 2;
            break;
        }
        if (nextX == -1 || nextX >= BOARDROWS - 1 || nextY == -1 || nextY >= BOARDCOLUMNS - 1)
        {
            cout << "Alien hit a board border and its turn ended." << endl;
            return;
        }
        else
        {
            char nextLocation = board[nextX][nextY];
            if (nextLocation == 'r')
            {
                cout << "Alien hits a rock can't move" << endl;
                while (board[nextX][nextY] == 'r')
                {
                    board[nextX][nextY] = getRandomObject();
                }
                break;
            }
            else
            {
                checkNextStops(nextLocation, alien, zombies);
                board[nextX][nextY] = 'A';
                board[alien.x][alien.y] = '.';
                alien.x = nextX;
                alien.y = nextY;
                system("CLS");
                system("pause");
                displayBoard(board);
                displayStatus(alien, zombies);
            }
        }
    }
}

bool inputCommand(Alien &alien, vector<Zombie> &zombies, vector<vector<char>> &board)
{
    bool moveable = false;
    cout << "\n\ncommand -> " << endl;
    string command;
    cin >> command;
    if (command == "up")
    {
        alien.direction = '^';
        moveable = true;
    }
    else if (command == "down")
    {
        alien.direction = 'v';
        moveable = true;
    }

    else if (command == "left")
    {
        alien.direction = '<';
        moveable = true;
    }
    else if (command == "right")
    {
        alien.direction = '>';
        moveable = true;
    }
    else if (command == "arrow")
    {
        ChangeArrowDirection(board);
        system("pause");
        system("CLS");
        displayBoard(board);
    }
    else if (command == "help")
    {
        cout << "\nCommands:"
             << "\n up       to move up"
             << "\ndown      to move down"
             << "\nleft      to move left"
             << "\nright     to move right"
             << "\narrow     to chang arrow direction "
             << "\nhelp      to see all the comands"
             << "\nsave      to save your curent game"
             << "\nload      to load an old game"
             << "\nquit      to quit the game" << endl;
        system("pause");
        system("CLS");
        displayBoard(board);
        displayStatus(alien, zombies);
    }

    else if (command == "save")
    {
        string filename;
        cout << "enter file name:";
        cin >> filename;
        saveGame(filename, alien, zombies, board);
    }
    else if (command == "load")
    {
        string filename;
        cout << "enter file name:";
        cin >> filename;
        loadGame(filename, alien, zombies, board);
    }
    else if (command == "quit")
    {
        cout << "Are you sure you want to quit? y/n" << endl;
        char confirm;
        cin >> confirm;
        if (tolower(confirm) == 'y')
        {
            exit(0);
        }
    }
    else
    {
        cout << "Invalid command. Type 'help' for a list of commands." << endl;
    }

    return moveable;
}

void displayStatus(Alien &alien, vector<Zombie> &zombies)
{

    string select1 = "    ";
    if (0 == NOWTURN)
    {
        select1 = "->  ";
    }
    cout << select1 << "Alien   :"
         << "  Life : " << alien.life << "    Attack: " << alien.attack << endl;

    for (auto i = 0; i < zombies.size(); i++)
    {
        string select = "    ";

        if (i + 1 == NOWTURN)
        {
            select = "->  ";
        }

        cout << select << "Zombie " << i + 1 << ":"
             << "  Life : " << zombies[i].life
             << "    Attack: " << zombies[i].attack
             << "     Range: " << zombies[i].range << endl;
    }
    cout << endl
         << endl;
}
bool alienInZombieRange(Alien alien, Zombie zombie, vector<vector<char>> &board)
{
    int alienX = alien.x;
    int alienY = alien.y;
    int zombieX = zombie.x;
    int zombiesY = zombie.y;
    int range = zombie.range;

    if (alienX >= zombieX - range && alienX <= zombieX + range && alienY == zombiesY)
    {
        // Alien is within range horizontally
        return true;
    }
    else if (alienY >= zombiesY - range && alienY <= zombiesY + range && alienX == zombieX)
    {
        // Alien is within range vertically
        return true;
    }
    else
    {
        return false;
    }
}
void zombieDamage(Alien &alien, Zombie zombie, vector<vector<char>> &board)
{

    if (alienInZombieRange(alien, zombie, board))
    {
        alien.life -= zombie.attack;
        cout << "Zombie " << zombie.id << " attacked Alien, Alien's life: " << alien.life << endl;
        if (alien.life <= 0)
        {
            cout << "Alien has been defeated" << endl;
            exit(0);
        }
    }
    else
    {
        cout << "Zombie cant attack out of range " << endl;
    }
}
void zombiesGame(Alien &alien, vector<vector<char>> &board, Zombie &zombie)
{

    int newX = zombie.x;
    int newY = zombie.y;
    char moves[4] = {'v', '^', '<', '>'};
    int moveIndex;
    string moveDirection;
    do
    {
        moveIndex = rand() % 4;
        char move = moves[moveIndex];
        switch (move)
        {
        case 'v':
            newX = zombie.x + 2;
            moveDirection = "Down";
            break;
        case '^':
            newX = zombie.x - 2;
            moveDirection = "Up";
            break;
        case '>':
            newY = zombie.y + 2;
            moveDirection = "Right";
            break;
        case '<':
            newY = zombie.y - 2;
            moveDirection = "Left";
            break;
        }
    } while (!(checkZombieCommingMove(newX, newY, board)));

    cout << "Zombie moves " << moveDirection << endl;
    // check if new coordinates are within board boundaries and not occupied by alien
    board[zombie.x][zombie.y] = ' ';
    zombie.x = newX;
    zombie.y = newY;
    board[zombie.x][zombie.y] = zombie.id;
    system("pause");
    zombieDamage(alien, zombie, board);
}

bool checkZombieCommingMove(int newX, int newY, vector<vector<char>> &board)
{

    if (newX >= 0 && newX < BOARDROWS && newY >= 0 && newY < BOARDCOLUMNS)
    {
        if (board[newX][newY] != 'A' && board[newX][newY] != 'Z' && (board[newX][newY] < '1' || board[newX][newY] > '9'))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void ChangeArrowDirection(vector<vector<char>> &board)
{
    int row, col;
    cout << "Enter the row and column of the arrow object to switch: ";
    cin >> row >> col;
    char newDirection;
    cout << "Enter the new direction of the arrow object (^, v, <, >): ";
    cin >> newDirection;
    // check if the entered coordinates are valid
    if (row < 0 || row >= BOARDROWS || col < 0 || col >= BOARDCOLUMNS)
    {
        cout << "Invalid coordinates!" << endl;
        return;
    }
    // check if the entered direction is valid
    if (newDirection != '^' && newDirection != 'v' && newDirection != '<' && newDirection != '>')
    {
        cout << "Invalid direction!" << endl;
        return;
    }
    // check if the current object is an arrow
    if (board[row][col] != '^' && board[row][col] != 'v' && board[row][col] != '<' && board[row][col] != '>')
    {
        cout << "This is not an arrow object!" << endl;
        return;
    }
    // switch the direction of the arrow
    board[row][col] = newDirection;
    cout << "Arrow direction switched successfully!" << endl;
}

void saveGame(string filename, Alien &alien, vector<Zombie> &zombies, vector<vector<char>> &board)
{
    ifstream checkfile(filename);

    if (checkfile.is_open())
    {
        cout << " there is an existing file with that name: " << filename << endl;
        return;
    }
    checkfile.close();

    ofstream file(filename + ".txt");

    file << "// board informations" << endl;
    file << "x:" << (BOARDCOLUMNS - 1) / 2 << endl;
    file << "y:" << (BOARDROWS - 1) / 2 << endl;
    file << "z:" << zombies.size() << endl;

    file << "// Alien informations" << endl;
    file << alien.x << ","
         << alien.y << ","
         << alien.attack << ","
         << alien.life << ","
         << alien.direction << endl;

    file << "// zombies informations" << endl;
    for (int i = 0; i < zombies.size(); i++)
    {
        file << zombies[i].id << ","
             << zombies[i].x << ","
             << zombies[i].y << ","
             << zombies[i].attack << ","
             << zombies[i].life << ","
             << zombies[i].range << endl;
    }

    file << "// board informations" << endl;

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            file << board[i][j];
        }
        file << endl;
    }

    cout << " The game has been saved successfully in file : " << filename << ".txt" << endl;
    file.close();
}

vector<string> splitString(string input, char delimiter)
{
    vector<string> output;
    stringstream ss(input);
    string token;
    while (getline(ss, token, delimiter))
    {
        output.push_back(token);
    }
    return output;
}

void loadGame(string filename, Alien &alien, vector<Zombie> &zombies, vector<vector<char>> &board)
{
    filename = filename + ".txt";
    ifstream file(filename);
    string line;

    int zombie_count = 0;

    if (file.is_open())
    {

        getline(file, line);
        getline(file, line);
        BOARDCOLUMNS = stoi(line.substr(2));

        getline(file, line);
        BOARDROWS = stoi(line.substr(2));

        getline(file, line);
        ZOMBIESNUM = stoi(line.substr(2));

        getline(file, line);
        getline(file, line);
        vector<string> alien_info = splitString(line, ',');
        try
        {
            alien.x = stoi(alien_info[0]);
        }
        catch (const std::invalid_argument &e)
        {
            cout << "Error converting string to integer: " << alien_info[0] << endl;
        }
        try
        {
            alien.y = stoi(alien_info[1]);
        }
        catch (const std::invalid_argument &e)
        {
            cout << "Error converting string to integer: " << alien_info[1] << endl;
        }
        try
        {
            alien.attack = stoi(alien_info[2]);
        }
        catch (const std::invalid_argument &e)
        {
            cout << "Error converting string to integer: " << alien_info[2] << endl;
        }
        try
        {
            alien.life = stoi(alien_info[3]);
        }
        catch (const std::invalid_argument &e)
        {
            cout << "Error converting string to integer: " << alien_info[3] << endl;
        }

        alien.direction = alien_info[4][0];
        zombies.clear();

        getline(file, line);
        while (zombie_count < ZOMBIESNUM)
        {
            getline(file, line);
            Zombie zombie;
            vector<string> zombie_info = splitString(line, ',');

            try
            {
                zombie.id = stoi(zombie_info[0]);
            }
            catch (const std::invalid_argument &e)
            {
                cout << "Error converting string to integer: " << zombie_info[0] << endl;
            }
            try
            {
                zombie.x = stoi(zombie_info[1]);
            }
            catch (const std::invalid_argument &e)
            {
                cout << "Error converting string to integer: " << zombie_info[1] << endl;
            }
            try
            {
                zombie.y = stoi(zombie_info[2]);
            }
            catch (const std::invalid_argument &e)
            {
                cout << "Error converting string to integer: " << zombie_info[2] << endl;
            }
            try
            {
                zombie.attack = stoi(zombie_info[3]);
            }
            catch (const std::invalid_argument &e)
            {
                cout << "Error converting string to integer: " << zombie_info[3] << endl;
            }
            try
            {
                zombie.life = stoi(zombie_info[4]);
            }
            catch (const std::invalid_argument &e)
            {
                cout << "Error converting string to integer: " << zombie_info[4] << endl;
            }
            try
            {
                zombie.range = stoi(zombie_info[5]);
            }
            catch (const std::invalid_argument &e)
            {
                cout << "Error converting string to integer: " << zombie_info[5] << endl;
            }

            zombies.push_back(zombie);
            zombie_count++;
        }

        BOARDCOLUMNS = (BOARDCOLUMNS * 2) + 1;
        BOARDROWS = (BOARDROWS * 2) + 1;

        board = getBoard();

        getline(file, line);
        for (int i = 0; i < BOARDCOLUMNS; i++)
        {
            getline(file, line);

            for (int j = 0; j < BOARDROWS; j++)
            {

                board[i][j] = line[j];
            }
        }
        cout << "The file has been successfully read" << endl;
        system("pause");
        system("CLS");
        placeZombies(zombies, board);
        placeAlien(alien, board);
        displayBoard(board);
        displayStatus(alien, zombies);
    }
    else
    {
        cout << "\tworong file name \n";
    }
}

void resetObjects(vector<vector<char>> &board)
{
    for (int i = 0; i < BOARDROWS; i++)
    {
        for (int j = 0; j < BOARDCOLUMNS; j++)
        {
            if (board[i][j] == '.')
            {
                // reset the trail to a random object
                board[i][j] = getRandomObject();
            }
        }
    }
}
void gamePlay()
{
    Alien alien;
    vector<Zombie> zombies;
    vector<vector<char>> board;

    system("cls");
    setGameSettings();
    board = getBoard();
    initializePlayers(alien, zombies);
    initializeBoard(alien, zombies, board);
    displayBoard(board);
    displayStatus(alien, zombies);
    while (true)
    {
        NOWTURN = 0;
        bool moveable = false;
        if (alien.life <= 0)
        {
            cout << "You are dead!" << endl;
            cout << "Thank You For Playing" << endl;
            break;
        }
        while (!moveable)
        {
            moveable = inputCommand(alien, zombies, board);
            system("pause");
        }
        alienGame(alien, board, zombies);
        system("pause");
        system("CLS");
        displayBoard(board);
        displayAlien(alien, board);
        displayStatus(alien, zombies);
        cout << "Alein turn ended" << endl;
        system("pause");
        cout << "reset trail" << endl;
        system("pause");
        resetObjects(board);

        for (auto i = 0; i < zombies.size(); i++)
        {
            NOWTURN++;
            // displayStatus(alien, zombies);
            zombiesGame(alien, board, zombies[i]);
            system("pause");
            system("CLS");
            displayBoard(board);
            displayAlien(alien, board);
            displayStatus(alien, zombies);
        }
        if (checkWin(zombies))
        {
            cout << "You Win!" << endl;
            cout << "Thank You For Playing" << endl;
            system("pause");
            exit(0);
        }
    }
}

int main()
{
    gamePlay();
}
// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT9L
// Names: mohamed mamoun mohamed|Alharthi, Hamzah Hamed S 
// IDs: 1211306306 |1211305485
// Emails: mohamed1161901324@gmail.com| 1211305485@student.mmu.edu.my
// Phones: 01161901324|01127880328
// *********************************************************
