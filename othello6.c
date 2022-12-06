//Include libaries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "othello.h"


//Main function
int main() {
    //Calls welcomeScreen function 
    welcomeScreen();
    //Calls clearScreen function 
    clearScreen();
    //Calls displayExplicitBoard function
    //displayExplicitBoard();

    //Calls playGame function to start game
    playGame();

    //Returns 0 to ensure program runs successfully
    return 0;
}

//Displays set of instructions to user
void welcomeScreen() {

    // Prints Welcome screen (12 lines)
    printf ("\t\t OOOO  TTTTTT HH  HH EEEEEE LL      LL      OOOO  \n");
    printf ("\t\tOO  OO   TT   HH  HH EE     LL      LL     OO  OO \n");
    printf ("\t\tOO  OO   TT   HHHHHH EEEE   LL      LL     OO  OO \n");
    printf ("\t\tOO  OO   TT   HH  HH EE     LL      LL     OO  OO \n");
    printf ("\t\t OOOO    TT   HH  HH EEEEEE LLLLLLL LLLLLL  OOOO  \n");
    printf ("\n\n");//
    printf("Othello Game Rules:\n");
    printf("1. A square 8 x 8 board\n");
    printf("2. 64 discs colored black (X) on one side and white (O) on the opposite site.\n");
    printf("3. The board will start with 2 black discs (X) and 2 white discs (O) at the center of the board.\n");
    printf("4. They are arranged with black (X) forming a North-East to South-West direction. White (O) is forming a North-West to South-East direction\n");
    printf("5. The goal is to get the majority of the color discs on the board at the end of the game\n");
    printf("6. Each player gets 32 discs and black (X) always starts the game\n");
    printf("7. The game alternates between white and black (X) until one player can not make a valid move to outflank the opponent or both players have no valid moves.\n");
    printf("8. When a player has no valid moves, they pass their turn and the opponent continues.\n");
    printf("9. A player cannot voluntarily forfeit their turn.\n");
    printf("10. When both players can not make a valid move the game ends.\n");


}

//Clears screen when user presses <enter>
void clearScreen() {
    //Prompts user to press <enter> to clear screen
    printf("\n\nPress <enter> to continue!\n");
    //Scans for user input for "<enter>"
    char enter;
    scanf("%c", &enter);
    //Clears screen (Windows)
    system("cls");
    //Clears screen (Mac)
    //system("clear");

}

//Displays gameboard to user

//LEGACY BOARD FOR ASSIGNMENTS 1 & 2
void displayExplicitBoard() {
    // Prints gameboard (11 lines) 
    printf("|-----------------------------------|\n");
    printf("|   | A | B | C | D | E | F | G | H |\n");
    printf("| 1 |   |   |   |   |   |   |   |   |\n");
    printf("| 2 |   |   |   |   |   |   |   |   |\n");
    printf("| 3 |   |   |   |   |   |   |   |   |\n");
    printf("| 4 |   |   |   | O | X |   |   |   |\n");
    printf("| 5 |   |   |   | X | O |   |   |   |\n");
    printf("| 6 |   |   |   |   |   |   |   |   |\n");
    printf("| 7 |   |   |   |   |   |   |   |   |\n");
    printf("| 8 |   |   |   |   |   |   |   |   |\n");
    printf("|-----------------------------------|\n"); 
}

