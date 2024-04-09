#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_MAX 1024

/**
 * @brief Represents a node in a linked list.
 */
typedef struct node {
  int value;
  char name[STRING_MAX];
  struct node* next;
} Node;

/**
 * @brief Represents a linked list.
 */
typedef struct linkedList {
  Node* head;
} LinkedList;

void readInputString(char* s, int length) {
  int i = 0;
  char c;

  while (i < length && (c = getchar()) != '\n') {
    s[i++] = c;
  }

  s[i] = '\0';
}

void readInputNumber(int* number) {
  char buf[STRING_MAX];
  readInputString(buf, STRING_MAX);
  *number = (int)strtol(buf, (char**)NULL, 10);
}

void readInputChar(char* character) {
  char buf[2];
  readInputString(buf, 3);
  *character = buf[0];
}

/**
 * @brief Initialize the members of a linked list.
 *
 * @param list A pointer to the linked list to initialize. Assumed to be
 * non-NULL.
 */
void initList(LinkedList* list) {
  // The head initially points to nothing.
  list->head = NULL;
}

char getCommand() {
  char command;

  printf("\nSupported commands are:\n");
  printf("  I - Insert Resistor\n");
  printf("  R - Remove Resistor \n");
  printf("  C - Calculate Current\n");  // Get sum of all resistors, and voltage
                                        // sum of resistance
  printf("  P - Print Resistor's Values\n");
  printf("  V - Voltage across a Resistor \n");  // Remove duplicates and
                                                 // replace with their sum
  printf("  Q - Quit\n");

  printf("\nPlease select a command: ");
  readInputChar(&command);

  while (command != 'I' && command != 'R' && command != 'C' && command != 'P' &&
         command != 'V' && command != 'Q') {
    printf("Invalid command <%c>, please select a command: ", command);
    readInputChar(&command);
  }

  return command;
}
