#ifndef LINKEDLISTBIDIRECTIONAL_H
#define LINKEDLISTBIDIRECTIONAL_H
#include "Node.h"
#include <stdio.h>

void PrintList(Node* head, FILE* stream);
void PrintActions();

Node* push(Node** head, Material* m);
Node* pop(Node** head);
Node* popAt(Node** head, int index);
Node* pushAt(Node** head, Material* m, int  index);
Node* getElementAt(Node* head, int index);

void freeList(Node* head);


#endif
