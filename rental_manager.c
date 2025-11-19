/*
 * rental_manager.c
 *
 * Implementation of all core data management functions, demonstrating
 * File Operations, Dynamic Memory Management, and Pointer Usage.
 */

#include "rental_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int last_record_index = 0;

/* --- Internal Helper Functions --- */

/**
 * Generates a unique ID string. (Internal helper)
 */
static void generate_unique_id(char *buffer, const char *prefix, int index) {
    sprintf(buffer, "%s%04d", prefix, index);
}

/**
 *  Prints the header for the rental records table. (Internal helper)
 */
static void print_record_header() {
    printf("\n%s\n", "------------------------------------------------------------------------------------------------------------------------------------");
    printf("| %-8s | %-8s | %-20s | %-24s | %-24s | %-8s | %-10s |\n",
           "REC ID", "SCOOTY", "CUSTOMER NAME", "START TIME", "END TIME", "COST ($)", "STATUS");
    printf("%s\n", "------------------------------------------------------------------------------------------------------------------------------------");
}

/**
 * Prints a single rental record in a formatted table row. (Internal helper)
 */
static void print_rental_record(const RentalRecord *r) {
    char start_time_str[26], end_time_str[26], cost_str[11];
    const char *status;

    struct tm *start_tm = localtime(&r->start_time);
    strftime(start_time_str, 26, "%Y-%m-%d %H:%M:%S", start_tm);

    if (r->end_time == 0) {
        strcpy(end_time_str, "--- ACTIVE ---");
        strcpy(cost_str, "N/A");
        status = "ACTIVE";
    } else {
        struct tm *end_tm = localtime(&r->end_time);
        strftime(end_time_str, 26, "%Y-%m-%d %H:%M:%S", end_tm);
        sprintf(cost_str, "%.2f", r->total_cost);
        status = "CLOSED";
    }

    printf("| %-8s | %-8s | %-20s | %-24s | %-24s | %-8s | %-10s |\n",
           r->record_id, r->scooty_id, r->customer_name, start_time_str, end_time_str, cost_str, status);
}

/* ---Implementation of rental_manager.h--- */

/**
 *  Loads rental records from the binary data file.
 * (Demonstrates File Operations and Dynamic Memory Allocation - malloc/fread)
 */
int load_data(RentalRecord **records, int *count) {
    FILE *file = fopen(DATA_FILE, "rb");
    if (file == NULL) {
        *records = NULL;
        *count = 0;
        printf("No existing data file found. Starting a new database.\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size == 0) {
        *records = NULL;
        *count = 0;
        fclose(file);
        return 1;
    }

    *count = file_size / sizeof(RentalRecord);
    *records = (RentalRecord *)malloc(*count * sizeof(RentalRecord));
    if (*records == NULL) {
        fprintf(stderr, "Error: Dynamic memory allocation failed during loading.\n");
        fclose(file);
        return 0;
    }

    size_t items_read = fread(*records, sizeof(RentalRecord), *count, file);
    fclose(file);

    if (items_read != *count) {
        fprintf(stderr, "Error: Only %zu of %d records read successfully.\n", items_read, *count);
        free(*records);
        *records = NULL;
        *count = 0;
        return 0;
    }

    if (*count > 0) {
        char id_num_str[5];
        strncpy(id_num_str, (*records)[*count - 1].record_id + 1, 4);
        id_num_str[4] = '\0';
        last_record_index = atoi(id_num_str);
    } else {
        last_record_index = 0;
    }

    printf("%d records loaded successfully from %s.\n", *count, DATA_FILE);
    return 1;
}

/**
 *Saves all rental records to the binary data file. (Demonstrates File Operations - fwrite)
 */
int save_data(RentalRecord *records, int count) {
    FILE *file = fopen(DATA_FILE, "wb");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file %s for writing.\n", DATA_FILE);
        return 0;
    }

    if (count > 0) {
        size_t items_written = fwrite(records, sizeof(RentalRecord), count, file);