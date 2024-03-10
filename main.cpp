/**
 *  MUSTAFA BATIN EFE
 *  Stackgammon Game
 */

#include "cmake-build-debug/Board.h"
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Random number generation helper function
 */
int mypower(int a, int b, int m)
{
    int res = 1;
    a = a % m;
    for(int i=1 ; i<=b ; ++i)
        res = (res * a) % m;
    return res;
}

/**
 * @brief Random number generation function
 *
 * @param seed
 * @return randnum
 */
int  rand_CS(int seed)
{
    static int recurseed = seed;
    int randnum = mypower (393, recurseed, 15307) % 4 +1;
    recurseed = recurseed*2 % 15307;
    return randnum;
}

int main()
{
    // Initializations
    string inputLine;
    bool invalidStr = false;
    Board futureTavla;
    char plyChr;
    int roundCount = 0, finalRound = 10, gameOutcome = -1,
            rngSeed = 1, die = -1, choice = 0, right = 1,
            targetInd = 0;
    // Fine programmer art :)
    cout << "   _____ __             __                                             \n"
            "  / ___// /_____ ______/ /______ _____ _____ ___  ____ ___  ____  ____ \n"
            "  \\__ \\/ __/ __ `/ ___/ //_/ __ `/ __ `/ __ `__ \\/ __ `__ \\/ __ \\/ __ \\\n"
            " ___/ / /_/ /_/ / /__/ ,< / /_/ / /_/ / / / / / / / / / / / /_/ / / / /\n"
            "/____/\\__/\\__,_/\\___/_/|_|\\__, /\\__,_/_/ /_/ /_/_/ /_/ /_/\\____/_/ /_/ \n"
            "                         /____/                                        " << endl;
    cout << "[*] Welcome to the Stackgammon Game!" << endl;
    do {
        invalidStr  = false;
        cout << "[*] Enter a board configuration:" << endl;
        cin >> inputLine;
        // Parsing the string for static syntax checking
        for (int i = 0; i < inputLine.length(); i++) {
            if((49 <= int(inputLine[i])) && (int(inputLine[i]) <= 51))  // Values between 1 and 3 [both inclusive]
            {
                if(i == inputLine.length()-1) // The last value
                {
                    invalidStr = true;
                }
                else {
                    if (!((inputLine[i + 1] == 'x') || (inputLine[i + 1] == 'o'))) { // Next value not equal to x or o
                        invalidStr = true;
                    }
                    else
                    {
                        i+=1;
                    }
                }
            }
            else if(inputLine[i] == '/')
            {
                continue;
            }
            else
            {
                invalidStr = true;
            }
        }
        if(invalidStr)
        {
            cout << "[!] Board configuration invalid! Try again..." << endl;
        }
    } while (invalidStr);  // Check if the board config is valid, if so construct the board. If board config not valid print an error message.

    // Parse the string and initialize the board object
    for (int i = 0; i < inputLine.length(); i++)
    {
        int numChrs = 0;
        char sltChr = ' ';
        if((49 <= int(inputLine[i])) && (int(inputLine[i]) <= 51))  // Values between 1 and 3 [both inclusive]
        {
            numChrs = int(inputLine[i]) - 48;                       // set the value
            i += 1;
            sltChr = inputLine[i];                                  // set the char to the next char
            i += 1;
        }
        if(sltChr == ' ')   // It is a seperator '/' (sltChr is set to x or o if the above if() executes)
        {
            futureTavla.createEmptySlotEnd();
        }
        else                // It is either x or o
        {
            futureTavla.createSlotEnd(sltChr,numChrs);
        }
        if ((inputLine[i] == '/') && (i==inputLine.length()-1)) // If there is a final seperator there should be another empty slot
        {
            futureTavla.createEmptySlotEnd(); // Create Empty Slot End
        }
    }

    futureTavla.printBoard();

    // Enter a round limit
    cout << "[*] Enter a round limit:" << endl;
    cin >> finalRound;

    // Enter a die seed
    cout << "[*] Enter a random number generator seed:" << endl;
    cin >> rngSeed;

    // Run the game until the round limit
    while(roundCount < finalRound)
    {
        cout << "[*] Round " << roundCount << endl;
        // x starts first
        cout << "[x] X's turn:" << endl;
        plyChr = 'x';
        cout << "Throwing die..." << endl;
        die = rand_CS(rngSeed);                 // Pseudo random number generation between [1-4]
        cout << "Die is " << die << "." << endl;
        if(futureTavla.noMove(plyChr, die))         // Check if there are any possible moves
        {
            cout << "[x] You have no legal moves! Choose to append at start (1) or at the end (0):" << endl;
            cin >> choice;
            if(choice == 1)
            {
                futureTavla.createSlotBegin(plyChr,1);
            }
            else
            {
                futureTavla.createSlotEnd(plyChr,1);
            }
        }
        else
        {
            // There is at least one move to make
            bool possibleMove = false;
            while (!possibleMove) {
                cout << "[x] Make your move. State the index (starts from 0) of your piece you want to move, and right (1) or left (0):" << endl;
                cin >> choice;
                cin >> right;
                int moveOutcome = futureTavla.validMove(plyChr, choice, die, right);    // Is the user input move possible to execute
                if(moveOutcome == 0)
                {
                    if(right == 1)
                    {
                        targetInd = choice + die;
                    }
                    else
                    {
                        targetInd = choice - die;
                    }
                    futureTavla.movePiece(choice, targetInd);
                    if (futureTavla.targetSlotFull(targetInd))
                    {
                        futureTavla.destroySlot(targetInd);     // Delete the full slot
                    }
                    possibleMove = true;
                }
                else
                {
                    // print error messages
                    if(moveOutcome == 1)
                    {
                        cout << "[!] Choice index out of bounds. Try again..." << endl;
                    }
                    else if(moveOutcome == 2)
                    {
                        cout << "[!] Target index out of bounds. Try again..." << endl;
                    }
                    else if(moveOutcome == 3)
                    {
                        cout << "[!] Target index not available. Try again..." << endl;
                    }
                    else if(moveOutcome == 4)
                    {
                        cout << "[!] Choice index not yours to move! Try again..." << endl;
                    }
                }

            }
        }
        futureTavla.printBoard();
        // o starts second
        cout << "[o] O's turn:" << endl;
        plyChr = 'o';
        cout << "Throwing die..." << endl;              // Pseudo random number generation between [1-4]
        die = rand_CS(rngSeed);
        cout << "Die is " << die << "." << endl;
        if(futureTavla.noMove(plyChr, die))
        {
            cout << "[o] You have no legal moves! Choose to append at start (1) or at the end (0):" << endl;
            cin >> choice;
            if(choice == 1)
            {
                futureTavla.createSlotBegin(plyChr,1);
            }
            else
            {
                futureTavla.createSlotEnd(plyChr,1);
            }
        }
        else
        {
            // There is at least one move to make
            bool possibleMove = false;
            while (!possibleMove) {
                cout << "[o] Make your move. State the index (starts from 0) of your piece you want to move, and right (1) or left (0):" << endl;
                cin >> choice;
                cin >> right;
                int moveOutcome = futureTavla.validMove(plyChr, choice, die, right);    // Is the user input move possible to execute
                if(moveOutcome == 0)
                {
                    if(right == 1)
                    {
                        targetInd = choice + die;
                    }
                    else
                    {
                        targetInd = choice - die;
                    }
                    futureTavla.movePiece(choice, targetInd);
                    if (futureTavla.targetSlotFull(targetInd))
                    {
                        futureTavla.destroySlot(targetInd);     // Delete the full slot
                    }

                    possibleMove = true;
                }
                else
                {
                    // print error messages
                    if(moveOutcome == 1)
                    {
                        cout << "[!] Choice index out of bounds. Try again..." << endl;
                    }
                    else if(moveOutcome == 2)
                    {
                        cout << "[!] Target index out of bounds. Try again..." << endl;
                    }
                    else if(moveOutcome == 3)
                    {
                        cout << "[!] Target index not available. Try again..." << endl;
                    }
                    else if(moveOutcome == 4)
                    {
                        cout << "[!] Choice index not yours to move! Try again..." << endl;
                    }
                }

            }
        }
        futureTavla.printBoard();
        roundCount += 1;
    }

    cout << "[*] Game over!" << endl;

    // Return a game result based on xCnt and oCnt (they are private variables, so evaluateGame() will acccess them and return a result
    gameOutcome = futureTavla.evaluateGame(); // evaluateGame()
    if(gameOutcome == 1)
    {
        cout << "   _  __    _       ___            __\n"
                "  | |/ /   | |     / (_)___  _____/ /\n"
                "  |   /    | | /| / / / __ \\/ ___/ / \n"
                " /   |     | |/ |/ / / / / (__  )_/  \n"
                "/_/|_|     |__/|__/_/_/ /_/____(_)   \n"
                "                                     " << endl;
    }
    else if(gameOutcome == 2)
    {
        cout << "   ____     _       ___            __\n"
                "  / __ \\   | |     / (_)___  _____/ /\n"
                " / / / /   | | /| / / / __ \\/ ___/ / \n"
                "/ /_/ /    | |/ |/ / / / / (__  )_/  \n"
                "\\____/     |__/|__/_/_/ /_/____(_)   \n"
                "                                     " << endl;
    }
    else if(gameOutcome == 3)
    {
        cout << "  _______      __\n"
                " /_  __(_)__  / /\n"
                "  / / / / _ \\/ / \n"
                " / / / /  __/_/  \n"
                "/_/ /_/\\___(_)   \n"
                "                 " << endl;
    }
    futureTavla.clearBoard();

    return 0;
}