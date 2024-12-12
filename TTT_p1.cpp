/*
Nick Spizzirri
CSC122
Portfolio 2 Battle TTT
*/
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include<fstream>
#include <cstdlib>
using namespace std;

char sQ[9];
bool pyromancerUsed[2] = { false, false };
int gameCount = 0;
int pXWins = 0;
int pOWins = 0;
int drawCount = 0;

void tttboard()
{
    cout << "\t\t" << sQ[0] << "\t" << "|" << "\t" << sQ[1] << "\t" << "|" << "\t" << sQ[2] << endl;
    cout << "\t----------------+---------------+----------------" << endl;
    cout << "\t\t" << sQ[3] << "\t" << "|" << "\t" << sQ[4] << "\t" << "|" << "\t" << sQ[5] << endl;
    cout << "\t----------------+---------------+----------------" << endl;
    cout << "\t\t" << sQ[6] << "\t" << "|" << "\t" << sQ[7] << "\t" << "|" << "\t" << sQ[8] << endl;
}

void welcomeMsg() {
    cout << "                                                          " << endl;
    cout << " _ _ _ _____ __    _____ _____ _____ _____    _____ _____ " << endl;
    cout << "| | | |   __|  |  |     |     |     |   __|  |_   _|     |" << endl;
    cout << "| | | |   __|  |__|   --|  |  | | | |   __|    | | |  |  |" << endl;
    cout << "|_____|_____|_____|_____|_____|_|_|_|_____|    |_| |_____|" << endl;
    cout << " _________  ___  ________          _________  ________  ________     " << endl;
    cout << "|\\___   ___\\\\  \\|\\   ____\\        |\\___   ___\\\\   __  \\|\\   ____\\    " << endl;
    cout << "\\|___ \\  \\_\\ \\  \\ \\  \\___|        \\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\___|    " << endl;
    cout << "     \\ \\  \\ \\ \\  \\ \\  \\                \\ \\  \\ \\ \\   __  \\ \\  \\       " << endl;
    cout << "      \\ \\  \\ \\ \\  \\ \\  \\____            \\ \\  \\ \\ \\  \\ \\  \\ \\  \\____  " << endl;
    cout << "       \\ \\__\\ \\ \\__\\ \\_______\\           \\ \\__\\ \\ \\__\\ \\__\\ \\_______\\ " << endl;
    cout << "        \\|__|  \\|__|\\|_______|            \\|__|  \\|__|\\|__|\\|_______|" << endl;
    cout << "                                                                     " << endl;
    cout << "                                                                     " << endl;
    cout << "                    _________  ________  _______   ___               " << endl;
    cout << "                   |\\___   ___\\\\   __  \\|\\  ___ \\ |\\  \\              " << endl;
    cout << "                   \\|___ \\  \\_\\ \\  \\|\\  \\ \\   __/|\\ \\  \\             " << endl;
    cout << "                        \\ \\  \\ \\ \\  \\\\\\  \\ \\  \\_|/_\\ \\  \\            " << endl;
    cout << "                         \\ \\  \\ \\ \\  \\\\\\  \\ \\  \\_|\\ \\ \\__\\           " << endl;
    cout << "                          \\ \\__\\ \\ \\_______\\ \\_______\\|__|           " << endl;
    cout << "                           \\|__|  \\|_______|\\|_______|   ___         " << endl;
    cout << "                                                        |\\__\\        " << endl;
    cout << "                                                        \\|__|        " << endl;
    cout << "                                                                     " << endl;
}

void resetBoard() {
    for (int i = 0; i < 9; ++i) {
        sQ[i] = '1' + i;
    }
}

vector<int> checkWin()
{
    vector<vector<int>> winConditions = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (auto& condition : winConditions) {
        char firstBox = sQ[condition[0]];
        if (firstBox != 'O' && firstBox != 'X') {
            continue;
        }
        if (firstBox == sQ[condition[1]] && firstBox == sQ[condition[2]]) {
            return condition;
        }
    }
    return {};
}

int protectData(char player)
{
    bool inputValid = false;
    int choice;
    string Choice;
    while (!inputValid) {
        cout << "\n\nPlayer " << player << ", enter a square #: " << endl;
        getline(cin, Choice);
        if (Choice.length() != 1 || !isdigit(Choice[0])) {
            cout << "\rInvalid input. Please enter a number between 1 and 9." << endl;
            tttboard();
        }
        else {
            choice = stoi(Choice);
            inputValid = true;
        }
    }
    return choice;
}

bool checkSwarmWin(char player) {
    return (sQ[0] == player && sQ[2] == player && sQ[6] == player && sQ[8] == player);
}

void PyroSpecial(char player, int& turnCount) {
    int playerIndex = (player == 'X') ? 0 : 1;
    if (pyromancerUsed[playerIndex]) {
        turnCount--;
        cout << "You've already used your special move! What a waste of a turn.\n";
    }
    else {
        resetBoard();
        turnCount = 0;
        cout << "The Pyromancer has cleared the board!\n";
        pyromancerUsed[playerIndex] = true;
    }
}

