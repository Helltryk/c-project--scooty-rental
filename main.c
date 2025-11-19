/*
 * main.c
 *
 * Contains the main application loop and user interface functions.
 * Relies on rental_manager.h for all data logic.
 */


#include "rental_manager.h" 

/* --- UI/HELPER FUNCTIONS --- */

/**
 * Displays the main menu options to the user.
 */
void display_menu() {
    printf("\n--- Scooty Rental Management ---\n");
    printf("1. Start New Rental\n");
    printf("2. End Active Rental\n");
    printf("3. View All Rental Records\n");
    printf("4. Exit and Save\n");
    printf("5. Search Records\n"); 
    printf("Enter your choice: ");
}

/**
 *Clears the stdin input buffer.
 */
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* --- MAIN APPLICATION --- */

int main() {
    RentalRecord *records = NULL; 
    int record_count = 0;         
    int choice;

    printf("Initializing Scooty Rental System...\n");

    if (!load_data(&records, &record_count)) {
        printf("System failed to initialize. Exiting.\n");
        return 1;
    }

    do {
        display_menu();
        if (scanf("%d", &choice) != 1) {
            choice = 0; 
        }
        clear_input_buffer(); 

        switch (choice) {
            case 1:
                add_new_rental(&records, &record_count); 
                break;
            case 2:
                end_active_rental(&records, &record_count); 
                break;
            case 3:
                view_all_rentals(records, record_count); 
                break;
            case 4:
                printf("\nExiting system. Saving data...\n");
                break;
            case 5:
                search_records(records, record_count); 
                break;
            default:
                printf("[WARNING] Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    save_data(records, record_count); 

    if (records != NULL) {
        free(records);
        records = NULL;
    }
    printf("Memory cleanup complete. Goodbye!\n");
    return 0;
}