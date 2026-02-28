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

Node* getElementAt(Node* head, int index) {
    if (head == NULL || index < 0) return NULL;
    if (index == 0) return head;
    return getElementAt(head->nastepny, index - 1);
}

void PrintList(Node* head, FILE* stream) {
    Node* current = head;
    while (current != NULL) {
        fprintf(stream, "%s %.2f %c\n ", current->material->nazwa,
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