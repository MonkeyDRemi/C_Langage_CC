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


// Insertion d'une ligne dans la table
void insert_row(Table *table, Row row) {
    Node *new_node = malloc(sizeof(Node));
    new_node->row = row;
    new_node->next = table->head;
    table->head = new_node;
}


// Recherche d'une ligne par ID
Row *select_row(Table *table, int id) {
    Node *current = table->head;
    while (current) {
        if (current->row.id == id) {
            return &current->row;
        }
        current = current->next;
    }
    return NULL;
}



// Suppression d'une ligne par ID
void delete_row(Table *table, int id) {
    Node *current = table->head;
    Node *previous = NULL;

    while (current) {
        if (current->row.id == id) {
            if (previous) {
                previous->next = current->next;
            } else {
                table->head = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}


// Affichage de toutes les lignes d'une table
void print_all_rows(Table *table) {
    Node *current = table->head;
    while (current) {
        printf("ID: %d, Nom: %s, Email: %s, Age: %d\n", current->row.id, current->row.name, current->row.email, current->row.age);
        current = current->next;
    }
}



// Sauvegarde des données de la table dans un fichier
void save_table(Table *table, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    fwrite(table->name, sizeof(char), strlen(table->name) + 1, file);

    Node *current = table->head;
    while (current) {
        fwrite(&current->row, sizeof(Row), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Table sauvegardée dans '%s'.\n", filename);
}