//Starts game
void playGame() {
    struct Player playerX;
    struct Player playerO;
    playerX.playerNum = PLAYER_X;
    playerO.playerNum = PLAYER_O;
    playerX.discCount = 2;
    playerO.discCount = 2;

    int endGame = FALSE;
    int currentPlayer = PLAYER_X;
    // int loop = ZERO; OLD LOOP COUNTER
    char board[ROW][COL];

    //Asks Players for their names and stores their names to be outputted later
    printf("\nPlayer X, please input your name.\nInput: ");
    scanf("%s", playerX.playerName);
    playerX.playChar = 'X';
    printf("\nPlayer O, please input your name.\nInput: ");
    scanf("%s", playerO.playerName);
    playerO.playChar = 'O';
    printf("\nHello %s and %s! Lets play Othello!\n\n", playerX.playerName, playerO.playerName);

    initializeBoard(board);
    //Loops eight times to allow for eight moves in the game
    while(endGame == FALSE) {
        endGame = isEndGame(board);
        if (endGame == TRUE) {
            gameOver(board, &playerX, &playerO);
            break;
        }
        displayBoard(board);
        if(currentPlayer == PLAYER_X) {
            if (validMoveExists(board, playerO.playChar) == TRUE) {
                makeMove(&playerX, board);
            }
            currentPlayer = PLAYER_O;
        }
        else if(currentPlayer == PLAYER_O) {
            if (validMoveExists(board, playerX.playChar) == TRUE) {
                makeMove(&playerO, board);
            }
            currentPlayer = PLAYER_X;
        }
        updateDiscCount(board, &playerX);
        displayStats(playerX);
        updateDiscCount(board, &playerO);
        displayStats(playerO);

        // loop++; OLD LOOP INCREMENT
    }
    return;
}

//Creates starting board
void initializeBoard(char board[ROW][COL]) {
    for(int r = 0; r < ROW; r++) {
        for(int c = 0; c < COL; c++) {
            if((r==THREE&&c==THREE)||(r==FOUR&&c==FOUR)) 
                board[r][c] = 'O';
            else if((r==THREE&&c==FOUR)||(r==FOUR&&c==THREE)) 
                board[r][c] = 'X';
            else 
                board[r][c] = SPACE;
        }
    }
    return;
}

//Displays updated board each time board is called
void displayBoard(char board[ROW][COL]) {
    printf("|-----------------------------------|\n");
    printf("|   | A | B | C | D | E | F | G | H |\n");
    for(int r = 0; r < ROW; r++) {
        printf("| %d |", r+1);
        for(int c = 0; c < COL; c++) {
            printf(" %c |", board[r][c]);
        }
        printf("\n");
    }
    printf("|-----------------------------------|\n");
    return;
}

//Processes user input and checks for user input errors
void makeMove(struct Player *player, char board[ROW][COL]) {
    char move[THREE];
    int valid = FALSE;

    while(valid == FALSE) {
        printf("\n%s (Player %c), it's your turn. Input your move location. (Ex: B6)\nInput: ", player->playerName, player->playChar);
        scanf("%s", move);
        printf("\n%s entered %s.\n", player->playerName, move);
        
        //Clears user output after each output to avoid errors
        getchar();
        fflush(stdin);

        //Checks if user input is valid
        int length = strlen(move);
        valid = (length == TWO && isValid(move, board, player)) ? TRUE : FALSE;
        if (valid == FALSE) {
            printf("%s, invalid move.\n", player->playerName);
        }
        else if (valid == TRUE) {
            printf("%s, valid move!\n", player->playerName);
        }
    }
    return;
}

//Checks if user input is valid given input length is 2 characters
int isValid(char move[THREE], char board[ROW][COL], struct Player *player) {
    int valid = FALSE;
    valid = isOpen(move, board);
    if (valid == FALSE) {
        return valid;
    }
    valid = isOutFlank(move, board, player->playChar);
    if (valid == FALSE) {
        return valid;
    }
    updateBoard(move, board, player);
    return valid;
}

//Checks if user's choice is open in the board
int isOpen(char move[THREE], char board[ROW][COL]) {
    int open = FALSE;
    int rowInt = getMoveRow(move);
    int colInt = getMoveCol(move);
    open = (rowInt != INVALID && colInt != INVALID && board[rowInt][colInt] == SPACE) ? TRUE : FALSE;
    return open;
}

//Returns back inputted col converted to an index of board if input was between A-H
//Uses Char subtraction, A = 65, if user inputted A, colIndex = 0.
int getMoveCol(char move[THREE]) {
    int colIndex = toupper(move[0])-65;
    return (colIndex>=0&&colIndex<=7) ? colIndex : INVALID;
}

