#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "include/tree_by_date.h"

int get_tree_by_date_choice();
void display_tree_by_date_menu(TreeNode* root);
int get_user_input();
void clear_stdin();

TreeNode* build_tree_from_file(char* filename);

int main(void) {
    TreeNode* root = build_tree_from_file("data/tempm.txt");

    // Display menu
    display_tree_by_date_menu(root);

    free_tree(root);
    return 0;
}

// Menu functions
int get_tree_by_date_choice() {
    printf("\n");
    printf("-------------------------- ΜΕΝΟΥ ΔΔΑ (ΗΜΕΡΑ) --------------------------\n");
    printf("1. Απεικόνιση του ΔΔΑ με ενδο-διατεταγμένη διάσχιση\n");
    printf("2. Αναζήτηση της ΜΕΣΗΣ ΘΕΡΜΟΚΡΑΣΙΑΣ βάσει ΗΜΕΡΑΣ\n");
    printf("3. Τροποποίηση του πεδίου της ΜΕΣΗΣ ΘΕΡΜΟΚΡΑΣΙΑΣ για συγκεκριμένη ΗΜΕΡΑ\n");
    printf("4. Διαγραφή μιας εγγραφής που αντιστοιχεί σε συγκεκριμένη ΗΜΕΡΑ\n");
    printf("0. Έξοδος\n");
    printf("-----------------------------------------------------------------------\n");
    
    return get_user_input();
}

void display_tree_by_date_menu(TreeNode* root) {
    int option;

    while ((option = get_tree_by_date_choice()) != 0) {
        switch (option) {
            case 1:
                print_tree_inorder(root);
                break;
            case 2:
                printf("Εισάγετε ΗΜΕΡΑ για αναζήτηση ΜΕΣΗΣ ΘΕΡΜΟΚΡΑΣΙΑΣ: ");
                search_by_date(root);
                clear_stdin();
                break;
            case 3:
                printf("Εισάγετε ΗΜΕΡΑ για τροποποίηση της ΜΕΣΗΣ ΘΕΡΜΟΚΡΑΣΙΑΣ: ");
                edit_temperature_by_date(root);
                clear_stdin();
                break;
            case 4:
                printf("Εισάγετε ΗΜΕΡΑ για διαγραφή εγγραφής: ");
                delete_by_date(root);
                clear_stdin();
                break;
            default:
                printf("Λανθασμένη επιλογή. Ξαναπροσπαθήστε.\n");
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
TreeNode* build_tree_from_file(char* filename) {
    TreeNode* root = NULL;

    if (filename == NULL) {
        printf("build_tree_from_file: Filename is invalid.\n");
        return NULL;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
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
            root = insert_by_date(root, date, average_temp);
        }
    }

    return root;
}

