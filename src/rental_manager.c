#include "rental_manager.h"

// Initialize the rental manager
void init_rental_manager(RentalManager *manager) {
    manager->scooter_count = 0;
    manager->customer_count = 0;
    manager->rental_count = 0;
}

// Add a new scooter to the system
int add_scooter(RentalManager *manager, const char *model, const char *reg_number, float hourly_rate) {
    if (manager->scooter_count >= MAX_SCOOTERS) {
        printf("Error: Maximum scooter limit reached!\n");
        return -1;
    }

    Scooter *new_scooter = &manager->scooters[manager->scooter_count];
    new_scooter->scooter_id = manager->scooter_count + 1;
    strncpy(new_scooter->model, model, MAX_MODEL_LENGTH - 1);
    new_scooter->model[MAX_MODEL_LENGTH - 1] = '\0';
    strncpy(new_scooter->registration_number, reg_number, 19);
    new_scooter->registration_number[19] = '\0';
    new_scooter->hourly_rate = hourly_rate;
    new_scooter->battery_level = 100;
    new_scooter->status = AVAILABLE;

    manager->scooter_count++;
    printf("Scooter added successfully! ID: %d\n", new_scooter->scooter_id);
    return new_scooter->scooter_id;
}

// Remove a scooter from the system
int remove_scooter(RentalManager *manager, int scooter_id) {
    for (int i = 0; i < manager->scooter_count; i++) {
        if (manager->scooters[i].scooter_id == scooter_id) {
            if (manager->scooters[i].status == RENTED) {
                printf("Error: Cannot remove a scooter that is currently rented!\n");
                return -1;
            }

            // Shift remaining scooters
            for (int j = i; j < manager->scooter_count - 1; j++) {
                manager->scooters[j] = manager->scooters[j + 1];
            }
            manager->scooter_count--;
            printf("Scooter removed successfully!\n");
            return 0;
        }
    }
    printf("Error: Scooter not found!\n");
    return -1;
}

// Display all scooters
void display_scooters(RentalManager *manager) {
    if (manager->scooter_count == 0) {
        printf("No scooters in the system.\n");
        return;
    }

    printf("\n========== ALL SCOOTERS ==========\n");
    printf("%-5s %-20s %-15s %-10s %-10s %-12s\n", 
           "ID", "Model", "Reg. Number", "Rate/Hr", "Battery", "Status");
    printf("---------------------------------------------------------------------\n");

    for (int i = 0; i < manager->scooter_count; i++) {
        Scooter *s = &manager->scooters[i];
        const char *status_str;
        switch (s->status) {
            case AVAILABLE: status_str = "Available"; break;
            case RENTED: status_str = "Rented"; break;
            case MAINTENANCE: status_str = "Maintenance"; break;
            default: status_str = "Unknown";
        }
        printf("%-5d %-20s %-15s $%-9.2f %-10d%% %-12s\n",
               s->scooter_id, s->model, s->registration_number,
               s->hourly_rate, s->battery_level, status_str);
    }
    printf("==================================\n\n");
}

// Display only available scooters
void display_available_scooters(RentalManager *manager) {
    int available_count = 0;

    printf("\n========== AVAILABLE SCOOTERS ==========\n");
    printf("%-5s %-20s %-15s %-10s %-10s\n", 
           "ID", "Model", "Reg. Number", "Rate/Hr", "Battery");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < manager->scooter_count; i++) {
        Scooter *s = &manager->scooters[i];
        if (s->status == AVAILABLE) {
            printf("%-5d %-20s %-15s $%-9.2f %-10d%%\n",
                   s->scooter_id, s->model, s->registration_number,
                   s->hourly_rate, s->battery_level);
            available_count++;
        }
    }

    if (available_count == 0) {
        printf("No scooters available for rent.\n");
    }
    printf("========================================\n\n");
}

// Find a scooter by ID
Scooter* find_scooter(RentalManager *manager, int scooter_id) {
    for (int i = 0; i < manager->scooter_count; i++) {
        if (manager->scooters[i].scooter_id == scooter_id) {
            return &manager->scooters[i];
        }
    }
    return NULL;
}

