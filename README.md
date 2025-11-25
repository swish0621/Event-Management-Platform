# Event Management Simulator
![Build](https://github.com/swish0621/Event-Management-Simulator/actions/workflows/c-cpp.yml/badge.svg)

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
- CSV-Parsing and loading 
- **Catch2 testing** for automated validation of key features  

Everything ties together through an `EventManager` singleton that controls program flow, tracks users, manages events, and handles all financial logic (balances, profits, and ticket status updates).

---
<img width="693" height="195" alt="Event-Managment-Platform" src="https://github.com/user-attachments/assets/baf4fb14-775f-487c-ab93-129b536edb05" />

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

# Future Plans

This project is currently an MVP implementation of an event management backend.  
The following roadmap outlines planned expansions to evolve the system into a fully functional, production-ready full-stack application.

---

## 1. Architecture Expansion
- Add support for user accounts with usernames, password hashes, emails, and roles/permissions.
- Introduce additional metadata fields for events and users as needed for expanded functionality.

---

## 2. Input Validation & Security
- Remove CLI-driven input and replace it with structured validation rules.
- Add robust checks for all user and event fields (length limits, allowed characters, date validation, ticket quantity rules, etc.).
- Implement secure password hashing and safe authentication handling.

---

## 3. Database Integration
- Migrate from CSV storage to a relational database (SQLite or PostgreSQL).
- Create a normalized schema for Users, Events, Tickets, and Transactions.
- Implement complete CRUD operations for all entities.
- Add indexing for performance on common queries.

---

## 4. API Layer
- Expose system functionality through REST API endpoints.
- Add authentication endpoints (register, login, logout).
- Structure routes using clean separation between domain logic and request handling.
- Introduce proper error responses and status codes.

---

## 5. Minimal Frontend
- Build a lightweight interface for verifying API functionality.
- Include basic pages for login, event browsing, event creation, and ticket management.
- Use simple forms and minimal styling to validate full-stack behavior.

---

## 6. Deployment
- Containerize backend and API services using Docker.
- Deploy the application to AWS (ECS, EC2, or similar).
- Configure environment variables, HTTPS, logging, and production settings.
- Set up CI/CD through GitHub Actions.

---

## 7. Full Frontend Experience
- Expand the UI into a polished interface using a modern framework (React, Vue, or Svelte).
- Add routing, authentication flow, form validation, and responsive layouts.
- Improve error handling, loading states, and overall user experience.

---

## 8. Logging, Monitoring & Testing
- Implement request/response logging and error logging.
- Add audit trails for key operations (event creation, purchases, account updates).
- Write unit tests and integration tests for all API endpoints.
- Conduct load testing for high-traffic workflows.

---

## 9. Feature Expansion
- Add event search, filtering, and sorting capabilities.
- Build admin tools for creating and managing events and users.
- Integrate the existing recommendation engine to provide personalized event suggestions.
- Support recurring events, categories, and advanced scheduling options.

---




