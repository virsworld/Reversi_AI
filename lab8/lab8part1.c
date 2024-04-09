//
// Author: Vir
//

#include "lab8part1.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


void printBoard(char board[][26], int n){
  printf("  a");
  char temp = 'a';
  for (int i = 0; i < n - 1; i ++){
    printf("%c", ++temp);
  }
  printf("\n");
  temp = '`';
  for (int row = 0; row < n; row++){
    for (int col = 0; col < n; col++){
      if ((row == (n / 2) - 1 && col == (n / 2) - 1) || (row == n / 2 && col == n / 2)){
        board[row][col] = 'W';
      }
      else if ((row == (n / 2) - 1 && col == n / 2) || (row == n / 2 && col == (n / 2) - 1)){
        board[row][col] = 'B';
      }
      else {
        board[row][col] = 'U';
      }
    }
  }
  for (int row = 0; row < n; row++){
    printf("%c ", ++temp);
    for (int col = 0; col < n; col++){
      printf("%c", board[row][col]);
    }
    printf("\n");
  }
}

bool positionInBounds(int n, int row, int col){
  int torf = 1;
  if (row >= n || col >= n){
    torf = 0;
  }
  return torf;
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
  for (int nRow = row, nCol = col; nRow + deltaRow >= 0 && nRow + deltaRow < n && nCol + deltaCol >= 0 && nCol + deltaCol < n; nRow += deltaRow, nCol += deltaCol){
    if (colour == 'W' && board[row + deltaRow][col + deltaCol] == 'B' && board[nRow + deltaRow][nCol + deltaCol] == 'W'){
      return true;
    }
    else if (colour == 'W' && board[row + deltaRow][col + deltaCol] == 'B' && board[nRow + deltaRow][nCol + deltaCol] == 'U'){
      return false;
    }
    else if (colour == 'B' && board[row + deltaRow][col + deltaCol] == 'W' && board[nRow + deltaRow][nCol + deltaCol] == 'B'){
      return true;
    }
    else if (colour == 'B' && board[row + deltaRow][col + deltaCol] == 'W' && board[nRow + deltaRow][nCol + deltaCol] == 'U')
      return false;
  }
  return false;
}

void getMoves(char board[][26], int *arTemp, char colour, int n);
void printNowboard(char board[][26], int n);
bool checkMove(char board[][26], int temp[], char Crow, char Ccol, int n);
void flipTiles(char board[][26], char colour, char Crow, char CCol, int n);
void getAImove(char board[][26], char aiMove[], char colour, int n);
void printWin(char board[][26], char clrs[], int n);
int checkStatus(char board[][26], char clrs[], int n);

int main(void) {
  int n = 0, turn = 0, invalid = 0;
  char board[26][26] = {0}, hMove[2] = {0}, aiMove[2] = {0}, clrs[2] = {0};
  printf("Enter the board dimension: ");
  scanf(" %d", &n);
  printf("Computer plays (B/W): ");
  scanf("\n%c", clrs);
  switch (*clrs){
    case 'W':
      clrs[1] = 'B';
      break;
    case 'B':
      turn = 1;
      clrs[1] = 'W';
    break;
  }
  int *hMoves = (int*) malloc(sizeof(int) * (unsigned long)(n * n));

  printBoard(board, n);
  getMoves(board, hMoves, clrs[1], n);
  while (checkStatus(board, clrs, n) != 0){
    if (turn){
      if (checkStatus(board, clrs, n) == -1){
        printf("%c player has no valid move.", *clrs);
        turn--;
      }
      else{
        getAImove(board, aiMove, *clrs, n);
        printf("\nComputer places %c at %c%c.", *clrs, *aiMove, aiMove[1]);
        flipTiles(board, *clrs, *aiMove, aiMove[1], n);
        *aiMove = 0;
        *(aiMove + 1) = 0;
        turn--;
        printNowboard(board, n);
        getMoves(board, hMoves, clrs[1], n);
      }
    }
    else{
      if (checkStatus(board, clrs, n) == -2){
        printf("%c player has no valid move.", clrs[1]);
        turn++;
      }
      else{
        printf("\nEnter move for colour %c (RowCol): ", clrs[1]);
        scanf("\n%c%c", hMove, hMove + 1);
        if (checkMove(board, hMoves, *hMove, hMove[1], n)){
          flipTiles(board, clrs[1], *hMove, hMove[1], n);
        }
        else{
          invalid = 1;
          break;
        }
        turn++;
        printNowboard(board, n);
        getMoves(board, hMoves, clrs[1], n);
      }
    }
  }
  if (invalid){
    printf("\nInvalid move.\n");
    printf("%c player wins.", *clrs);
  }
  else{
    printWin(board, clrs, n);
  }
  free(hMoves);
  return 0;
}
void printNowboard(char board[][26], int n){
  printf("\n");
  printf("  a");
  char temp = 'a';
  for (int i = 0; i < n - 1; i ++){
    printf("%c", ++temp);
  }
  printf("\n");
  temp = '`';
  for (int row = 0; row < n; row++){
    printf("%c ", ++temp);
    for (int col = 0; col < n; col++){
      printf("%c", board[row][col]);
    }
    printf("\n");
  }
}