//Returns back inputted row-1 if input was between 1-8
//Uses ASCII Comparsion 1=49,8=56
int getMoveRow(char move[THREE]) {
    return (move[1]>=49&&move[1]<=56) ? move[1]-49 : INVALID;
}

//Displays user stats after each turn
void displayStats(struct Player player) {
    printf("\nPlayer Name: %s\n", player.playerName);
    printf("Player Number: %d\n", player.playerNum);
    printf("Player Discs: %d\n", player.discCount);
    printf("Player Char: %c\n", player.playChar);
    return;
}

//Checks if there is either a horizontal, vertical, or diagonal flank
int isOutFlank(char move[THREE], char board[ROW][COL], char playChar) {
    int flank = FALSE;
    int rowInt = getMoveRow(move);
    int colInt = getMoveCol(move);
    flank = (checkHorizontal(rowInt, colInt, board, playChar) > ZERO ||
             checkVertical(rowInt, colInt, board, playChar) > ZERO ||
             checkDiagonal(rowInt, colInt, board, playChar) > ZERO) ? TRUE : FALSE;
    return flank;
}

//Checks entire horizontal row to see if there is a flank, if there is, the move is valid
int checkHorizontal(int row, int col, char board[ROW][COL], char playerChar) {
    int flank = FALSE;
    int count = 0;
    for (int c = col-1; c >= 0; c--) {
        if (board[row][c] == SPACE) {
            break;
        }
        if (board[row][c] == playerChar) {
            flank = TRUE;
            break;
        }
        if (board[row][c] != playerChar) {
            count++;
        }
    }
    for (int c = col+1; c < COL; c++) {
        if (board[row][c] == SPACE) {
            break;
        }
        if (board[row][c] == playerChar) {
            flank = TRUE;
            break;
        }
        if (board[row][c] != playerChar) {
            count++;
            flank = FALSE;
        }
    }
    return (count > 0 && flank == TRUE) ? count : ZERO;
}

//Checks entire vertical column to see if there is a flank, if there is, the move is valid
int checkVertical(int row, int col, char board[ROW][COL], char playerChar) {
    int flank = FALSE;
    int count = 0;
    for (int r = row-1; r >= 0; r--) {
        if (board[r][col] == SPACE) {
            break;
        }
        if (board[r][col] == playerChar) {
            flank = TRUE;
            break;
        }
        if (board[r][col] != playerChar) {
            count++;
        }
    }
    for (int r = row+1; r < ROW; r++) {
        if (board[r][col] == SPACE) {
            break;
        }
        if (board[r][col] == playerChar) {
            flank = TRUE;
            break;
        }
        if (board[r][col] != playerChar) {
            count++;
            flank = FALSE;
        }
    }
    return (count > 0 && flank == TRUE) ? count : ZERO;
}

//Checks entire diagonal row to see if there is a flank, if there is, the move is valid
int checkDiagonal(int row, int col, char board[ROW][COL], char playerChar) {
    int wasFlank = FALSE;
    int flank = FALSE;
    int count = 0;
    int oldCount = 0;
    //CHECKS DIAGONAL TOP LEFT TO BOTTOM RIGHT
    for (int r = row-1, c = col-1; r >= 0 && c >= 0; r--, c--) {
        if (board[r][c] == SPACE) {
            break;
        }
        if (board[r][c] == playerChar) {
            flank = TRUE;
            break;
        }
        if (board[r][c] != playerChar) {
            count++;
        }
    }
    for (int r = row+1, c = col+1; r < ROW && c < COL; r++, c++) {
        if (board[r][c] == SPACE) {
            break;
        }
        if (board[r][c] == playerChar) {
            flank = TRUE;
            break;
        }
        if (board[r][c] != playerChar) {
            count++;
            flank = FALSE;
        }
    }
    if (flank == FALSE) {
        count = 0;
    }
    else {
        wasFlank = TRUE;
        oldCount = count;
    }
    //CHECKS DIAGONAL TOP RIGHT TO BOTTOM LEFT
    for (int r = row+1, c = col-1; r < ROW && c >= 0; r++, c--) {
        if (board[r][c] == SPACE) {
            break;
        }
        if (board[r][c] == playerChar) {
            flank = TRUE;
            break;
        }
        if (board[r][c] != playerChar) {
            count++;
        }
    }
    for (int r = row-1, c = col+1; r >= 0 && c < COL; r--, c++) {
        if (board[r][c] == SPACE) {
            break;
        }
        if (board[r][c] == playerChar) {
            flank = TRUE;
            break;
        }
        if (board[r][c] != playerChar) {
            count++;
            flank = FALSE;
        }
    }
    return (count > 0 && (flank == TRUE || wasFlank == TRUE)) ? count : ZERO;
}

