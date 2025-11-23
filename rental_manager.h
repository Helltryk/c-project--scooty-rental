#ifndef RENTAL_MANAGER_H
#define RENTAL_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SCOOTERS 100
#define MAX_CUSTOMERS 100
#define MAX_RENTALS 100
#define MAX_NAME_LENGTH 50
#define MAX_MODEL_LENGTH 50
#define MAX_PHONE_LENGTH 15

// Scooter status enumeration
typedef enum {
    AVAILABLE,
    RENTED,
    MAINTENANCE
} ScooterStatus;

// Scooter structure
typedef struct {
    int scooter_id;
    char model[MAX_MODEL_LENGTH];
    char registration_number[20];
    float hourly_rate;
    int battery_level;
    ScooterStatus status;
} Scooter;

// Customer structure
typedef struct {
    int customer_id;
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char license_number[20];
    int total_rentals;
} Customer;

// Rental structure
typedef struct {
    int rental_id;
    int scooter_id;
    int customer_id;
    time_t start_time;
    time_t end_time;
    float total_cost;
    int is_active;
} Rental;

// Rental Manager structure
typedef struct {
    Scooter scooters[MAX_SCOOTERS];
    Customer customers[MAX_CUSTOMERS];
    Rental rentals[MAX_RENTALS];
    int scooter_count;
    int customer_count;
    int rental_count;
} RentalManager;

// Function prototypes for scooter management
void init_rental_manager(RentalManager *manager);
int add_scooter(RentalManager *manager, const char *model, const char *reg_number, float hourly_rate);
int remove_scooter(RentalManager *manager, int scooter_id);
void display_scooters(RentalManager *manager);
void display_available_scooters(RentalManager *manager);
Scooter* find_scooter(RentalManager *manager, int scooter_id);

// Function prototypes for customer management
int add_customer(RentalManager *manager, const char *name, const char *phone, const char *license);
void display_customers(RentalManager *manager);
Customer* find_customer(RentalManager *manager, int customer_id);

// Function prototypes for rental management
int start_rental(RentalManager *manager, int customer_id, int scooter_id);
int end_rental(RentalManager *manager, int rental_id);
void display_active_rentals(RentalManager *manager);
void display_rental_history(RentalManager *manager);
float calculate_rental_cost(Rental *rental, Scooter *scooter);

// Utility functions
void update_scooter_status(RentalManager *manager, int scooter_id, ScooterStatus status);
void display_menu();

#endif // RENTAL_MANAGER_H