void getMoves(char board[][26], int* arTemp, char colour, int n){
  for (int i = 0; i < n * n; i++){
    arTemp[i] = 0;
  }
  int count = 0, rowDirec = 1, colDirec = 1;
  for (int row = 0; row < n; row++){
    for (int col = 0; col < n; col++){
      if (board[row][col] == 'U'){
        for (int i = 0; i < 8; i++){
          if (checkLegalInDirection(board, n, row, col, colour, rowDirec, colDirec)){
            if (row * 10 + col == 0){
              arTemp[count] = -1;
            }
            else{
              arTemp[count] = row * 10 + col;
            }
            count++;
            break;
          }
          switch (i){
            case 0:
              colDirec--; // 1, 1
              break;
            case 1:
              colDirec--; // 1, 0
              break;
            case 2:
              rowDirec--; // 1, -1
              break;
            case 3:
              rowDirec--; // 0, -1
              break;
            case 4:
              colDirec++; // -1, -1
              break;
            case 5:
              colDirec++; // -1, 0
              break;
            case 6:
              rowDirec++; // -1, 1 last: 0, 1
              break;
          }
        }
        rowDirec = 1, colDirec = 1;
      }
    }
  }
}

bool checkMove(char board[][26], int temp[], char Crow, char Ccol, int n){
  int Nrow = Crow - 'a', Ncol = Ccol - 'a';
  if (!(positionInBounds(n,Crow - 'a',Ccol - 'a') && board[(int) Crow - 'a'][(int) Ccol - 'a'] == 'U')){
    return false;
  }
  else{
    for (int i = 0; temp[i] != 0; i++){
      if (temp[i] == Nrow * 10 + Ncol || (Nrow * 10 + Ncol == 0 && temp[i] == -1)){
        return true;
      }
    }
  }
  return false;
}