void turn(char player, const string& archetype, int& turnCount)
{
    bool inputValid = false;
    int action;
    string Action;
    if (archetype == "Pyromancer") {
        while (!inputValid) {
            cout << "\nPlayer " << player << ", choose your action:\n";
            cout << "1. Regular move\n2. Special move (Clear board)\n";
            getline(cin, Action);
            if (Action.length() != 1 || !isdigit(Action[0])) {
                cout << "Invalid choice. Please enter 1 or 2.\n";
            }
            else {
                action = stoi(Action);
                if (action != 1 && action != 2) {
                    cout << "Invalid choice. Please select 1 or 2.\n";
                    continue;
                }
                if (action == 2) {
                    PyroSpecial(player, turnCount);
                    return;
                }
                break;
            }
        }
    }
    while (true) {
        int choice = protectData(player);
        char tile = choice + 48;
        if (sQ[choice - 1] == tile) {
            sQ[choice - 1] = player;
            break;
        }
        else {
            cout << "You can't pick that square, silly." << endl;
            tttboard();
        }
    }
}

string selectArchetype(char player) {
    bool inputValid = false;
    string archetype;
    while (!inputValid) {
        cout << "\nPlayer " << player << ", select your archetype:\n";
        cout << "1. Swarm - Wins with all four corners in addition to regular rules.\n";
        cout << "2. Pyromancer - Can clear the board once per game.\n";
        cout << "Enter your choice (1 or 2): ";
        int choice;
        string Choice;
        getline(cin, Choice);
        if (Choice.length() != 1 || !isdigit(Choice[0])) {
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
        else {
            if (Choice[0] != '1' && Choice[0] != '2') {
                cout << "Invalid choice. Please enter 1 or 2.\n";
            }
            else {
                choice = stoi(Choice);
                archetype = (choice == 1) ? "Swarm" : "Pyromancer";
                inputValid = true;
            }
        }
    }
    return archetype;
}

void gameLoop(const string& gameMode) {
    vector<int> winningBoxes;
    char currentPlayer = 'X';
    string archetypes[2];
    if (gameMode == "Battle") {
        archetypes[0] = selectArchetype('X');
        archetypes[1] = selectArchetype('O');
    }
    resetBoard();
    for (int turnCount = 1; turnCount < 10; ++turnCount) {
        tttboard();
        turn(currentPlayer, gameMode == "Battle" ? archetypes[currentPlayer == 'X' ? 0 : 1] : "Regular", turnCount);
        winningBoxes = checkWin();
        if (!winningBoxes.empty() || (gameMode == "Battle" && checkSwarmWin(currentPlayer))) {
            tttboard();
            cout << "\nPlayer " << currentPlayer << " wins!\n";
            if (currentPlayer == 'X') {
                pXWins++;
            }
            else {
                pOWins++;
            }
            return;
        }
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
    tttboard();
    cout << "\nIt's a draw!\n";
    drawCount++;
}

void createScoreSheet() {
    ofstream scoreSheet;
    scoreSheet.open("TTTwins.txt", ios::out);
    if (!scoreSheet) {
        cerr << "Error opening File";
        exit(EXIT_FAILURE);
    }
    scoreSheet << "*** TIC-TAC-TOE SCORE SHEET ***\n\nGames played: " << gameCount << "\n\nPlayer X win count: " << pXWins << "\n\nPlayer O win count: " << pOWins << "\n\nDraw count: " << drawCount;
    scoreSheet.close();
    system("start TTTWins.txt");
}

int main() {
    welcomeMsg();
    while (true) {
        int choice;
        string Choice;
        bool inputValid = false;
        pyromancerUsed[0] = { false };
        pyromancerUsed[1] = { false };
        while (!inputValid) {
            gameCount++;
            cout << "\nSelect Game Mode:\n";
            cout << "1. Regular Tic-Tac-Toe\n";
            cout << "2. Battle Tic-Tac-Toe\n";
            cout << "Enter your choice (1 or 2): ";
            getline(cin, Choice);
            if (Choice.length() != 1 || !isdigit(Choice[0])) {
                cout << "Invalid choice. Please enter 1 or 2.\n";
            }
            else {
                if (Choice[0] != '1' && Choice[0] != '2') {
                    cout << "Invalid choice. Please enter 1 or 2.\n";
                }
                else {
                    choice = stoi(Choice);
                    inputValid = true;
                }
            }
        }
        string gameMode = (choice == 1) ? "Regular" : "Battle";
        gameLoop(gameMode);
        cout << "\nWould you like to play again? (Y/N): ";
        char replay;
        cin >> replay;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (replay != 'Y' && replay != 'y') {
            cout << "Thank you for playing!\n";
            break;
        }
    }
    createScoreSheet();
    return 0;
}
