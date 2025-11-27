SAPID:590023585


# Scooter Rental Management System

A comprehensive C programming project for managing scooter rentals with features for fleet management, customer registration, and rental tracking.

## Project Structure

```
project/
├── docs/
│   ├── ProjectReport.pdf
├── src/
│   ├── rental_manager.h
│   ├── rental_manager.c
│   └── main.c
└── include/
    ├── Makefile
└── README.md          # This file
```

## Features

### Scooter Management
- Add new scooters to the fleet with model, registration, and hourly rates
- Remove scooters from the system
- View all scooters with details (ID, model, registration, rate, battery, status)
- Display only available scooters
- Update scooter status (Available, Rented, Maintenance)
- Track battery levels for each scooter

### Customer Management
- Register new customers with name, phone, and license number
- View all registered customers
- Track total number of rentals per customer
- Customer verification for rentals

### Rental Management
- Start new rentals by linking customers to available scooters
- End rentals and calculate total cost based on duration
- View all active rentals in real-time
- Access complete rental history
- Automatic cost calculation based on hourly rates
- Time-based duration tracking

## Data Structures

### Scooter
- Scooter ID
- Model name
- Registration number
- Hourly rental rate
- Battery level (percentage)
- Status (Available/Rented/Maintenance)

### Customer
- Customer ID
- Name
- Phone number
- License number
- Total rental count

### Rental
- Rental ID
- Scooter ID reference
- Customer ID reference
- Start time
- End time
- Total cost
- Active status flag

## Compilation & Execution

### Using Makefile (Recommended)

```bash
# Compile the project
make

# Run the program
make run

# Clean build files
make clean

# Rebuild from scratch
make rebuild
```

### Manual Compilation

```bash
# Compile
gcc -Wall -Wextra -std=c11 -o scooter_rental main.c rental_manager.c

# Run
./scooter_rental
```

## Usage Guide

When you run the program, you'll see a menu with the following options:

1. **Add Scooter** - Register a new scooter in the fleet
2. **Display All Scooters** - View complete scooter inventory
3. **Display Available Scooters** - See only rentable scooters
4. **Remove Scooter** - Delete a scooter from the system
5. **Add Customer** - Register a new customer
6. **Display All Customers** - View all registered customers
7. **Start Rental** - Begin a new rental transaction
8. **End Rental** - Complete an ongoing rental and calculate cost
9. **Display Active Rentals** - View all current rentals
10. **Display Rental History** - See all past and present rentals
11. **Update Scooter Status** - Change scooter availability status
0. **Exit** - Close the program

## Sample Workflow

1. Start the program (comes with pre-loaded sample data)
2. View available scooters (Option 3)
3. Register a new customer or use existing (Option 5)
4. Start a rental by entering customer ID and scooter ID (Option 7)
5. View active rentals (Option 9)
6. End the rental when customer returns (Option 8)
7. Check rental history for cost details (Option 10)

## System Limits

- Maximum Scooters: 100
- Maximum Customers: 100
- Maximum Rentals: 100
- Maximum Name Length: 50 characters
- Maximum Model Length: 50 characters
- Maximum Phone Length: 15 characters

## Key Functions

### rental_manager.c

- `init_rental_manager()` - Initialize the management system
- `add_scooter()` - Add a new scooter
- `remove_scooter()` - Remove a scooter
- `display_scooters()` - Show all scooters
- `display_available_scooters()` - Show available scooters only
- `add_customer()` - Register a new customer
- `display_customers()` - Show all customers
- `start_rental()` - Begin a rental
- `end_rental()` - Complete a rental
- `display_active_rentals()` - Show ongoing rentals
- `display_rental_history()` - Show all rental records
- `calculate_rental_cost()` - Compute rental charges
- `update_scooter_status()` - Modify scooter status

## Technical Details

- **Language**: C
- **Memory Management**: Static arrays (no dynamic allocation)
- **Time Handling**: POSIX time functions for duration calculation
- **Input Validation**: Error checking for all operations
- **Status Management**: Enum-based status tracking

## Future Enhancements

- File I/O for persistent data storage
- Dynamic memory allocation for unlimited records
- Payment processing integration
- Advanced search and filter options
- Discount and loyalty programs
- Multi-location support
- GPS tracking integration
- Reporting and analytics features

## Notes

- The system initializes with sample scooters and customers for demonstration
- All rentals are tracked with precise timestamps
- Rental costs are calculated based on actual duration in hours
- Scooters cannot be removed while actively rented
- Battery levels are tracked but not yet integrated with rental logic

## Author

Created as a C programming educational project demonstrating:
- Modular code organization
- Struct-based data management
- Function decomposition
- User interface design
- Time-based calculations


By:
- Arahan Chaudhary
- Aditya Satyam