//
// Author: Vir
//

#include "reversi.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int Wcheck = 0;
int Bcheck = 0;
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
  if (row > n || col > n){
    torf = 0;
  }
  return torf;
}

//Based on old APS105 repository
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

void printMoves(char board[][26], int *arTemp, char colour, int n);

void printNowboard(char board[][26], int n);

bool checkMove(char board[][26], char colour, int temp[], char Crow, char Ccol, int n);

void makeMove(char board[][26], char colour, char Crow, char CCol, int n);

int main(void) {
  int n = 0;
  char board[26][26] = {0};
  printf("Enter the board dimension: ");
  scanf(" %d", &n);
  int WTemp[26*26] = {0};
  int BTemp[26*26] = {0};
  printBoard(board, n);
  printf("Enter board configuration:\n");
  char colour[1];
  char Crow[1];
  char Ccol[1];
  do{
    scanf(" %c%c%c", colour, Crow, Ccol);
    board[(int) *Crow - 'a'][(int) *Ccol - 'a'] = *colour;
  } while (*colour != '!');
  printNowboard(board, n);
  printf("Available moves for W:\n");
  printMoves(board, WTemp, 'W', n);
  printf("\nAvailable moves for B:\n");
  printMoves(board, BTemp, 'B', n);
  printf("Enter a move:\n");
  scanf(" %c%c%c", colour, Crow, Ccol);
  if (*colour == 'W' && checkMove(board, *colour, WTemp, *Crow, *Ccol, n)){
    printf("Valid move.\n");
    makeMove(board, *colour, *Crow, *Ccol, n);
    printNowboard(board, n);
  }
  else if (*colour == 'B' && checkMove(board, *colour, BTemp, *Crow, *Ccol, n)){
    printf("Valid move.\n");
    makeMove(board, *colour, *Crow, *Ccol, n);
    printNowboard(board, n);
  }
  else{
    printf("Invalid move.\n");
    printNowboard(board, n);
  }
  return 0;
}

void printNowboard(char board[][26], int n){
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

void printMoves(char board[][26], int* arTemp, char colour, int n){
  int count = 0, rowDirec = 1, colDirec = 1;
  for (int row = 0; row < n; row++){
    for (int col = 0; col < n; col++){
      if (board[row][col] == 'U'){
        for (int i = 0; i < 8; i++){
          if (checkLegalInDirection(board, n, row, col, colour, rowDirec, colDirec)){
            printf("%c%c\n", 'a' + row, 'a' + col);
            if (row * 10 + col == 0 && colour == 'W'){
              Wcheck = 1;
            }
            if (row * 10 + col == 0 && colour == 'B'){
              Bcheck = 1;
            }
            arTemp[count] = row * 10 + col;
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

bool checkMove(char board[][26], char colour, int temp[], char Crow, char Ccol, int n){
  int Nrow = Crow - 'a';
  int Ncol = Ccol - 'a';

  if (colour == 'W' && Nrow * 10 + Ncol == 0 && !Wcheck){
    return false;
  }
  if (colour == 'B' && Nrow * 10 + Ncol == 0 && !Bcheck){
    return false;
  }

  if (!(positionInBounds(n,Crow - 'a' + 1,Ccol - 'a' + 1) && board[(int) Crow - 'a'][(int) Ccol - 'a'] == 'U')){
    return false;
  }
  else{
    for (int i = 0; i < 26 * 26; i++){
      if (temp[i] == Nrow * 10 + Ncol){
        return true;
      }
    }
  }
  return false;
}

void makeMove(char board[][26], char colour, char Crow, char Ccol, int n){
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
