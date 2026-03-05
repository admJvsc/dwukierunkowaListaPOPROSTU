#include <stdio.h>
#include <stdlib.h>
#include "LinkedListBidirectional.h"

Node* push(Node** head, Material* m) {
    if (*head == NULL) {
        Node* nowyNode = (Node*)malloc(sizeof(Node));
        nowyNode->material = m;
        nowyNode->nastepny = NULL;
        nowyNode->poprzedni = NULL;
        *head = nowyNode;
        return nowyNode;
    }
    if ((*head)->nastepny == NULL) {
        Node* nowyNode = (Node*)malloc(sizeof(Node));
        nowyNode->material = m;
        nowyNode->nastepny = NULL;
        nowyNode->poprzedni = *head;
        (*head)->nastepny = nowyNode;
        return nowyNode;
    }
    return push(&((*head)->nastepny), m);
}

Node* pop(Node** head) {
    if (*head == NULL) return NULL;

    Node* current = *head;
    if (current->nastepny == NULL) {
        free(current->material);
        free(current);
        *head = NULL;
        return NULL;
    }
    while (current->nastepny != NULL) {
        current = current->nastepny;
    }
    current->poprzedni->nastepny = NULL;
    free(current->material);
    free(current);

    return *head;
}

Node* getElementAt(Node* head, int index) {
    if (head == NULL || index < 0) return NULL;
    if (index == 0) return head;
    return getElementAt(head->nastepny, index - 1);
}

Node* pushAt(Node** head, Material* m, int index) {
    if (index <= 0 || *head == NULL) {
        Node* nowyNode = (Node*)malloc(sizeof(Node));
        nowyNode->material = m;
        nowyNode->nastepny = *head;
        nowyNode->poprzedni = NULL;
        if (*head != NULL) (*head)->poprzedni = nowyNode;
        *head = nowyNode;
        return nowyNode;
    }

    Node* prevNode = getElementAt(*head, index - 1);

    if (prevNode == NULL || prevNode->nastepny == NULL) {
        return push(head, m);
    }

    Node* nowyNode = (Node*)malloc(sizeof(Node));
    nowyNode->material = m;
    nowyNode->nastepny = prevNode->nastepny;
    nowyNode->poprzedni = prevNode;

    prevNode->nastepny->poprzedni = nowyNode;
    prevNode->nastepny = nowyNode;

    return nowyNode;
}

Node* popAt(Node** head, int index) {
    if (*head == NULL) return NULL;

    Node* toDelete = getElementAt(*head, index);
    if (toDelete == NULL) return *head;

    if (toDelete->poprzedni != NULL) {
        toDelete->poprzedni->nastepny = toDelete->nastepny;
    } else {
        *head = toDelete->nastepny; // Usuwamy pierwszy element
    }

    if (toDelete->nastepny != NULL) {
        toDelete->nastepny->poprzedni = toDelete->poprzedni;
    }

    free(toDelete->material);
    free(toDelete);
    return *head;
}

void PrintList(Node* head, FILE* stream) {
    Node* current = head;
    while (current != NULL) {
        fprintf(stream, "%s %.2f %c\n", current->material->nazwa,
            current->material->gestosc, current->material->flaga);
        current = current->nastepny;
    }
}

void PrintActions() {
    printf("\n--- DOSTEPNE AKCJE ---\n");
    printf("1. Dodaj (push)\n2. Usun ostatni (pop)\n3. Dodaj na pozycji (pushAt)\n");
    printf("4. Usun z pozycji (popAt)\n5. Wyswietl liste\n6. Zapisz i Wyjdz\n");
    printf("Wybor: ");
}

void freeList(Node* head) {
    if (head == NULL) return;
    freeList(head->nastepny);
    free(head->material);
    free(head);
}