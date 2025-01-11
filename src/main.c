#include "database.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Bienvenue dans le gestionnaire de base de données.\n");
    Table *table = create_table("default_table");

    // Affichage pour vérifier la création de la table
    printf("Table créée : %s\n", table->name);

    free_table(table); // Libération des ressources
    return 0;
}
