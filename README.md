# Bus-Ticket
Bus Ticket Reservation System
Bus Ticket Reservation System
Objective
Develop a menu-driven C program to manage bus routes, seat availability and ticket booking using structures and file handling.

Overview
The Bus Ticket Reservation System is a menu-driven application developed using C to simulate a basic ticket booking and management process. It utilizes structures to maintain details of buses, routes, and passenger bookings, along with file handling to ensure data persistence. The system allows users to add new bus routes, view available buses and seat availability, book or cancel tickets, and search for buses by route or bus number. Each operation is implemented through modular functions to enhance clarity and maintainability.

System Features
•	Add bus routes with seat capacity
•	Display all buses and availability
•	Book ticket (reserve seat)
•	Cancel booking (free seat)
•	Search bus by route or bus number
•	File-based storage for buses and bookings

Input: Structure Definition
struct Bus {
    int busNo;
    char route[100];    // e.g., 'CityA - CityB'
    int totalSeats;
    int bookedSeats;
};

Main Function Outline
int main() {
    int choice;
    do {
        // Display main menu and get user input
        // Use switch-case to call module functions
    } while(choice != 0);
    return 0;
}

