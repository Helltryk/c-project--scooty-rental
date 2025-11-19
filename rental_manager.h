/*
 * rental_manager.h
 *
 * Defines structures, constants, and function prototypes for the
 * Scooty Rental Data Management System.
 */

#ifndef RENTAL_MANAGER_H
#define RENTAL_MANAGER_H

#include <time.h>


// --- CONSTANTS ---
#define DATA_FILE "rental_data.dat"
#define MAX_NAME_LEN 50
#define MAX_ID_LEN 10
#define HOURLY_RATE 15.0 // Rental rate per hour

// --- STRUCTURE DEFINITION ---
// Data structure for a single rental transaction.
typedef struct {
    char record_id[MAX_ID_LEN];      // Unique rental record ID (e.g., R0001)
    char scooty_id[MAX_ID_LEN];      // Scooty identifier (e.g., S001)
    char customer_name[MAX_NAME_LEN];
    time_t start_time;               // Time rental started
    time_t end_time;                 // Time rental ended (0 if ongoing)
    double total_cost;               // Calculated cost
} RentalRecord;

// File I/O and Initialization
int load_data(RentalRecord **records, int *count);
int save_data(RentalRecord *records, int count);

// Data Management Operations
void add_new_rental(RentalRecord **records, int *count);
void end_active_rental(RentalRecord **records, int *count);

// View and Reporting
void view_all_rentals(RentalRecord *records, int count);
void search_records(RentalRecord *records, int count);

#endif // RENTAL_MANAGER_H