// Add a new customer
int add_customer(RentalManager *manager, const char *name, const char *phone, const char *license) {
    if (manager->customer_count >= MAX_CUSTOMERS) {
        printf("Error: Maximum customer limit reached!\n");
        return -1;
    }

    Customer *new_customer = &manager->customers[manager->customer_count];
    new_customer->customer_id = manager->customer_count + 1;
    strncpy(new_customer->name, name, MAX_NAME_LENGTH - 1);
    new_customer->name[MAX_NAME_LENGTH - 1] = '\0';
    strncpy(new_customer->phone, phone, MAX_PHONE_LENGTH - 1);
    new_customer->phone[MAX_PHONE_LENGTH - 1] = '\0';
    strncpy(new_customer->license_number, license, 19);
    new_customer->license_number[19] = '\0';
    new_customer->total_rentals = 0;

    manager->customer_count++;
    printf("Customer registered successfully! ID: %d\n", new_customer->customer_id);
    return new_customer->customer_id;
}

// Display all customers
void display_customers(RentalManager *manager) {
    if (manager->customer_count == 0) {
        printf("No customers registered.\n");
        return;
    }

    printf("\n========== ALL CUSTOMERS ==========\n");
    printf("%-5s %-25s %-15s %-15s %-10s\n", 
           "ID", "Name", "Phone", "License", "Rentals");
    printf("-----------------------------------------------------------------------\n");

    for (int i = 0; i < manager->customer_count; i++) {
        Customer *c = &manager->customers[i];
        printf("%-5d %-25s %-15s %-15s %-10d\n",
               c->customer_id, c->name, c->phone, 
               c->license_number, c->total_rentals);
    }
    printf("===================================\n\n");
}

// Find a customer by ID
Customer* find_customer(RentalManager *manager, int customer_id) {
    for (int i = 0; i < manager->customer_count; i++) {
        if (manager->customers[i].customer_id == customer_id) {
            return &manager->customers[i];
        }
    }
    return NULL;
}

// Start a new rental
int start_rental(RentalManager *manager, int customer_id, int scooter_id) {
    if (manager->rental_count >= MAX_RENTALS) {
        printf("Error: Maximum rental limit reached!\n");
        return -1;
    }

    Customer *customer = find_customer(manager, customer_id);
    if (customer == NULL) {
        printf("Error: Customer not found!\n");
        return -1;
    }

    Scooter *scooter = find_scooter(manager, scooter_id);
    if (scooter == NULL) {
        printf("Error: Scooter not found!\n");
        return -1;
    }

    if (scooter->status != AVAILABLE) {
        printf("Error: Scooter is not available!\n");
        return -1;
    }

    Rental *new_rental = &manager->rentals[manager->rental_count];
    new_rental->rental_id = manager->rental_count + 1;
    new_rental->scooter_id = scooter_id;
    new_rental->customer_id = customer_id;
    new_rental->start_time = time(NULL);
    new_rental->end_time = 0;
    new_rental->total_cost = 0.0;
    new_rental->is_active = 1;

    scooter->status = RENTED;
    customer->total_rentals++;
    manager->rental_count++;

    printf("Rental started successfully! Rental ID: %d\n", new_rental->rental_id);
    printf("Customer: %s | Scooter: %s (%s)\n", 
           customer->name, scooter->model, scooter->registration_number);
    return new_rental->rental_id;
}

