#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Bus {
    int busNo;
    char route[100];
    int totalSeats;
    int bookedSeats;
};

/* Function declarations */
void addBus();
void displayBuses();
void searchBus();
void bookTicket();
void cancelBooking();
void viewBookings();

/* Main Function */
int main() {
    int choice;

    do {
        printf("\n-----------------------------------------\n");
        printf("BUS TICKET RESERVATION SYSTEM\n");
        printf("-----------------------------------------\n");
        printf("1. Add Bus\n");
        printf("2. Display All Buses\n");
        printf("3. Search Bus\n");
        printf("4. Book Ticket\n");
        printf("5. Cancel Booking\n");
        printf("6. View Bookings\n");
        printf("0. Exit\n");
        printf("-----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addBus(); break;
            case 2: displayBuses(); break;
            case 3: searchBus(); break;
            case 4: bookTicket(); break;
            case 5: cancelBooking(); break;
            case 6: viewBookings(); break;
            case 0: printf("Exiting program...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while(choice != 0);

    return 0;
}

/* Add Bus */
void addBus() {
    FILE *fp = fopen("buses.txt", "a");
    struct Bus b;

    if(fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Bus Number: ");
    scanf("%d", &b.busNo);
    getchar(); // clear newline

    printf("Enter Route: ");
    fgets(b.route, sizeof(b.route), stdin);
    b.route[strcspn(b.route, "\n")] = '\0';

    printf("Enter Total Seats: ");
    scanf("%d", &b.totalSeats);

    b.bookedSeats = 0;

    fwrite(&b, sizeof(struct Bus), 1, fp);
    fclose(fp);

    printf("Bus added successfully!\n");
}

/* Display All Buses */
void displayBuses() {
    FILE *fp = fopen("buses.txt", "r");
    struct Bus b;
    int found = 0;

    if(fp == NULL) {
        printf("No buses available.\n");
        return;
    }

    printf("\nBusNo  Route                 Total  Booked  Available\n");
    while(fread(&b, sizeof(struct Bus), 1, fp)) {
        printf("%-6d %-20s %-6d %-7d %-9d\n",
               b.busNo, b.route, b.totalSeats,
               b.bookedSeats, b.totalSeats - b.bookedSeats);
        found = 1;
    }

    if(!found)
        printf("No buses available.\n");

    fclose(fp);
}

/* Search Bus */
void searchBus() {
    FILE *fp = fopen("buses.txt", "r");
    struct Bus b;
    char search[100];
    int found = 0;

    if(fp == NULL) {
        printf("No buses available.\n");
        return;
    }

    getchar();
    printf("Enter Bus Number or Route to search: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';

    while(fread(&b, sizeof(struct Bus), 1, fp)) {
        char busNoStr[10];
        sprintf(busNoStr, "%d", b.busNo);

        if(strstr(b.route, search) || strcmp(busNoStr, search) == 0) {
            printf("\nBus Found:\n");
            printf("Bus No: %d\nRoute: %s\nTotal Seats: %d\nBooked Seats: %d\nAvailable Seats: %d\n",
                   b.busNo, b.route, b.totalSeats,
                   b.bookedSeats, b.totalSeats - b.bookedSeats);
            found = 1;
        }
    }

    if(!found)
        printf("Bus not found.\n");

    fclose(fp);
}

/* Book Ticket */
void bookTicket() {
    FILE *fp = fopen("buses.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Bus b;
    int busNo, seats, found = 0;

    if(fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Bus Number: ");
    scanf("%d", &busNo);
    printf("Enter seats to book: ");
    scanf("%d", &seats);

    while(fread(&b, sizeof(struct Bus), 1, fp)) {
        if(b.busNo == busNo) {
            found = 1;
            if((b.totalSeats - b.bookedSeats) >= seats) {
                b.bookedSeats += seats;
                printf("Booking successful! Tickets booked: %d. Seats left: %d\n",
                       seats, b.totalSeats - b.bookedSeats);
            } else {
                printf("Not enough seats available.\n");
            }
        }
        fwrite(&b, sizeof(struct Bus), 1, temp);
    }

    if(!found)
        printf("Bus not found.\n");

    fclose(fp);
    fclose(temp);
    remove("buses.txt");
    rename("temp.txt", "buses.txt");
}

/* Cancel Booking */
void cancelBooking() {
    FILE *fp = fopen("buses.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Bus b;
    int busNo, seats, found = 0;

    if(fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Bus Number: ");
    scanf("%d", &busNo);
    printf("Enter seats to cancel: ");
    scanf("%d", &seats);

    while(fread(&b, sizeof(struct Bus), 1, fp)) {
        if(b.busNo == busNo) {
            found = 1;
            if(b.bookedSeats >= seats) {
                b.bookedSeats -= seats;
                printf("Cancellation successful! Seats left: %d\n",
                       b.totalSeats - b.bookedSeats);
            } else {
                printf("Cannot cancel more seats than booked.\n");
            }
        }
        fwrite(&b, sizeof(struct Bus), 1, temp);
    }

    if(!found)
        printf("Bus not found.\n");

    fclose(fp);
    fclose(temp);
    remove("buses.txt");
    rename("temp.txt", "buses.txt");
}

/* View Bookings */
void viewBookings() {
    FILE *fp = fopen("buses.txt", "r");
    struct Bus b;

    if(fp == NULL) {
        printf("No bookings available.\n");
        return;
    }

    printf("\nBusNo  Route                 Total  Booked  Available\n");
    while(fread(&b, sizeof(struct Bus), 1, fp)) {
        printf("%-6d %-20s %-6d %-7d %-9d\n",
               b.busNo, b.route, b.totalSeats,
               b.bookedSeats, b.totalSeats - b.bookedSeats);
    }

    fclose(fp);
}
