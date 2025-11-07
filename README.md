# Event Management Simulator

A simulation of an event and ticket management system built with C++ and key design patterns to showcase OOP architecture.  
This project models a Ticketmaster-style system where users can act as attendees or organizers, create events, buy or sell tickets, and track balances handled through a CLI menu interface.

---

## Overview

The core of this system revolves around **object-oriented design and architecture**.  
It’s built to demonstrate real software structure using:

- **Inheritance and polymorphism** across event and user hierarchies  
- **Factory pattern** for dynamic event creation  
- **Singleton pattern** for centralized event management  
- **Encapsulation and abstraction** to isolate logic cleanly  
- **CSV-Parsing and loading 
- **Catch2 testing** for automated validation of key features  

Everything ties together through an `EventManager` singleton that controls program flow, tracks users, manages events, and handles all financial logic (balances, profits, and ticket status updates).

---

## Features

- Create new **Attendee** or **Organizer** accounts  
- Organizers can create events of various types (Concerts, Sports, Theater, Conventions, Comedy)  
- Attendees can:
  - Browse available events  
  - Purchase or resell tickets  
  - View purchase history  
  - Manage balance and add funds  
- Ticket inventory and availability update dynamically  
- System tracks organizer earnings and platform profit  

---

## Design Patterns Used

- **Factory Pattern:**  
  Used in `EventFactory` to handle dynamic event creation from user input or CSV files.  
  Keeps client code clean and decoupled from specific event subclasses.

- **Singleton Pattern:**  
  Implemented in `EventManager` to maintain a single controller instance that manages global system state.

---

## Structure


Each part of the system has a clear role:
- **Event hierarchy:** defines data models and shared behavior  
- **EventFactory:** central object creator  
- **EventManager:** controls system flow and logic  
- **User classes:** define attendee and organizer roles  
- **StringFunctions:** utility for parsing input and CSV data  
- **Catch2 tests:** validate functionality and architecture

---

## Build & Run

To build and run the main program:

```bash
make
./main
```
To run the test suite:
```
make test
./test
```
To clean build files:
```
make clean
```