//Updates board if there is a valid move
void updateBoard(char move[THREE], char board[ROW][COL], struct Player *player) {
    int rowInt = getMoveRow(move);
    int colInt = getMoveCol(move);
    if (checkHorizontal(rowInt, colInt, board, player->playChar) > ZERO) {
        updateHorizontal(rowInt, colInt, board, player);
    }
    if (checkVertical(rowInt, colInt, board, player->playChar) > ZERO) {
        updateVertical(rowInt, colInt, board, player);
    }
    if (checkDiagonal(rowInt, colInt, board, player->playChar) > ZERO) {
        updateDiagonal(rowInt, colInt, board, player);
    }
    board[rowInt][colInt] = player->playChar;
}

//Updates horizontal row if there is a valid horizontal move
void updateHorizontal(int row, int col, char board[ROW][COL], struct Player *player) {
    char playChar = player->playChar;
    int c;
    int count = 0;
    int flank = FALSE;
    //UPDATES HORIZTONAL FROM PLAYER's MOVE TO LEFT 
    for (c = col-1; c >= 0; c--) {
        if (board[row][c] == SPACE) {
            break;
        }
        else if (board[row][c] == playChar) {
            if (count > 0) {
                flank = TRUE;
            }
            break;
        }
        else if (board[row][c] != playChar) {
            count++;
        }
    }
    if (flank == TRUE) {
        for (; c <= col-1; c++) {
            board[row][c] = playChar;
        }
        flank = FALSE;
    }
    count = 0;
    //UPDATES HORIZTONAL FROM PLAYER's MOVE TO RIGHT 
    for (c = col+1; c < COL; c++) {
        if (board[row][c] == SPACE) {
            break;
        }
        else if (board[row][c] == playChar) {
            if (count > 0) {
                flank = TRUE;
            }
            break;
        }
        else if (board[row][c] != playChar) {
            count++;
        }
    }
    if (flank == TRUE) {
        for (; c >= col+1; c--) {
            board[row][c] = playChar;
        }
    }
    return;
}

//Updates vertical column if there is a valid vertical move
void updateVertical(int row, int col, char board[ROW][COL], struct Player *player) {
    char playChar = player->playChar;
    int r; 
    int count = 0;
    int flank = FALSE;
    //UPDATES VERTICAL FROM PLAYER's MOVE TO TOP 
    for (r = row-1; r >= 0; r--) {
        if (board[r][col] == SPACE) {
            break;
        }
        else if (board[r][col] == playChar) {
            if (count > 0) {
                flank = TRUE;
            }
            break;
        }
        else if (board[r][col] != playChar) {
            count++;
        }
    }
    if (flank == TRUE) {
        for (; r <= row-1; r++) {
            board[r][col] = playChar;
        }
        flank = FALSE;
    }
    count = 0;
    //UPDATES VERTICAL FROM PLAYER's MOVE TO BOTTOM 
    for (r = row+1; r < ROW; r++) {
        if (board[r][col] == SPACE) {
            break;
        }
        else if (board[r][col] == playChar) {
            if (count > 0) {
                flank = TRUE;
            }
            break;
        }
        else if (board[r][col] != playChar) {
            count++;
        }
    }
    if (flank == TRUE) {
        for (; r >= row+1; r--) {
            board[r][col] = playChar;
        }
    }
    return;
}

