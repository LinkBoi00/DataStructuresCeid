#include <stdio.h>

#include "include/tree_by_date.h"
#include "include/tree_by_temp.h"
#include "include/hashing.h"

void read_from_file(TreeNode** treeRootPtr, HashTable** hashTablePtr, char* filename, int option);
int get_structure_choice(void);

void display_tree_by_date_menu(TreeNode* root);
void display_tree_by_temp_menu(TreeNode* root);
void display_hashing_menu(HashTable* table);
int get_user_input(void);
void clear_stdin(void);

int main(void) {
    TreeNode* treeRoot = NULL;
    HashTable* hashTable = NULL;

    // Get the structure choice from the user
    // 0: Date BST, 1: Temp BST, 2: Hashing, -1: Exit or invalid choice
    int structure_choice = get_structure_choice();
    if (structure_choice == -1) return 0;
    
    // Read the data from the file
    char* filename = "data/tempm.txt";
    read_from_file(&treeRoot, &hashTable, filename, structure_choice);

    // Print the appropriate submenu
    switch (structure_choice) {
        case 0:
            display_tree_by_date_menu(treeRoot);
            break;
        case 1:
            display_tree_by_temp_menu(treeRoot);
            break;
        case 2:
            display_hashing_menu(hashTable);            
            break;
        default:
            break;
    }

    // Free alloacated memory
    if (treeRoot != NULL) free_tree(treeRoot);
    if (hashTable != NULL) free_hash_table(hashTable);

    return 0;
}

// Function that returns the user's structure choice
// 0: Date oriented BST, 1: Average temp oriented BST
// 2: Hashing with chaining, -1: Exit or invalid choice
int get_structure_choice(void) {
    int option = -1;
    int result = -1;

    printf("\n");
    printf("-------------------- ΑΡΧΙΚΟ ΜΕΝΟΥ --------------------\n");
    printf("1. Φόρτωση αρχείου σε ΔΔΑ (Δυαδικό Δέντρο Αναζήτησης)\n");
    printf("2. Φόρτωση αρχείου σε δομή Hashing με αλυσίδες\n");
    printf("0. Έξοδος\n");
    printf("------------------------------------------------------\n");
    option = get_user_input();

    switch (option) {
        case 1:
            printf("\n");
            printf("-------------------- ΜΕΝΟΥ ΔΔΑ --------------------\n");
            printf("1. Φόρτωση σε ΔΔΑ με βάση την ΗΜΕΡΑ\n");
            printf("2. Φόρτωση σε ΔΔΑ με βάση την ΜΕΣΗ ΘΕΡΜΟΚΡΑΣΙΑ\n");
            printf("0. Έξοδος\n");
            printf("---------------------------------------------------\n");
            
            option = get_user_input();
            switch (option) {
                case 1:
                    result = 0;
                    break;
                case 2:
                    result = 1;
                    break;
                case 0:
                    result = -1;
                    break;
                default:
                    printf("Λανθασμένη επιλογή. Έξοδος...\n");
                    result = -1;
                    break;
            }
            break;
        case 2:
            result = 2;
            break;
        case 0:
            result = -1;
            break;
        default:
            printf("Λανθασμένη επιλογή. Έξοδος...\n");
            result = -1;
            break;
    }

    return result;
}

// Menu functions
void display_tree_by_date_menu(TreeNode* root) {
    int option;

    do {
        printf("\n");
        printf("-------------------------- ΜΕΝΟΥ ΔΔΑ (ΗΜΕΡΑ) --------------------------\n");
        printf("1. Απεικόνιση του ΔΔΑ με ενδο-διατεταγμένη διάσχιση\n");
        printf("2. Αναζήτηση της ΜΕΣΗΣ ΘΕΡΜΟΚΡΑΣΙΑΣ βάσει ΗΜΕΡΑΣ\n");
        printf("3. Τροποποίηση του πεδίου της ΜΕΣΗΣ ΘΕΡΜΟΚΡΑΣΙΑΣ για συγκεκριμένη ΗΜΕΡΑ\n");
        printf("4. Διαγραφή μιας εγγραφής που αντιστοιχεί σε συγκεκριμένη ΗΜΕΡΑ\n");
        printf("0. Έξοδος\n");
        printf("-----------------------------------------------------------------------\n");

        option = get_user_input();
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
            case 0:
                break;
            default:
                printf("Λανθασμένη επιλογή. Ξαναπροσπαθήστε.\n");
                break;
        }
    } while (option != 0);
}

