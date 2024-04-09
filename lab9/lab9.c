#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

// Implement these functions
void handleInsert(LinkedList*);
void handleRemove(LinkedList*);
void handleCurrentCal(LinkedList*, int);
void handleVoltage(LinkedList*, int);
void handlePrint(LinkedList*);
void handleQuit(LinkedList*);

int main(void) {
  LinkedList circuit;
  initList(&circuit);
  char command = '\0';
  printf("Welcome to our circuit simulator\n");
  // Enter the source voltage!
  printf("What is the source of the voltage?\n");
  int voltage;
  readInputNumber(&voltage);
  while (command != 'Q') {
    command = getCommand();

    switch (command) {
      case 'I':
        handleInsert(&circuit);
        break;
      case 'R':
        handleRemove(&circuit);
        break;
      case 'C':
        handleCurrentCal(&circuit, voltage);
        break;
      case 'V':
        handleVoltage(&circuit, voltage);
        break;
      case 'P':
        handlePrint(&circuit);
        break;
      case 'Q':
        handleQuit(&circuit);
        break;
    }
  }
  return 0;
}

void handleInsert(LinkedList* circuit) {
  int resistance = 0;
  printf("What's the value of the resistor: ");
  readInputNumber(&resistance);
  printf("What's the label of the resistor: ");
  char labelName[STRING_MAX];
  readInputString(labelName, STRING_MAX);
  // TODO: Implement the insert into ordered list function
  Node *newR = (Node*) malloc(sizeof(Node));
  newR->value = resistance;
  for(int i = 0; i < strlen(labelName); i++){
    newR->name[i] = labelName[i];
  }
  newR->next = NULL;

  Node *now = circuit->head;
  while (now != NULL){
    if (!strcmp(newR->name, now->name)){
      printf("A resistor with %s label already exists.\n", newR->name);
      free(newR);
      return;
    }
    now = now->next;
  }

  if (circuit->head == NULL){
    circuit->head = newR;
  }
  else if (circuit->head->next == NULL){
    int cmp = strcmp(newR->name, circuit->head->name);
    // if (!cmp){
    //   printf("A resistor with %s label already exists.", newR->name);
    //   free(newR);
    // }
    if (cmp > 0){
      circuit->head->next = newR;
    }
    else{
      newR->next = circuit->head;
      circuit->head = newR;
    }
  }
  else {
    Node *current = circuit->head;
    if (strcmp(newR->name, current->name) < 0){
      newR->next = circuit->head;
      circuit->head = newR;
      return;
    }
    while (current->next != NULL && strcmp(newR->name, current->next->name) > 0){
      current = current->next;
    }
    if (current->next == NULL){
      current->next = newR;
    }
    else{
      newR->next = current->next;
      current->next = newR;
    }
  }
}
void handleRemove(LinkedList* circuit) {
  // TODO: Implement the remove function
  printf("What's the label of the resistor you want to remove: ");
  char labelName[STRING_MAX];
  readInputString(labelName, STRING_MAX);

  Node *current = circuit->head;
  if (current == NULL || (strcmp(current->name, labelName) && current->next == NULL)){
    printf("The resistor with %s label does not exist.\n", labelName);
    return;
  }
  if (!strcmp(current->name, labelName) && current->next == NULL){
    free(circuit->head);
    circuit->head = NULL;
    return;
  }
  if (!strcmp(current->name, labelName)){
    Node *temp = current->next;
    free(circuit->head);
    circuit->head = temp;
    return;
  }

  while (current->next->next != NULL && strcmp(current->next->name, labelName)){
    current = current->next;
  }

  if (current->next->next == NULL){
    if (!strcmp(current->next->name, labelName)){
      free(current->next);
      current->next = NULL;
      return;
    }
    else if (strcmp(current->next->name, labelName)){
      printf("The resistor with %s label does not exist.\n", labelName);
      return;
    }
  }  
  else{
    if (!strcmp(current->next->name, labelName)){
      Node *temp = current->next;
      current->next = temp->next;
      free(temp);
      return;
    }
  }
}


void handleCurrentCal(LinkedList* circuit, int voltage) {
  // TODO: Implement the function that prints the value of current in the
  // circuit
  Node *current = circuit->head;
  int Req = 0;
  while (current != NULL){
    Req += current->value;
    current = current->next;
  }
  printf("The current in the circuit is %.6lfA", (double) voltage / Req);
}
void handleVoltage(LinkedList* circuit, int voltage) {
  // TODO: Implement the function that prints the potential difference across a
  // resistor
  printf("What's the label of the resistor you want to find the voltage across: ");
  char label[STRING_MAX];
  readInputString(label, STRING_MAX);
  Node *current = circuit->head;
  int Req = 0, R = 0;
  double I = 0;
  bool found = false;
  while (current != NULL){
    if (!strcmp(label, current->name)){
      R = current->value;
      found = true;
    }
    Req += current->value;
    current = current->next;
  }
  if (!found){
    printf("The resistor with %s label does not exist.\n", label);
  }
  else{
    I = (double) voltage / Req;
    printf("Voltage across resistor is %.6lfV\n", I * R);
  }
}
void handlePrint(LinkedList* circuit) {
  // TODO: they can implement the print function
  Node* current = circuit->head;
  while(current != NULL){
    printf("%s  %d Ohms\n", current->name, current->value);
    current = current->next;
  }
}

void handleQuit(LinkedList* circuit) {
  // TODO: Implement the quit function
  printf("Removing all resistors in the circuit...\n");
  handlePrint(circuit);
  Node *temp = circuit->head;
  Node *current = temp->next;
  while (current != NULL){
    free(temp);
    temp = current;
    current = current->next;
  }
  free(temp);
}
