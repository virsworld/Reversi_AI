#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void readWordPuzzle(const int Size, char puzzle[][Size]);
char* readWord(int* wordSize);
void printWordPuzzle(const int Size, char puzzle[][Size]);
void printWord(char* word, const int wordSize);

void search(const int Size,
  char puzzle[][Size],
  const int wordSize,
  char* word);

bool inBounds(int row, int col, const int Size);

int main(void) {
  const int Size = 20;
  char puzzle[Size][Size];
  readWordPuzzle(Size, puzzle);
  int wordSize = 0;
  char* word = readWord(&wordSize);
  printWordPuzzle(Size, puzzle);
  printf("The word you are looking for is\n");
  printWord(word, wordSize);
  printf("\n");
  printf("Do you want to search? (Y or N)\n");
  char isSearch;
  scanf(" %c", &isSearch);
  if (isSearch == 'Y' || isSearch == 'y') {
    search(Size, puzzle, wordSize, word);
  }
  free(word);
  return 0;
}

void search(const int Size, char puzzle[][Size], const int wordSize, char* word) {

  int temp = 0;
  int x = 0;
  int y = 0;
  for (int row = 0; row < Size; row++){
    for (int col = 0; col < Size; col++){
      // E check
      for (int count = 0; count < wordSize; count++){
          if ( (col + 1 <= Size) && (puzzle[row][col + count] == word[temp]) ){
            temp++;
          }
          else{
            break;
          }
        }
        if (temp == wordSize){
          x = row + 1;
          y = col + 1;
          temp = 3;
          break;
        }
        else{
          temp = 0;
        }
      // NE check
      for (int count = 0; count < wordSize; count++){
          if ( (col + 1 <= Size) && (row - count >= 0) && (puzzle[row - count][col + count] == word[temp]) ){
            temp++;
          }
          else{
            break;
          }
        }
        if (temp == wordSize){
          x = row + 1;
          y = col + 1;
          temp = 2;
          break;
        }
        else{
          temp = 0;
        }
      // N check
      for (int count = 0; count < wordSize; count++){
          if ( (row - count >= 0) && (puzzle[row - count][col] == word[temp]) ){    // trying to use lazy eval
            temp++;
          }
          else{
            break;
          }
        }
        if (temp == wordSize){
          x = row + 1;
          y = col + 1;
          temp = 1;
          break;
        }
        else{
          temp = 0;
        }
      // NW check
      for (int count = 0; count < wordSize; count++){
          if ( (col - count >= 0) && (row - count >= 0) && (puzzle[row - count][col - count] == word[temp]) ){
            temp++;
          }
          else{
            break;
          }
        }
        if (temp == wordSize){
          x = row + 1;
          y = col + 1;
          temp = 8;
          break;
        }
        else{
          temp = 0;
        }
      // W check
      for (int count = 0; count < wordSize; count++){
          if ( (col - count >= 0) && (puzzle[row][col - count] == word[temp]) ){
            temp++;
          }
          else{
            break;
          }
        }
        if (temp == wordSize){
          x = row + 1;
          y = col + 1;
          temp = 7;
          break;
        }
        else{
          temp = 0;
        }
      // SW check
      for (int count = 0; count < wordSize; count++){
          if ( (col - count >= 0) && (row + 1 <= Size) && (puzzle[row + count][col - count] == word[temp]) ){
            temp++;
          }
          else{
            break;
          }
        }
        if (temp == wordSize){
          x = row + 1;
          y = col + 1;
          temp = 6;
          break;
        }
        else{
          temp = 0;
        }
      // S check
      for (int count = 0; count < wordSize; count++){
          if ( (row + 1 <= Size) && (puzzle[row + count][col] == word[temp]) ){
            temp++;
          }
          else{
            break;
          }
        }
        if (temp == wordSize){
          x = row + 1;
          y = col + 1;
          temp = 5;
          break;
        }
        else{
          temp = 0;
        }
      // SE check
      for (int count = 0; count < wordSize; count++){
          if ( (col + 1 <= Size) && (row + 1 <= Size) && (puzzle[row + count][col + count] == word[temp]) ){
            temp++;
          }
          else{
            break;
          }
        }
        if (temp == wordSize){
          x = row + 1;
          y = col + 1;
          temp = 4;
          break;
        }
        else{
          temp = 0;
        }
      }
    if (temp != 0){
      break;
    }
  }

  switch(temp) {
    case 1:
      for (int i = 0; i < wordSize; i++){
        printf("%c", word[i]);
      }
      printf(" can be found at row, col = (%d, %d) in the north direction.", x, y);
      break;
    case 2:
      for (int i = 0; i < wordSize; i++){
        printf("%c", word[i]);
      }
      printf(" can be found at row, col = (%d, %d) in the north-east direction.", x, y);
      break;
    case 3:
      for (int i = 0; i < wordSize; i++){
        printf("%c", word[i]);
      }
      printf(" can be found at row , col = (%d, %d) in the east direction.", x, y);
      break;
    case 4:
      for (int i = 0; i < wordSize; i++){
        printf("%c", word[i]);
      }
      printf(" can be found at row , col = (%d, %d) in the south-east direction.", x, y);
      break;
    case 5:
      for (int i = 0; i < wordSize; i++){
        printf("%c", word[i]);
      }
      printf(" can be found at row , col = (%d, %d) in the south direction.", x, y);
      break;
    case 6:
      for (int i = 0; i < wordSize; i++){
        printf("%c", word[i]);
      }
      printf(" can be found at row , col = (%d, %d) in the south-west direction.", x, y);
      break;
    case 7:
      for (int i = 0; i < wordSize; i++){
        printf("%c", word[i]);
      }
      printf(" can be found at row , col = (%d, %d) in the west direction.", x, y);
      break;
    case 8:
      for (int i = 0; i < wordSize; i++){
        printf("%c", word[i]);
      }
      printf(" can be found at row , col = (%d, %d) in the north-west direction.", x, y);
      break;
  }
}

char* readWord(int* wordSize) {
  printf("\nHow many characters are there in the word? ");
  scanf(" %d", wordSize);

  char *hArray = (char*) malloc(sizeof(char) * *wordSize);

  printf("\nWhat is the word that you are looking for? ");
  for (int i = 0; i < *wordSize; i++){
    scanf(" %c", &hArray[i]);
  }

  return hArray;
}

void readWordPuzzle(const int Size, char puzzle[][Size]) {
  printf("Please enter the word puzzle:\n");
  for (int row = 0; row < Size; row++){
    for (int col = 0; col < Size; col++){
      scanf(" %c", &puzzle[row][col]);
    }
  }
}

bool inBounds(int row, int col, const int Size) {
  if (col >= 0 && col < Size && row >= 0 && row < Size){
    return true;
  }
  else{
    return false;
  }
}

void printWordPuzzle(const int Size, char puzzle[][Size]) {
  printf("\nThe word puzzle entered is\n");
  for (int row = 0; row < Size; row++){
    for (int col = 0; col < Size; col++){
      printf("%c ", puzzle[row][col]);
    }
    printf("\n");
  }
}

void printWord(char* word, const int wordSize) {
  for (int col = 0; col < wordSize; col++){
    printf("%c ", word[col]);
  }
}