void display_tree_by_temp_menu(TreeNode* root) {
    int option;

    do {
        printf("\n");
        printf("------------------- ΜΕΝΟΥ ΔΔΑ (ΜΕΣΗ ΘΕΡΜΟΚΡΑΣΙΑ) -------------------\n");
        printf("1. Εύρεση ΗΜΕΡΑΣ/ΗΜΕΡΩΝ με την ΕΛΑΧΙΣΤΗ ΜΕΣΗ ΘΕΡΜΟΚΡΑΣΙΑ\n");
        printf("2. Εύρεση ΗΜΕΡΑΣ/ΗΜΕΡΩΝ με τη ΜΕΓΙΣΤΗ ΜΕΣΗ ΘΕΡΜΟΚΡΑΣΙΑ\n");
        printf("3. Απεικόνιση του ΔΔΑ με ενδο-διατεταγμένη διάσχιση (debugging)\n");
        printf("0. Έξοδος\n");
        printf("--------------------------------------------------------------------\n");

        option = get_user_input();

        switch (option) {
            case 1:
                find_days_with_min_temp(root);
                break;
            case 2:
                find_days_with_max_temp(root);
                break;
            case 3:
                print_tree_inorder(root);
                break;
            case 0:
                break;
            default:
                printf("Λανθασμένη επιλογή. Ξαναπροσπαθηστε.\n");
                break;
        }
    } while (option != 0);
}

void display_hashing_menu(HashTable* table) {
    int option;

    do {
        printf("\n");
        printf("------------------- ΜΕΝΟΥ HASHING ΜΕ ΑΛΥΣΙΔΕΣ ------------------------\n");
        printf("1. Αναζήτηση ΜΕΣΗΣ ΘΕΡΜΟΚΡΑΣΙΑΣ βάσει ΗΜΕΡΑΣ\n");
        printf("2. Τροποποίηση ΜΕΣΗΣ ΘΕΡΜΟΚΡΑΣΙΑΣ βάσει ΗΜΕΡΑΣ\n");
        printf("3. Διαγραφή μιας εγγραφής απο τον πίνακα κατακερματισμού βάσει ΗΜΕΡΑΣ\n");
        printf("4. Εκτύπωση του πίνακα κατακερματισμού (Debugging)\n");
        printf("0. Έξοδος\n");
        printf("----------------------------------------------------------------------\n");

        option = get_user_input();

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
            case 0:
                break;
            default:
                printf("Λανθασμένη επιλογή. Ξαναπροσπαθήστε.\n");
                break;
        }
    } while (option != 0);
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
void read_from_file(TreeNode** treeRootPtr, HashTable** hashTablePtr, char* filename, int option) {
    if (filename == NULL) {
        printf("read_from_file: Filename is invalid.\n");
        return;
    }

    if (option < 0 || option > 2) {
        printf("read_from_file: Invalid option.\n");
        return;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
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

            // Insert the node to the structure (based on option)
            switch (option) {
                case 0:
                    *treeRootPtr = insert_by_date(*treeRootPtr, date, average_temp);
                    break;
                case 1:
                    *treeRootPtr = insert_by_temp(*treeRootPtr, date, average_temp);
                    break;
                case 2:
                    if (*hashTablePtr == NULL) *hashTablePtr = create_hash_table();
                    if (*hashTablePtr == NULL) {
                        printf("read_from_file: Failed to create hash table.\n");
                        return;
                    }
                    insert_hash_table(*hashTablePtr, date, average_temp);
                    break;
                default:
                    break;
            }
        }
    }
}