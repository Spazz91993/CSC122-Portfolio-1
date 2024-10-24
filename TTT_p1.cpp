/*
Nick Spizzirri
CSC122
Portfolio 1 TTT
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;
char sQ[9];
void tttboard()
{
    cout << "\t\t" << sQ[0] << "\t" << "|" << "\t" << sQ[1] << "\t" << "|" << "\t" << sQ[2] << endl;
    cout << "\t----------------+---------------+----------------" << endl;
    cout << "\t\t" << sQ[3] << "\t" << "|" << "\t" << sQ[4] << "\t" << "|" << "\t" << sQ[5] << endl;
    cout << "\t----------------+---------------+----------------" << endl;
    cout << "\t\t" << sQ[6] << "\t" << "|" << "\t" << sQ[7] << "\t" << "|" << "\t" << sQ[8] << endl;
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
            cout << "\rTry a valid square 1-9." << endl;
            tttboard();
        }
        else {
            choice = stoi(Choice);
            inputValid = true;
        }
    }
    return choice;
}
void turn(char player)
{
    int choice;
    choice = protectData(player);
    char tile = choice + 48;
    if (sQ[choice - 1] == tile) {
        sQ[choice - 1] = player;
    }
    else {
        cout << "You can't pick that square, silly." << endl;
        tttboard();
        turn(player);
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
void resetBoard() {
    for (int i = 0; i < 9; ++i) {
        sQ[i] = '1' + i;
    }
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


int main() {
    char Reset = 'Y';
    vector<int> winningBoxes;
    welcomeMsg();
    while (Reset == 'Y' || Reset == 'y') {
        bool gameEnd = false;
        char currentPlayer = 'X';
        resetBoard();
        for (int turnCount = 0; turnCount < 9 && !gameEnd; ++turnCount) {
            tttboard();
            turn(currentPlayer);
            winningBoxes = checkWin();
            if (!winningBoxes.empty()) {
                gameEnd = true;
            }
            if (currentPlayer == 'O') {
                currentPlayer = 'X';
            }
            else {
                currentPlayer = 'O';
            }
        }
        tttboard();
        if (!winningBoxes.empty()) {
            char winner = sQ[winningBoxes[0]];
            cout << "\nPlayer " << winner << " wins!" << endl;
            cout << "\nWinning combination: ";
            for (int i = 0; i < 3; ++i) {
                cout << winningBoxes[i] + 1;
                if (i < 2) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        else {
            cout << "It's a draw!" << endl;
        }
        cout << "\nWould you like to play again?\n\nPress Y to play again, or any other key to exit: " << endl;
        cin >> Reset;
    }
    return 0;
}