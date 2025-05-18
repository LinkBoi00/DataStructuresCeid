#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/hashing.h"

HashTable* build_tree_from_file(char* filename);

int get_hashing_choice(void);
void display_hashing_menu(HashTable* table);
int get_user_input(void);
void clear_stdin(void);

int main(void) {
    HashTable* table = build_tree_from_file("data/tempm.txt");

    display_hashing_menu(table);

    free_hash_table(table);
    return 0;
}

int get_hashing_choice(void) {
    printf("\n");
    printf("------------------- ΜΕΝΟΥ HASHING ΜΕ ΑΛΥΣΙΔΕΣ ------------------------\n");
    printf("1. Αναζήτηση ΜΕΣΗΣ ΘΕΡΜΟΚΡΑΣΙΑΣ βάσει ΗΜΕΡΑΣ\n");
    printf("2. Τροποποίηση ΜΕΣΗΣ ΘΕΡΜΟΚΡΑΣΙΑΣ βάσει ΗΜΕΡΑΣ\n");
    printf("3. Διαγραφή μιας εγγραφής απο τον πίνακα κατακερματισμού βάσει ΗΜΕΡΑΣ\n");
    printf("4. Εκτύπωση του πίνακα κατακερματισμού (Debugging)\n");
    printf("0. Έξοδος\n");
    printf("----------------------------------------------------------------------\n");
    
    return get_user_input();
}

void display_hashing_menu(HashTable* table) {
    int option;

    while ((option = get_hashing_choice()) != 0) {
        switch (option) {
            case 1:
                printf("Εισάγετε ΗΜΕΡΑ για αναζήτηση ΜΕΣΗΣ ΘΕΡΜΟΚΡΑΣΙΑΣ: ");
                search_in_hash_table(table);
                clear_stdin();
                break;
            case 2:
                printf("Εισάγετε ΗΜΕΡΑ για τροποποίηση της ΜΕΣΗΣ ΘΕΡΜΟΚΡΑΣΙΑΣ: ");
                edit_hash_table_temperature(table);
                break;
            case 3:
                printf("Εισάγετε ΗΜΕΡΑ για διαγραφή εγγραφής: ");
                delete_hash_table_entry(table);
                clear_stdin();
                break;
            case 4:
                print_hash_table(table);
                break;
            default:
                printf("Λανθασμένη επιλογή. Ξαναπροσπαθηστε.\n");
                break;

        }
    }
}

int get_user_input(void) {
    int option = -1;

    printf("Εισάγετε την επιλογή σας: ");
    scanf("%d", &option);
    clear_stdin();

    return option;
}

void clear_stdin(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// File reading functions
HashTable* build_tree_from_file(char* filename) {
    if (filename == NULL) {
        printf("build_tree_from_file: Filename is invalid.\n");
        return NULL;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    HashTable* table = create_hash_table();
    if (table == NULL) {
        fclose(file);
        return NULL;
    }

    int c;
    unsigned int i = 0;
    while ((c = fgetc(file)) != EOF) {
        if (c == '{') {
            int values_count = 0;
            char date[MAX_DATE_LEN] = { 0 };
            char valueStr[32] = { 0 };
            double average_temp = 0.0;

            // Skip to the first quote
            while ((c = fgetc(file)) != '"' && c != EOF);
            if (c == EOF) break;

            // Parse the first timestamp to extract the date
            i = 0;
            while ((c = fgetc(file)) != '"' && c != EOF && i < MAX_DATE_LEN - 1) {
                date[i++] = c;
            }
            date[i] = '\0';

            // Skip to timestamp end quote
            while ((c = fgetc(file)) != '"' && c != EOF);
            if (c == EOF) break;

            // Skip to value start quote
            while ((c = fgetc(file)) != '"' && c != EOF);
            if (c == EOF) break;
            
            // Parse the first value
            i = 0;
            while ((c = fgetc(file)) != '"' && c != EOF && i < sizeof(valueStr) - 1) {
                valueStr[i++] = c;
            }
            if (c == EOF || c == '}') break;
            valueStr[i] = '\0';
            average_temp += atof(valueStr);
            values_count++;
            
            // Parse the rest of the values
            while ((c = fgetc(file)) != '}' && c != EOF) {
                // Skip whitespace, commas, newlines, etc.
                while (((c = fgetc(file)) == ' ' || c == ',' || c == '\n' || c == '\r') && c != EOF);
                if (c == '}' || c == EOF) break;
                
                // Expecting quote for timestamp key
                if (c != '"') break;

                // Skip the timestamp key (until next quote)
                while ((c = fgetc(file)) != '"' && c != EOF);
                if (c == EOF) break;

                // Skip to colon ':'
                while ((c = fgetc(file)) != ':' && c != EOF && c != '}');
                if (c == EOF || c == '}') break;

                // Skip to opening quote of value
                while ((c = fgetc(file)) != '"' && c != EOF && c != '}');
                
                // Get the value
                i = 0;
                while ((c = fgetc(file)) != '"' && c != EOF && c != '}' && i < sizeof(valueStr) - 1) {
                    valueStr[i++] = c;
                }
                if (c == EOF || c == '}') break;
                valueStr[i] = '\0';
                values_count++;
                average_temp += atof(valueStr);
            }
            
            // Calculate average temperature for the day
            average_temp /= values_count;
            insert_hash_table(table, date, average_temp);
        }
    }

    fclose(file);
    return table;
}