//Updates diagonal row if there is a valid diagonal move
void updateDiagonal(int row, int col, char board[ROW][COL], struct Player *player) {
    char playChar = player->playChar;
    int r; 
    int c;
    int count = 0;
    int flank = FALSE;
    //UPDATES DIAGONAL FROM PLAYER's MOVE TO TOP LEFT
    for (r = row-1, c = col-1; r >= 0 && c >= 0; r--, c--) {
        if (board[r][c] == SPACE) {
            break;
        }
        else if (board[r][c] == playChar) {
            if (count > 0) {
                flank = TRUE;
            }
            break;
        }
        else if (board[r][c] != playChar) {
            count++;
        }
    }
    if (flank == TRUE) {
        for (; r <= row-1 && c <= col-1; r++, c++) {
            board[r][c] = playChar;
        }
        flank = FALSE;
    }
    count = 0;
    //UPDATES DIAGONAL FROM PLAYER's MOVE TO BOTTOM RIGHT
    for (r = row+1, c = col+1; r < ROW && c < COL; r++, c++) {
        if (board[r][c] == SPACE) {
            break;
        }
        else if (board[r][c] == playChar) {
            if (count > 0) {
                flank = TRUE;
            }
            break;
        }
        else if (board[r][c] != playChar) {
            count++;
        }
    }
    if (flank == TRUE) {
        for (; r >= row+1 && c >= col+1; r--, c--) {
            board[r][c] = playChar;
        }
        flank = FALSE;
    }
    count = 0;
    //UPDATES DIAGONAL FROM PLAYER's MOVE TO BOTTOM LEFT
    for (r = row+1, c = col-1; r < ROW && c > 0; r++, c--) {
        if (board[r][c] == SPACE) {
            break;
        }
        else if (board[r][c] == playChar) {
            if (count > 0) {
                flank = TRUE;
            }
            break;
        }
        else if (board[r][c] != playChar) {
            count++;
        }
    }
    if (flank == TRUE) {
        for (; r >= row+1 && c <= col-1; r--, c++) {
            board[r][c] = playChar;
        }
        flank = FALSE;
    }
    count = 0;
    //UPDATES DIAGONAL FROM PLAYER's MOVE TO TOP RIGHT
    for (r = row-1, c = col+1; r >= 0 && c < COL; r--, c++) {
        if (board[r][c] == SPACE) {
            break;
        }
        else if (board[r][c] == playChar) {
            if (count > 0) {
                flank = TRUE;
            }
            break;
        }
        else if (board[r][c] != playChar) {
            count++;
        }
    }
    if (flank == TRUE) {
        for (; r <= row-1 && c >= col+1; r++, c--) {
            board[r][c] = playChar;
        }
    }
    return;
}

//Updates Disc Count to be displayed to user in method displayStats
void updateDiscCount(char board[ROW][COL], struct Player *player) {
    int count = 0;
    char playChar = player->playChar;
    for (int r = 0; r < ROW; r++) {
        for (int c = 0; c < COL; c++) {
            if (board[r][c] == playChar) {
                count++;
            }
        }
    }
    player->discCount = count;
}

//If no valid moves exist, returns TRUE, else FALSE
int isEndGame(char board[ROW][COL]) {
    // setFullBoard(board); //TEST
    // displayBoard(board); //TEST
    if (getDiscCount(board) == SQUARES) {
        return TRUE;
    }
    // setNoMoveBoard(board); //TEST
    // displayBoard(board); //TEST
    return (validMoveExists(board, 'X') == FALSE && validMoveExists(board, 'O') == FALSE) ? TRUE : FALSE;
}

