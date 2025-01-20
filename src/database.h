#ifndef DATABASE_H
#define DATABASE_H
#include <stdlib.h>

// Structure table
typedef struct Row {
    int id;
    char *name;
    char *email;
    int age;
} Row;

// Nœud Liste Chainee
typedef struct Node {
    Row row;		// donnee de la ligne
    struct Node *next;	// pointeur du prochain noeud
} Node;

// Table
typedef struct Table {
    char *name;
    Node *head;
} Table;

// Fonctions principales
Table *create_table(const char *name);
void free_table(Table *table);
void insert_row(Table *table, Row row);
Row *select_row(Table *table, int id);
void delete_row(Table *table, int id);
void save_table(Table *table, const char *filename);
Table *load_table(const char *filename);

#endif
