#include <stdio.h>
#include <stdlib.h>
#include "LinkedListBidirectional.h"
#include <string.h>

int main(void) {
    Node* list = NULL;

    FILE* file = fopen("dane.txt", "r");
    if (file == NULL) {
        printf("Blad");
    }

    if (file) {
        char name[100];
        double g;
        char f;
        while (fscanf(file, "%s %lf %c", name, &g, &f) == 3) {
            Material* m = malloc(sizeof(Material));
            strcpy(m->nazwa, name);
            m->gestosc = g;
            m->flaga = f;
            push(&list, m);
        }
        fclose(file);
        printf("Wczytano dane z pliku");
    }

    int wybor = 0;
    while (wybor != 6) {
        PrintActions();
        scanf("%d", &wybor);

        if (wybor == 1) {
            Material* m = malloc(sizeof(Material));
            printf("Nazwa: "); scanf("%s", m->nazwa);
            printf("Gestosc: "); scanf("%lf", &m->gestosc);
            printf("Flaga: "); scanf(" %c", &m->flaga);
            push(&list, m);
        } else if (wybor == 5) {
            PrintList(list, stdout);
        } else if (wybor == 6) {
            FILE* saveplik = fopen("dane.txt", "w");
            if (saveplik == NULL) {
                printf("Blad");
            }

            if (saveplik) {
                PrintList(list, saveplik);
                fclose(saveplik);
            }
        }
    }
    freeList(list);
    return 0;
}