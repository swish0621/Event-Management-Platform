## HW3 Design 

### Event (Abstract Base Class)
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |
| Event(int id, std::string event_name, double price, int available_tickets) | Constructor: Initialize shared attributes present in all Events | None |
| virtual ~Event() | Virtual destructor to be used by all derived classes unless a specific destructor is needed | None |
| int getId() const | Getter: returns Event Id | None |
| double getPrice() const | Getter: returns Event price | None |
| virtual EventCategory getEventCategory() const = 0| virtual function to return the specific EventCategory of derived classes | None | 
| std::string getEventName() const | Getter: returns the name of the Event | None | 
| bool hasTickets(int qty) const | Determines if the Event has the amount of tickets requested still available | None |
| void setTicketStatus(TicketStatus status) | Setter: modifies the ticket status of the Event | None |
| TicketStatus getTicketStatus() const | Getter: returns the ticket status of th Event | None |

### Concert (Abstract Derived Class)
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |
| Concert(int id, std::string event_name, double price, int available_tickets) | Constructor: Initializes shared attributes present in all Concert Events | Event(int id, std::string event_name, double price, int available_tickets) |
| virtual MusicGenre getGenre() const = 0 | Virtual function to be defined in derived classes to return the music genre of the ConcertEvent | None |
| EventCategory getEventCategory() const override | Overridden virtual function returns the EventCategory assigned to the Event | None |

### Sport (Abstract Derived Class)
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |
| Sport(int id, std::string event_name, double price, int available_tickets) | Constructor: Initializes shared attributes present in all Sport Events | Event(int id, std::string event_name, double price, int available_tickets) |
| virtual SportType getSportType() const = 0 | Virtual function implemented by derived classes to return the type of sport at the SportEvent | None |
| EventCategory getEventCategory() const override | Overridden virtual function returns the EventCategory assigned to the Event | None |


### Theater (Abstract Derived Class)
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |
| Theater(int id, std::string event_name, double price, int available_tickets) | Constructor: Initializes shared attributes present in all Theater Events | Event(int id, std::string event_name, double price, int available_tickets) |
| EventCategory getEventCategory() const override | Overridden virtual function returns the EventCategory assigned to the Event | None |
| virtual TheaterGenre getTheaterGenre() const | Virtual function implemented by derived classes to return the genre of TheaterEvent | None | 

### Convention (Abstract Derived Class)
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |
| Convention(int id, std::string event_name, double price, int available_tickets) | Constructor: Initializes shared attributes present in all Convention Events | Event(int id, std::string event_name, double price, int available_tickets) |
| EventCategory getEventCategory() const override | Overridden virtual function returns the EventCategory assigned to the Event | None |
| virtual std::string getIndustryType() const = 0 | Virtual function implemented by derived classes to return the IndustryType of the ConventionEvent | None |

### Comedy (Abstract Derived Class)
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |
| Comedy(int id, std::string event_name, double price, int available_tickets) | Constructor: Initializes shared attributes present in all Comedy Events | Event(int id, std::string event_name, double price, int available_tickets) |
| EventCategory getEventCategory() const override | Overridden virtual function returns the EventCategory assigned to the Event | None |
| virtual std::string getPerformer() const = 0 | Virtual function to be implemented in derived classes to return the performer of the ComedyEvent |

### EventFactory

### User

### EventManager
