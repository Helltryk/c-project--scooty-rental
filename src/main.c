#include "rental_manager.h"

int main() {
    RentalManager manager;
    init_rental_manager(&manager);

    int choice;
    char model[MAX_MODEL_LENGTH];
    char reg_number[20];
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char license[20];
    float hourly_rate;
    int scooter_id, customer_id, rental_id, status;

    // Add some sample data for demonstration
    printf("Initializing system with sample data...\n");
    add_scooter(&manager, "Honda Activa", "MH12AB1234", 5.50);
    add_scooter(&manager, "TVS Jupiter", "MH12CD5678", 5.00);
    add_scooter(&manager, "Suzuki Access", "MH12EF9012", 6.00);
    add_scooter(&manager, "Hero Maestro", "MH12GH3456", 5.25);

    add_customer(&manager, "Rajesh Kumar", "9876543210", "DL1234567890");
    add_customer(&manager, "Priya Sharma", "9876543211", "DL0987654321");
    printf("\nSystem initialized!\n");

    while (1) {
        display_menu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        while (getchar() != '\n'); // Clear newline

        switch (choice) {
            case 1: // Add Scooter
                printf("\nEnter scooter model: ");
                fgets(model, MAX_MODEL_LENGTH, stdin);
                model[strcspn(model, "\n")] = 0; // Remove newline

                printf("Enter registration number: ");
                fgets(reg_number, 20, stdin);
                reg_number[strcspn(reg_number, "\n")] = 0;

                printf("Enter hourly rate: $");
                scanf("%f", &hourly_rate);
                while (getchar() != '\n');

                add_scooter(&manager, model, reg_number, hourly_rate);
                break;

            case 2: // Display All Scooters
                display_scooters(&manager);
                break;

            case 3: // Display Available Scooters
                display_available_scooters(&manager);
                break;

            case 4: // Remove Scooter
                printf("\nEnter scooter ID to remove: ");
                scanf("%d", &scooter_id);
                while (getchar() != '\n');
                remove_scooter(&manager, scooter_id);
                break;

            case 5: // Add Customer
                printf("\nEnter customer name: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = 0;

                printf("Enter phone number: ");
                fgets(phone, MAX_PHONE_LENGTH, stdin);
                phone[strcspn(phone, "\n")] = 0;

                printf("Enter license number: ");
                fgets(license, 20, stdin);
                license[strcspn(license, "\n")] = 0;

                add_customer(&manager, name, phone, license);
                break;

            case 6: // Display All Customers
                display_customers(&manager);
                break;

            case 7: // Start Rental
                printf("\nEnter customer ID: ");
                scanf("%d", &customer_id);
                printf("Enter scooter ID: ");
                scanf("%d", &scooter_id);
                while (getchar() != '\n');

                start_rental(&manager, customer_id, scooter_id);
                break;

            case 8: // End Rental
                printf("\nEnter rental ID to complete: ");
                scanf("%d", &rental_id);
                while (getchar() != '\n');
                end_rental(&manager, rental_id);
                break;

            case 9: // Display Active Rentals
                display_active_rentals(&manager);
                break;

            case 10: // Display Rental History
                display_rental_history(&manager);
                break;

            case 11: // Update Scooter Status
                printf("\nEnter scooter ID: ");
                scanf("%d", &scooter_id);
                printf("Enter status (0=Available, 1=Rented, 2=Maintenance): ");
                scanf("%d", &status);
                while (getchar() != '\n');

                if (status >= 0 && status <= 2) {
                    update_scooter_status(&manager, scooter_id, (ScooterStatus)status);
                } else {
                    printf("Invalid status!\n");
                }
                break;

            case 0: // Exit
                printf("\nThank you for using Scooter Rental Management System!\n");
                printf("Goodbye!\n\n");
                return 0;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}