// End a rental
int end_rental(RentalManager *manager, int rental_id) {
    for (int i = 0; i < manager->rental_count; i++) {
        if (manager->rentals[i].rental_id == rental_id) {
            Rental *rental = &manager->rentals[i];

            if (!rental->is_active) {
                printf("Error: Rental is already completed!\n");
                return -1;
            }

            rental->end_time = time(NULL);
            rental->is_active = 0;

            Scooter *scooter = find_scooter(manager, rental->scooter_id);
            if (scooter != NULL) {
                scooter->status = AVAILABLE;
                rental->total_cost = calculate_rental_cost(rental, scooter);
            }

            Customer *customer = find_customer(manager, rental->customer_id);

            printf("\nRental completed successfully!\n");
            printf("Rental ID: %d\n", rental->rental_id);
            if (customer != NULL) {
                printf("Customer: %s\n", customer->name);
            }
            if (scooter != NULL) {
                printf("Scooter: %s (%s)\n", scooter->model, scooter->registration_number);
            }
            printf("Duration: %.2f hours\n", (double)(rental->end_time - rental->start_time) / 3600.0);
            printf("Total Cost: $%.2f\n\n", rental->total_cost);

            return 0;
        }
    }
    printf("Error: Rental not found!\n");
    return -1;
}

// Display active rentals
void display_active_rentals(RentalManager *manager) {
    int active_count = 0;

    printf("\n========== ACTIVE RENTALS ==========\n");
    printf("%-8s %-8s %-8s %-25s %-20s\n", 
           "Rental", "Customer", "Scooter", "Customer Name", "Scooter Model");
    printf("-------------------------------------------------------------------------\n");

    for (int i = 0; i < manager->rental_count; i++) {
        Rental *r = &manager->rentals[i];
        if (r->is_active) {
            Customer *customer = find_customer(manager, r->customer_id);
            Scooter *scooter = find_scooter(manager, r->scooter_id);

            printf("%-8d %-8d %-8d %-25s %-20s\n",
                   r->rental_id, r->customer_id, r->scooter_id,
                   customer ? customer->name : "Unknown",
                   scooter ? scooter->model : "Unknown");
            active_count++;
        }
    }

    if (active_count == 0) {
        printf("No active rentals.\n");
    }
    printf("====================================\n\n");
}

// Display rental history
void display_rental_history(RentalManager *manager) {
    if (manager->rental_count == 0) {
        printf("No rental history.\n");
        return;
    }

    printf("\n========== RENTAL HISTORY ==========\n");
    printf("%-8s %-8s %-8s %-20s %-10s %-10s\n", 
           "Rental", "Customer", "Scooter", "Duration (hrs)", "Cost", "Status");
    printf("--------------------------------------------------------------------\n");

    for (int i = 0; i < manager->rental_count; i++) {
        Rental *r = &manager->rentals[i];
        double duration = 0.0;

        if (!r->is_active && r->end_time > 0) {
            duration = (double)(r->end_time - r->start_time) / 3600.0;
        }

        printf("%-8d %-8d %-8d %-20.2f $%-9.2f %-10s\n",
               r->rental_id, r->customer_id, r->scooter_id,
               duration, r->total_cost,
               r->is_active ? "Active" : "Completed");
    }
    printf("====================================\n\n");
}

// Calculate rental cost based on duration
float calculate_rental_cost(Rental *rental, Scooter *scooter) {
    if (rental->end_time == 0) {
        return 0.0;
    }

    double hours = (double)(rental->end_time - rental->start_time) / 3600.0;
    return (float)(hours * scooter->hourly_rate);
}

// Update scooter status
void update_scooter_status(RentalManager *manager, int scooter_id, ScooterStatus status) {
    Scooter *scooter = find_scooter(manager, scooter_id);
    if (scooter != NULL) {
        scooter->status = status;
        printf("Scooter status updated successfully!\n");
    } else {
        printf("Error: Scooter not found!\n");
    }
}

// Display main menu
void display_menu() {
    printf("\n========================================\n");
    printf("   SCOOTER RENTAL MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1.  Add Scooter\n");
    printf("2.  Display All Scooters\n");
    printf("3.  Display Available Scooters\n");
    printf("4.  Remove Scooter\n");
    printf("5.  Add Customer\n");
    printf("6.  Display All Customers\n");
    printf("7.  Start Rental\n");
    printf("8.  End Rental\n");
    printf("9.  Display Active Rentals\n");
    printf("10. Display Rental History\n");
    printf("11. Update Scooter Status\n");
    printf("0.  Exit\n");
    printf("========================================\n");
    printf("Enter your choice: ");
}
