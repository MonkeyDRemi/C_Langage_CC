// database.h
#ifndef DATABASE_H
#define DATABASE_H

#include <stdlib.h>

// Structure pour une ligne
typedef struct Row {
    int id;
    char *name;
    char *email;
    int age;
} Row;

// Structure pour un nœud de liste chaînée
typedef struct Node {
    Row row;
    struct Node *next;
} Node;

// Structure pour une table
typedef struct Table {
    char *name;
    Node *head;
} Table;

// Fonctions principales
Table *create_table(const char *name);
void free_table(Table *table);

#endif
