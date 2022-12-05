#ifndef OTHELLO_H_INCLUDED
#define OTHELLO_H_INCLUDED

//DEFINE GLOBAL CONSTANTS 
#define TRUE 1
#define FALSE 0 
#define NAME 20
#define ROW 8
#define COL 8
#define SPACE ' '
#define PLAYER_X 1
#define PLAYER_O 2
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define EIGHT 8
#define INVALID -1
#define MIN 0
#define MAX 7
#define SQUARES 64

struct Player {
    int playerNum;
    char playerName[20];
    int discCount;
    char playChar;
};

//Function prototypes
void welcomeScreen();
void clearScreen();
void displayExplicitBoard();
void playGame();
void initializeBoard(char[ROW][COL]);
void displayBoard(char[ROW][COL]);
void makeMove(struct Player*, char[ROW][COL]);
int isValid(char[THREE], char[ROW][COL], struct Player*);
int getMoveRow(char[THREE]);
int getMoveCol(char[THREE]);
int isOpen(char[THREE], char[ROW][COL]);
void displayStats(struct Player);
int isOutFlank(char[THREE], char[ROW][COL], char);
int checkHorizontal(int, int, char[ROW][COL], char);
int checkVertical(int, int, char[ROW][COL], char);
int checkDiagonal(int, int, char[ROW][COL], char);
void updateBoard(char[THREE], char[ROW][COL], struct Player*);
void updateHorizontal(int, int, char[ROW][COL], struct Player*);
void updateVertical(int, int, char[ROW][COL], struct Player*);
void updateDiagonal(int, int, char[ROW][COL], struct Player*);
void updateDiscCount(char[ROW][COL], struct Player*);
int isEndGame(char [ROW][COL]);
int getDiscCount(char [ROW][COL]);
int validMoveExists(char [ROW][COL], char);
void gameOver(char [ROW][COL], struct Player*, struct Player*);
void setFullBoard(char [ROW][COL]);
void setNoMoveBoard(char [ROW][COL]);

#endif