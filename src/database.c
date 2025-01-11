// database.c
#include "database.h"
#include <string.h>
#include <stdio.h>

// Création d'une nouvelle table
Table *create_table(const char *name) {
    Table *table = malloc(sizeof(Table));
    table->name = strdup(name);
    table->head = NULL;
    return table;
}

// Libération des ressources associées à une table
void free_table(Table *table) {
    if (!table) return;

    Node *current = table->head;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    free(table->name);
    free(table);
}
