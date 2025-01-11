#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("Bienvenue dans le gestionnaire de base de données.\n");
    
    Table *table = NULL;
    char command[256];

    while (1) {
        printf("db> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;

        if (strncmp(command, "CREATE", 6) == 0) {
            char name[256];
            sscanf(command + 7, "%s", name);
            if (table) free_table(table);
            table = create_table(name);
            printf("Table '%s' créée.\n", name);
        } else if (strncmp(command, "EXIT", 4) == 0) {
            printf("Quitter...\n");
            break;
        } else {
            printf("Commande inconnue! Utilisez CREATE ou EXIT.\n");
        }
    }

    if (table) free_table(table);
    return 0;
}