void flipTiles(char board[][26], char colour, char Crow, char Ccol, int n){
  int Nrow = Crow - 'a', Ncol = Ccol - 'a',rowDirec = 1, colDirec = 1;
  for (int i = 0; i < 8; i++){
    if (checkLegalInDirection(board, n, Nrow, Ncol, colour, rowDirec, colDirec)){
      board[Nrow][Ncol] = 'U';
      switch (i){
        case 0: // 1, 1
          for (; board[Nrow][Ncol] != colour; Nrow++, Ncol++){
            board[Nrow][Ncol] = colour;
          }
          break;
        case 1: // 1, 0
          for (; board[Nrow][Ncol] != colour; Nrow++){
            board[Nrow][Ncol] = colour;
          }
          break;
        case 2: // 1, -1
          for (; board[Nrow][Ncol] != colour; Nrow++, Ncol--){
            board[Nrow][Ncol] = colour;
          }
          break;
        case 3: // 0, -1
          for (; board[Nrow][Ncol] != colour; Ncol--){
            board[Nrow][Ncol] = colour;
          }
          break;
        case 4: // -1, -1
          for (; board[Nrow][Ncol] != colour; Nrow--, Ncol--){
            board[Nrow][Ncol] = colour;
          }
          break;
        case 5: // -1, 0
          for (; board[Nrow][Ncol] != colour; Nrow--){
            board[Nrow][Ncol] = colour;
          } 
          break;
        case 6: // -1, 1
          for (; board[Nrow][Ncol] != colour; Nrow--, Ncol++){
            board[Nrow][Ncol] = colour;
          }
          break;
        case 7: // 0, 1
          for (; board[Nrow][Ncol] != colour; Ncol++){
            board[Nrow][Ncol] = colour;
          }
          break;
      }
    }
    switch (i){
      case 0: // 1, 1
        colDirec--; 
        break;
      case 1: // 1, 0
        colDirec--; 
        break;
      case 2: // 1, -1
        rowDirec--; 
        break;
      case 3: // 0, -1
        rowDirec--; 
        break;
      case 4: // -1, -1
        colDirec++; 
        break;
      case 5: // -1, 0
        colDirec++; 
        break;
      case 6: // -1, 1 last: 0, 1
        rowDirec++; 
        break;
    }
    Nrow = Crow - 'a', Ncol = Ccol - 'a';
  }
}
void getAImove(char board[][26], char aiMove[], char colour, int n){
  int *points = (int*) malloc(sizeof(int) * (unsigned long)(n * n));
  for (int i = 0; i < n * n; i++){
    points[i] = 0;
  }
  int maxPoints = 0, rowDirec = 1, colDirec = 1;
  for (int row = 0; row < n; row++){
    for (int col = 0; col < n; col++){
      if (board[row][col] == 'U'){
        for (int i = 0; i < 8; i++){
          if (checkLegalInDirection(board, n, row, col, colour, rowDirec, colDirec)){
            switch (i){
              case 0: // 1, 1
                for (int Nrow = row , Ncol = col; board[Nrow][Ncol] != colour; Nrow++, Ncol++){
                  if(!(Nrow == row && Ncol == col)){
                    points[row * n + col]++;
                  }
                }
                break;
              case 1: // 1, 0
                for (int Nrow = row, Ncol = col; board[Nrow][Ncol] != colour; Nrow++){
                  if(!(Nrow == row && Ncol == col)){
                    points[row * n + col]++;
                  }
                }
                break;
              case 2: // 1, -1
                for (int Nrow = row, Ncol = col; board[Nrow][Ncol] != colour; Nrow++, Ncol--){
                  if(!(Nrow == row && Ncol == col)){
                    points[row * n + col]++;
                  }
                }
                break;
              case 3: // 0, -1
                for (int Nrow = row, Ncol = col; board[Nrow][Ncol] != colour; Ncol--){
                  if(!(Nrow == row && Ncol == col)){
                    points[row * n + col]++;
                  }
                }
                break;
              case 4: // -1, -1
                for (int Nrow = row, Ncol = col; board[Nrow][Ncol] != colour; Nrow--, Ncol--){
                  if(!(Nrow == row && Ncol == col)){
                    points[row * n + col]++;
                  }
                }
                break;
              case 5: // -1, 0
                for (int Nrow = row, Ncol = col; board[Nrow][Ncol] != colour; Nrow--){
                  if(!(Nrow == row && Ncol == col)){
                    points[row * n + col]++;
                  }
                } 
                break;
              case 6: // -1, 1
                for (int Nrow = row, Ncol = col; board[Nrow][Ncol] != colour; Nrow--, Ncol++){
                  if(!(Nrow == row && Ncol == col)){
                    points[row * n + col]++;
                  }
                }
                break;
              case 7: // 0, 1
                for (int Nrow = row, Ncol = col; board[Nrow][Ncol] != colour; Ncol++){
                  if(!(Nrow == row && Ncol == col)){
                    points[row * n + col]++;
                  }
                }
                break;
            }
          }
          switch (i){
            case 0:
              colDirec--; // 1, 1
              break;
            case 1:
              colDirec--; // 1, 0
              break;
            case 2:
              rowDirec--; // 1, -1
              break;
            case 3:
              rowDirec--; // 0, -1
              break;
            case 4:
              colDirec++; // -1, -1
              break;
            case 5:
              colDirec++; // -1, 0
              break;
            case 6:
              rowDirec++; // -1, 1 last: 0, 1
              break;
          }
        }
        rowDirec = 1, colDirec = 1;
      }
    }
  }
  for (int i = 0; i < n * n; i++){
    if (points[i] > maxPoints){
      maxPoints = points[i];
    }
  }

  for (int i = 0; i < n * n; i++){
    if (points[i] == maxPoints){
      aiMove[0] = (char)('a' + (i / n)), aiMove[1] = (char)('a' + (i % n));
      break;
    }
  }
  free(points);
  points = NULL;
}
int checkStatus(char board[][26], char clrs[], int n){
  int temp[26 * 26] = {0}, status = 0;
  bool aiCheck = false, hCheck = false;
  getMoves(board, temp, *clrs, n);
  for (int i = 0; i < 26 * 26; i++){
    if (temp[i] != 0){
      aiCheck = true;
    }
  }
  for (int i = 0; i < 26 * 26; i++){
    temp[i] = 0;
  }
  getMoves(board, temp, clrs[1], n);
  for (int i = 0; i < 26 * 26; i++){
    if (temp[i] != 0){
      hCheck = true;
    }
  }
  if (!aiCheck && hCheck){
    status = -1;
  }
  else if (aiCheck && !hCheck){
    status = -2;
  }
  else if (aiCheck && hCheck){
    status = 1;
  }
  return status;
}

void printWin(char board[][26], char clrs[], int n){
  int aiPoints = 0, hPoints = 0;
  for (int row = 0; row < n; row++){
    for (int col = 0; col < n; col++){
      if (board[row][col] == *clrs){
        aiPoints++;
      }
      else if (board[row][col] == clrs[1]){
        hPoints++;
      }
    }
  }
  if (aiPoints > hPoints){
    printf("\n%c player wins.\n", *clrs);
  }
  else if (hPoints > aiPoints){
    printf("\n%c player wins.\n", clrs[1]);
  }
  else{
    printf("\nDraw!\n");
  }
}
