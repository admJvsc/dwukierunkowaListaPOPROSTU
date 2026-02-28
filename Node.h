#ifndef NODE_H
#define NODE_H
#include "Material.h"

typedef struct Node {
    struct Material* material;
    struct Node* nastepny;
    struct Node* poprzedni;
} Node;

#endif