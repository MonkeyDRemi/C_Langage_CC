#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_row(Row *row) {
    if (row) {
        printf("ID: %d, Name: %s, Email: %s, Age: %d\n", row->id, row->name, row->email, row->age);
    } else {
        printf("Ligne non trouvee\n");
    }
}

//afficher toutes les lignes d'une table
void print_all_rows(Table *table) {
    Node *current = table->head; // Parcourt la liste chainee
    while (current) {
        print_row(&current->row); 
        current = current->next; //nœud suivant
    }
}

int main() {
    Table *table = NULL; // initialiser la table à NULL
    char command[256]; //pour stocker la commande user

    printf("Bienvenue dans la BDD. Ecrire 'EXIT' pour quitter.\n");

    while (1) {
        printf("db> ");
        fgets(command, sizeof(command), stdin); // Lecture de la commande
        command[strcspn(command, "\n")] = 0; // supprime le caractère '\n'

        // creer une table
        if (strncmp(command, "CREATE", 6) == 0) {
            char name[256];
            sscanf(command + 7, "%s", name);
            if (table) free_table(table); // libère la table si existe
            table = create_table(name); 
            printf("Table '%s' creee.\n", name);

        // inserer une ligne
        } else if (strncmp(command, "INSERT", 6) == 0) {
            if (!table) {
                printf("Aucune table creer. Utiliser 'CREATE'.\n");
                continue;
            }
            int id, age;
            char name[256], email[256];
            sscanf(command + 7, "%d %s %s %d", &id, name, email, &age); // recupère les valeurs
            insert_row(table, (Row){id, strdup(name), strdup(email), age}); // insère la ligne
            printf("Row inserted: ID=%d, Name=%s, Email=%s, Age=%d\n", id, name, email, age);

        // Commande pour rechercher une ligne
        } else if (strncmp(command, "SELECT", 6) == 0) {
            if (!table) {
                printf("Aucune table creer. Utiliser 'CREATE'.\n");
                continue;
            }
            int id;
            sscanf(command + 7, "%d", &id); // recupère l'ID de la ligne
            Row *row = select_row(table, id); 
            print_row(row); // afiche la ligne si trouvee

        // supprimer une ligne
        } else if (strncmp(command, "DELETE", 6) == 0) {
            if (!table) {
                printf("Aucune table creee. Utiliser 'CREATE'.\n");
                continue;
            }
            int id;
            sscanf(command + 7, "%d", &id); // recupère l'id de la ligne
            delete_row(table, id);
            printf("Row with ID %d deleted.\n", id);

        // affiche toutes les lignes
        } else if (strncmp(command, "SHOW", 4) == 0) {
            if (!table) {
                printf("Aucune table creee. Utiliser 'CREATE'.\n");
                continue;
            }
            print_all_rows(table);

        //sauvegarder de la table
        } else if (strncmp(command, "SAVE", 4) == 0) {
            if (!table) {
                printf("Aucune table creee. Utiliser 'CREATE'.\n");
                continue;
            }
            char filename[256];
            sscanf(command + 5, "%s", filename); 
            save_table(table, filename); // Sauvegarde les donnees dans le fichier
            printf("Table sauvegardee dans '%s'.\n", filename);

        // Charger une table depuis un fichier
        } else if (strncmp(command, "LOAD", 4) == 0) {
            char filename[256];
            sscanf(command + 5, "%s", filename);
            if (table) free_table(table); // Libère la table actuelle si elle existe
            table = load_table(filename); 
            printf("Table chargee depuis '%s'.\n", filename);

        // Commande pour quitter le programme
        } else if (strncmp(command, "EXIT", 4) == 0) {
            printf("Quitter...\n");
            break;

        } else {
            printf("Commande inconnue! Commandes autorisees: CREATE, INSERT, SELECT, DELETE, SHOW, SAVE, LOAD, EXIT.\n");
        }
    }

    // Libère les ressources 
    if (table) free_table(table);
    return 0;
}
