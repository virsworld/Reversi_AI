//
// Author: Vir
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <float.h>
#include <sys/time.h>
#include <sys/resource.h>

int location = 0;
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
double eval(char state[][26], char aiCol, char hCol, int n);
double ieScore(char state[][26], char aiCol, char hCol, int n);
double spaceScore(char state[][26], char aiCol, char hCol, int n);
double extremeScore(char state[][26], char aiCol, char hCol, int n);
double openmovesScore(char state[][26], char aiCol, char hCol, int n);
bool isInterior(char state[][26], int row, int col, int n);
double MM(char state[][26], int n, char Cols[], double alpha, double beta, int depth, bool isMax, int *row, int *col);
void getBranches(char state[][26], int n, int *branchCount, char branches[][26][26], char colour);
double max(double x, double y);
double min(double x, double y);

int makeMove(const char board[][26], int n, char turn, int *row, int *col); // submit


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
        // getAImove(board, aiMove, *clrs, n);
        int row = 0, col = 0;
        struct rusage usage; // a structure to hold "resource usage" (including time)
        struct timeval start, end; // will hold the start and end times
        getrusage(RUSAGE_SELF, &usage);
        start = usage.ru_utime;
        double timeStart = start.tv_sec +
        start.tv_usec / 1000000.0; // in seconds
        makeMove(board, n, *clrs, &row, &col);
        getrusage(RUSAGE_SELF, &usage);
        end = usage.ru_utime;
        double timeEnd = end.tv_sec +
        end.tv_usec / 1000000.0; // in seconds
        double totalTime = timeEnd - timeStart;
        printf("\n---------------------------\n");
        printf("%lf", totalTime);
        printf("\n---------------------------\n");
        *aiMove = 'a' + (char) row, aiMove[1] = 'a' + (char) col;
        printf("\nComputer places %c at %c%c.", *clrs, *aiMove, aiMove[1]);
        flipTiles(board, *clrs, *aiMove, aiMove[1], n);
        *aiMove = 0;
        *(aiMove + 1) = 0;
        turn--;
        printNowboard(board, n);
        eval(board, *clrs, clrs[1], n);
        getMoves(board, hMoves, clrs[1], n);
      }
    }
    else{
      if (checkStatus(board, clrs, n) == -2){
        printf("%c player has no valid move.", clrs[1]);
        turn++;
      }
      else{
        // printf("\nEnter move for colour %c (RowCol): ", clrs[1]);
        // scanf("\n%c%c", hMove, hMove + 1);
        int row = 0, col = 0;
        findSmarterMove(board, n, clrs[1], &row, &col);
        *hMove = 'a' + (char) row, hMove[1] = 'a' + (char) col;
        printf("\nSmartest move: %c%c", *hMove, hMove[1]);
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
  // printf("\n----------------------------");
  // for (int i = 0; i < n; i++){
  //   printf("\n");
  //   for (int j = 0; j < n; j++){
  //     printf("%c", board[i][j]);
  //   }
  // }
  // printf("\n----------------------------");
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

int makeMove(const char board[][26], int n, char turn, int *row, int *col){
  char Cols[2];
  if (turn == 'B'){
    *Cols = turn;
    Cols[1] = turn + ('W' - 'B');
  }
  else{
    *Cols = turn;
    Cols[1] = turn - ('W' - 'B');
  }
  char state[26][26] = {0};
  for (int floor = 0; floor < n; floor++){
    for (int wall = 0; wall < n; wall++){
      state[floor][wall] = board[floor][wall];
    }
  }
  double alpha = -DBL_MAX, beta = DBL_MAX;
  MM(state, n, Cols, alpha, beta, 4, true, row, col);
  int *temp = (int*) malloc( (unsigned int) (n * n) * sizeof(int));
  getMoves(board, temp, *Cols, n);
  if (temp[location] == -1){
    *row = 0;
    *col = 0;
  }
  else{
    *row = temp[location] / 10;
    *col = temp[location] % 10;
  }
  free(temp);
  location = 0;
  return 0;
}
double MM(char state[][26], int n, char Cols[], double alpha, double beta, int depth, bool isMax, int *row, int *col){
  if (depth == 0 || !checkStatus(state, Cols, n)){
    return eval(state, *Cols, Cols[1], n);
  }
  if (isMax){
    double maxEval = -DBL_MAX, eval = 0;
    char branches[26*26][26][26] = {0};
    int branchCount = 0;
    getBranches(state, n, &branchCount, branches, *Cols);
    for (int j = 0; j < branchCount; j++){
      eval = MM(branches[j], n, Cols, alpha, beta, depth - 1, false, row, col);
      maxEval = max(maxEval, eval);
      if (eval >= maxEval && depth == 4){
        location = j;
      }
      alpha = max(alpha, eval);
      if (beta <= alpha){
        break;
      }
    }
    return maxEval;
  }
  else{
    double minEval = DBL_MAX, eval = 0;
    char branches[26*26][26][26] = {0};
    int branchCount = 0;
    getBranches(state, n, &branchCount, branches, Cols[1]);
    for (int j = 0; j < branchCount; j++){
      eval = MM(branches[j], n, Cols, alpha, beta, depth - 1, true, row, col);
      minEval = min(minEval, eval);
      beta = min(beta, eval);
      if (beta <= alpha){
        break;
      }
    }
    return minEval;
  }
}
void getBranches(char state[][26], int n, int *branchCount, char branches[][26][26], char colour){
  int *temp = (int*) malloc(sizeof(int) * (unsigned int) (n * n));
  getMoves(state, temp, colour, n);
  for(int i = 0; temp[i] != 0; i++){
    *branchCount = *branchCount + 1;
    for (int row = 0; row < n; row++){
      for (int col = 0; col < n; col++){
        branches[i][row][col] = state[row][col];
      }
    }
    if (temp[i] == -1){
      flipTiles(branches[i], colour, 'a', 'a', n);
      // printNowboard(branches[i], n);
    }
    else{
      flipTiles(branches[i], colour, 'a' + (char) (temp[i] / 10), 'a' + (temp[i] % 10), n);
      // printNowboard(branches[i], n);
    }
  }
}
double eval(char state[][26], char aiCol, char hCol, int n){
  double score = 0;
  score+= ieScore(state, aiCol, hCol, n) + spaceScore(state, aiCol, hCol, n) + extremeScore(state, aiCol, hCol, n) + openmovesScore(state, aiCol, hCol, n);
  // printf("\n%lf", score);
  return score;
}
bool isInterior(char state[][26], int row, int col, int n){
  int deltaRow = 1, deltaCol = 1;
  for (int i = 0; i < 8; i++){
    if(positionInBounds(n, row + deltaRow, col + deltaCol) && state[row + deltaRow][col + deltaCol] == 'U'){
      return false;
    }
    switch (i){
    case 0:
      deltaCol--; // 1, 1
      break;
    case 1:
      deltaCol--; // 1, 0
      break;
    case 2:
      deltaRow--; // 1, -1
      break;
    case 3:
      deltaRow--; // 0, -1
      break;
    case 4:
      deltaCol++; // -1, -1
      break;
    case 5:
      deltaCol++; // -1, 0
      break;
    case 6:
      deltaRow++; // -1, 1 last: 0, 1
      break;
    }
  }
  return true;
}
double ieScore(char state[][26], char aiCol, char hCol, int n){
  double ieScore = 0, wInterior = .5, wExterior = -.5;
  int aiInterior = 0, aiExterior = 0, hInterior = 0, hExterior = 0;
  for (int row = 0; row < n; row++){
    for (int col =0; col < n; col++){
      if (state[row][col] == aiCol){
        if (isInterior(state, row, col, n)){
          aiInterior++;
        }
        else{
          aiExterior++;
        }
      }
      else if (state[row][col] == hCol){
        if (isInterior(state, row, col, n)){
          hInterior++;
        }
        else{
          hExterior++;
        }
      }
    }
  }
  ieScore = (aiInterior * wInterior + aiExterior * wExterior) - (hInterior * wInterior + hExterior * wExterior);
  // printf("\nInterior & Exterior for %c: %d, %d", aiCol, aiInterior, aiExterior);
  // printf("\nInterior & Exterior for %c: %d, %d", hCol, hInterior, hExterior);
  return ieScore;
}

double spaceScore(char state[][26], char aiCol, char hCol, int n){
  double spaceScore = 0, wCorner = 16.16, wBuffer = -2.99, wEdge = 0.98, wCenter = -.04;
  int aiCorners = 0, hCorners = 0, aiBuffers = 0, hBuffers = 0, aiEdges = 0, hEdges = 0, aiCenters = 0, hCenters = 0;
  for (int row = 0; row < n; row++){
    for (int col = 0; col < n; col++){
      if (state[row][col] == aiCol){
        if ((row == 0 && col < n - 2 && col >= 1) || (row == n - 1 && col < n - 2 && col >= 1)
        || (col == 0 && row < n - 2 && row >= 1) || (col == n && row < n - 2 && row >= 1)){
          aiEdges++;
        }
        else if ((row == 0 && col == 1) || (row == 1 && (col == 0 || col == 1)) || 
        (row == 0 && col == n - 2) || (row == 1 && (col == n - 1 || col == n - 2)) ||
        (row == n - 1 && col == 1) || (row == n - 2 && (col == 0 || col == 1)) ||
        (row == n - 1 && col == n - 2) || (row == n - 2 && (col == n - 1 || col == n - 2))){
          aiBuffers++;
        }
        else if ((row == 0 && col == 0) || (row == n - 1 && col == 0) || (row == 0 && col == n - 1) || (row == n - 1 && col == n - 1)){
          aiCorners++;
        }
        else{
          aiCenters++;
        }
      }
      else if (state[row][col] == hCol){
        if ((row == 0 && col < n - 2 && col >= 1) || (row == n - 1 && col < n - 2 && col >= 1)
        || (col == 0 && row < n - 2 && row >= 1) || (col == n && row < n - 2 && row >= 1)){
          hEdges++;
        }
        else if ((row == 0 && col == 1) || (row == 1 && (col == 0 || col == 1)) || 
        (row == 0 && col == n - 2) || (row == 1 && (col == n - 1 || col == n - 2)) ||
        (row == n - 1 && col == 1) || (row == n - 2 && (col == 0 || col == 1)) ||
        (row == n - 1 && col == n - 2) || (row == n - 2 && (col == n - 1 || col == n - 2))){
          hBuffers++;
        }
        else if ((row == 0 && col == 0) || (row == n - 1 && col == 0) || (row == 0 && col == n - 1) || (row == n - 1 && col == n - 1)){
          hCorners++;
        }
        else{
          hCenters++;
        }
      }
    }
  }
  // printf("\n%c space score: %lf", aiCol, aiBuffers * wBuffer + aiCenters * wCenter + aiCorners * wCorner + aiEdges * wEdge);
  // printf("\n%c space score: %lf", hCol, hBuffers * wBuffer + hCenters * wCenter + hCorners * wCorner + hEdges * wEdge);
  spaceScore = (aiBuffers * wBuffer + aiCenters * wCenter + aiCorners * wCorner + aiEdges * wEdge) - (hBuffers * wBuffer + hCenters * wCenter + hCorners * wCorner + hEdges * wEdge);
  return spaceScore;
}
double extremeScore(char state[][26], char aiCol, char hCol, int n){
  char Cols[2] = {aiCol, hCol};
  if (!checkStatus(state, Cols, n)){
    int aiPoints = 0, hPoints = 0;
    for (int row = 0; row < n; row++){
      for (int col = 0; col < n; col++){
        if (state[row][col] == *Cols){
          aiPoints++;
        }
        else if (state[row][col] == Cols[1]){
          hPoints++;
        }
      }
    }
    if (aiPoints > hPoints){
      return DBL_MAX;
    }
    else if (hPoints > aiPoints){
      return -DBL_MAX;
    }
  }
  return 0;
}
double openmovesScore(char state[][26], char aiCol, char hCol, int n){
  int *temp = (int*) malloc(sizeof(int) * (unsigned int) (n * n));
  getMoves(state, temp, aiCol, n);
  int aiCount = 0;
  for (int i = 0; temp[i] != 0; i++){
    aiCount++;
  }
  getMoves(state, temp, hCol, n);
  int hCount = 0;
  for (int i = 0; temp[i] != 0; i++){
    hCount++;
  }
  free(temp);
  return (aiCount - hCount) / 1.7;
}
double max(double x, double y){
  double big = 0;
  if (x > y){
    big = x;
  }
  else if (y > x){
    big = y;
  }
  else{
    big = x;
  }
  return big;
}
double min(double x, double y){
  double small = 0;
  if (x < y){
    small = x;
  }
  else if (y < x){
    small = y;
  }
  else{
    small = x;
  }
  return small;
}
