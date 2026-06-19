#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

char board[3][3];
char currentPlayer;

void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << "   ";
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 'X') {
                cout << RED << " X " << RESET;
            } else if (board[i][j] == 'O') {
                cout << BLUE << " O " << RESET;
            } else {
                cout << " " << (i*3 + j + 1) << " ";
            }
            if (j < 2) cout << CYAN << "│" << RESET;
        }
        cout << endl;
        if (i < 2) cout << CYAN << "  ───┼───┼───" << RESET << endl;
    }
    cout << "\n";
}

bool isFull() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') return false;
    return true;
}

bool checkWin(char player) {
    // Rows & Columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    // Diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

int minimax(bool isMaximizing) {
    if (checkWin('O')) return 10;
    if (checkWin('X')) return -10;
    if (isFull()) return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int score = minimax(false);
                    board[i][j] = ' ';
                    if (score > bestScore) bestScore = score;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int score = minimax(true);
                    board[i][j] = ' ';
                    if (score < bestScore) bestScore = score;
                }
            }
        }
        return bestScore;
    }
}

pair<int, int> bestMove() {
    int bestScore = -1000;
    pair<int, int> move = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int score = minimax(false);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    move = {i, j};
                }
            }
        }
    }
    return move;
}

int main() {
    srand(time(0));
    cout << "=== Tic-Tac-Toe with Unbeatable AI ===\n";
    cout << "You are X (Red), Computer is O (Blue)\n\n";

    char playAgain;
    do {
        initializeBoard();
        currentPlayer = 'X';

        while (true) {
            printBoard();

            if (currentPlayer == 'X') {
                int choice;
                cout << "Enter position (1-9): ";
                cin >> choice;

                if (choice < 1 || choice > 9) {
                    cout << "Invalid move! Try again.\n";
                    continue;
                }

                int row = (choice - 1) / 3;
                int col = (choice - 1) % 3;

                if (board[row][col] != ' ') {
                    cout << "Position already taken!\n";
                    continue;
                }

                board[row][col] = 'X';
            } else {
                cout << "Computer thinking...\n";
                pair<int, int> aiMove = bestMove();
                if (aiMove.first != -1) {
                    board[aiMove.first][aiMove.second] = 'O';
                }
            }

            if (checkWin(currentPlayer)) {
                printBoard();
                if (currentPlayer == 'X')
                    cout << GREEN << "🎉 You Win!\n" << RESET;
                else
                    cout << RED << "💻 Computer Wins!\n" << RESET;
                break;
            }

            if (isFull()) {
                printBoard();
                cout << YELLOW << "It's a Draw!\n" << RESET;
                break;
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing!\n";
    return 0;
}