//Get number of discs on board
int getDiscCount(char board[ROW][COL]) {
    int discs = ZERO;
    for (int r = 0; r < ROW; r++) {
        for (int c = 0; c < COL; c++) {
            if (board[r][c] != SPACE) {
                discs++;
            }
        }
    }
    return discs;
}
int validMoveExists(char board[ROW][COL], char playerChar) {
    int spaces = ZERO;
    int result = FALSE;
    for (int r = 0; r < ROW; r++) {
        for (int c = 0; c < COL; c++) {
            if (board[r][c] == SPACE) {
                spaces++;
            }
            if (spaces > 0) {
                if (checkHorizontal(r, c, board, playerChar) == ZERO &&
                    checkVertical(r, c, board, playerChar) == ZERO &&
                    checkDiagonal(r, c, board, playerChar) == ZERO) {
                    
                    result = FALSE;
                }
                else {
                    result = TRUE;
                    break;
                }
            }
        }
        if (result == TRUE) {
            break;
        }
    }
    return result;
}

void gameOver(char board[ROW][COL], struct Player *playerX, struct Player *playerO) {
    printf("*******************************************************\n");
    printf("********************** GAME OVER **********************\n");
    printf("*******************************************************\n");
    displayBoard(board);
    updateDiscCount(board, playerX);
    updateDiscCount(board, playerO);
    displayStats(*playerX);
    displayStats(*playerO);
}


/*
 * PROVIDED TEST CODE
*/


// test end game support function
void setFullBoard(char board[ROW][COL])
{
    for(int row = ZERO; row < ROW; row++)
    {
        for(int col = ZERO; col < COL; col++)
        {
            if(row % TWO == ZERO && col % TWO == ZERO)
                board[row][col] = 'X';
            else
                board[row][col] = 'O';
        }
    }
}

// test end game support function
void setNoMoveBoard(char board[ROW][COL])
{
    // row 0
    // {'X','X','X','X','X','O','X','O'}
    board[0][0] = 'X';
    board[0][1] = 'X';
    board[0][2] = 'X';
    board[0][3] = 'X';
    board[0][4] = 'X';
    board[0][5] = 'O';
    board[0][6] = 'X';
    board[0][7] = 'O';

    // row 1
    // {'O','X','X','O','O','O','X','O'}
    board[1][0] = 'O';
    board[1][1] = 'X';
    board[1][2] = 'X';
    board[1][3] = 'O';
    board[1][4] = 'O';
    board[1][5] = 'O';
    board[1][6] = 'X';
    board[1][7] = 'O';

    // row 2
    // {'X','X','X','X','X','X','X','O'}
    board[2][0] = 'X';
    board[2][1] = 'X';
    board[2][2] = 'X';
    board[2][3] = 'X';
    board[2][4] = 'X';
    board[2][5] = 'X';
    board[2][6] = 'X';
    board[2][7] = 'O';

    // row 3
    // {'X','X','X','X','X','X','X','O'}
    board[3][0] = 'X';
    board[3][1] = 'X';
    board[3][2] = 'X';
    board[3][3] = 'X';
    board[3][4] = 'X';
    board[3][5] = 'X';
    board[3][6] = 'X';
    board[3][7] = 'O';

    // row 4
    // {'O','X','X','O','X','X','X','O'}
    board[4][0] = 'O';
    board[4][1] = 'X';
    board[4][2] = 'X';
    board[4][3] = 'O';
    board[4][4] = 'X';
    board[4][5] = 'X';
    board[4][6] = 'X';
    board[4][7] = 'O';

    // row 5
    // {'O','O','X','O','O','X','X','O'}
    board[5][0] = 'O';
    board[5][1] = 'O';
    board[5][2] = 'X';
    board[5][3] = 'O';
    board[5][4] = 'O';
    board[5][5] = 'X';
    board[5][6] = 'X';
    board[5][7] = 'O';

    // row 6
    // {'O','O','X','X','O','O','X','O'}
    board[6][0] = 'O';
    board[6][1] = 'O';
    board[6][2] = 'X';
    board[6][3] = 'x';
    board[6][4] = 'O';
    board[6][5] = 'O';
    board[6][6] = 'X';
    board[6][7] = 'O';

    // row 7
    // {'O','O','O','O','O','O','O',' '}
    board[7][0] = 'O';
    board[7][1] = 'O';
    board[7][2] = 'O';
    board[7][3] = 'O';
    board[7][4] = 'O';
    board[7][5] = 'O';
    board[7][6] = 'O';
    board[7][7] = ' ';
}
