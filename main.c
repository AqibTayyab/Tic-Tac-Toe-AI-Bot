#include <stdio.h>
#include <limits.h>

#define PLAYER 'X'
#define AI 'O'

char board[3][3];

// Function prototypes
void initializeBoard();
void printBoard();
int isMovesLeft();
int evaluate();
int minimax(int depth, int isMax);
void findBestMove();
void playerMove();

// Initialize the board
void initializeBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

// Print the board
void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

// Check if moves are left
int isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 1;
    return 0;
}

// Evaluate board state
int evaluate() {
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == AI) return +10;
            else if (board[row][0] == PLAYER) return -10;
        }
    }

    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == AI) return +10;
            else if (board[0][col] == PLAYER) return -10;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == AI) return +10;
        else if (board[0][0] == PLAYER) return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == AI) return +10;
        else if (board[0][2] == PLAYER) return -10;
    }

    return 0;
}

// Minimax algorithm
int minimax(int depth, int isMax) {
    int score = evaluate();
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!isMovesLeft()) return 0;

    if (isMax) {
        int best = INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = AI;
                    best = (best > minimax(depth + 1, 0)) ? best : minimax(depth + 1, 0);
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = PLAYER;
                    best = (best < minimax(depth + 1, 1)) ? best : minimax(depth + 1, 1);
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// Find the best move for AI
void findBestMove() {
    int bestVal = INT_MIN, row = -1, col = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = AI;
                int moveVal = minimax(0, 0);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    row = i; col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    board[row][col] = AI;
}

// Player's move
void playerMove() {
    int x, y;
    do {
        printf("Enter row and column (1-3) separated by space: ");
        scanf("%d %d", &x, &y);
        x--; y--;
    } while (x < 0 || x > 2 || y < 0 || y > 2 || board[x][y] != ' ');
    board[x][y] = PLAYER;
}

// Main function
int main() {
    initializeBoard();
    printBoard();

    while (isMovesLeft() && evaluate() == 0) {
        playerMove();
        printBoard();
        if (evaluate() != 0 || !isMovesLeft()) break;
        findBestMove();
        printBoard();
    }

    int finalScore = evaluate();
    if (finalScore == 10) printf("AI Wins!\n");
    else if (finalScore == -10) printf("You Win!\n");
    else printf("It's a Draw!\n");

    return 0;
}
