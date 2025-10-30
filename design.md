## HW3 Design 

### Event (Abstract Base Class)
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |
| Event(int id, std::string event_name, double price, int available_tickets) | Initialize shared attributes present in all Events | None |
| virtual ~Event() | Virtual destructor to be used by all derived classes unless a specific destructor is needed | None |
| int getId() const | Returns Event Id | None |
| double getPrice() const | Returns Event price | None |
| virtual EventCategory getEventCategory() const = 0| Virtual function to return the specific EventCategory of derived classes | None | 
| std::string getEventName() const | Returns the name of the Event | None | 
| bool hasTickets(int qty) const | Determines if the Event has the amount of tickets requested still available | None |
| void setTicketStatus(TicketStatus status) | Modifies the ticket status of the Event | None |
| TicketStatus getTicketStatus() const | Returns the ticket status of th Event | None |

### Concert (Abstract Derived Class)
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |
| Concert(int id, std::string event_name, double price, int available_tickets) | Initializes shared attributes present in all Concert Events | Event(int id, std::string event_name, double price, int available_tickets) |
| virtual MusicGenre getGenre() const = 0 | Virtual function to be defined in derived classes to return the music genre of the ConcertEvent | None |
| EventCategory getEventCategory() const override | Overridden virtual function returns the EventCategory assigned to the Event | None |

### Sport (Abstract Derived Class)
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |
| Sport(int id, std::string event_name, double price, int available_tickets) | Initializes shared attributes present in all Sport Events | Event(int id, std::string event_name, double price, int available_tickets) |
| virtual SportType getSportType() const = 0 | Virtual function implemented by derived classes to return the type of sport at the SportEvent | None |
| EventCategory getEventCategory() const override | Overridden virtual function returns the EventCategory assigned to the Event | None |


### Theater (Abstract Derived Class)
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |
| Theater(int id, std::string event_name, double price, int available_tickets) | Initializes shared attributes present in all Theater Events | Event(int id, std::string event_name, double price, int available_tickets) |
| EventCategory getEventCategory() const override | Overridden virtual function returns the EventCategory assigned to the Event | None |
| virtual TheaterGenre getTheaterGenre() const = 0| Virtual function implemented by derived classes to return the genre of TheaterEvent | None | 

### Convention (Abstract Derived Class)
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |
| Convention(int id, std::string event_name, double price, int available_tickets) | Initializes shared attributes present in all Convention Events | Event(int id, std::string event_name, double price, int available_tickets) |
| EventCategory getEventCategory() const override | Overridden virtual function returns the EventCategory assigned to the Event | None |
| virtual std::string getIndustryType() const = 0 | Virtual function implemented by derived classes to return the IndustryType of the ConventionEvent | None |

### Comedy (Abstract Derived Class)
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |
| Comedy(int id, std::string event_name, double price, int available_tickets) | Initializes shared attributes present in all Comedy Events | Event(int id, std::string event_name, double price, int available_tickets) |
| EventCategory getEventCategory() const override | Overridden virtual function returns the EventCategory assigned to the Event | None |
| virtual std::string getPerformer() const = 0 | Virtual function to be implemented in derived classes to return the performer of the ComedyEvent |

### ConcertEvent (Concrete Derived Class)
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |
| ConcertEvent(int id, std::string event_name, double price, int available_tickets, std::vector\<std::string> artists, MusicGenre genre, DateTime event_date) | Initializes ConcertEvent specific attributes and calls Concert constructor for shared attribute handling | Concert(id, event_name, price, available_tickets) |
| MusicGenre getGenre() const override | Overridden virtual function returns the genre of the ConcertEvent | None |
| std::vector\<std::string> getArtists() const | Returns a list of the Artists at the ConcertEvent | None |
| void setArtists(std::vector\<std::string> artists) | Modifies the artists at the ConcertEvent | None |
| DateTime getDate() const | Returns the DateTime info of the ConcertEvent | None |
| void setDate(DateTime date) | Modifies the DateTime info of the ConcertEvent| None |

### SportEvent (Concrete Derived Class)
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |
| SportEvent(int id, std::string event_name, double price, int available_tickets, DateTime event_date, std::string away_team, std::string home_team, SportType sport_type) | Initializes SportEvent specific attributes and calls Sport constructor for shared attribute handling | Sport(id, event_name, price, available_tickets) |
| SportType getSportType() const override | Overridden function returns the SportType of the Sport Event | None |
| std::string getAwayTeam() const | Returns the away team | None |
| void setAwayTeam(std::string away_team) | Modifies the away team | None |
| std::string getHomeTeam() const | Returns the home team | None | 
| void setHomeTeam(std::string home_team) | Modifies the home team | None |
| DateTime getDate() const | Returns the DateTime info of the SportEvent | None |
| void setDate(DateTime date) | Modifies the DateTime info of the SportEvent| None |

### TheaterEvent (Concrete Derived Class)
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |
|TheaterEvent(int id, std::string event_name, double price, int available_tickets, std::string original_title, std::string director, std::vector\<std::string> performers, TheaterGenre genre, bool age_restricted, DateTime date) | Initializes TheaterEvent specific attributes and calls Theater constructor for shared attribute handling | Theater(id, event_name, price, available_tickets) |
| TheaterGenre getTheaterGenre() const override | Overridden function returns the genre of the TheaterEvent | None |
| std::vector\<std::string> getPerformers() const | Returns a list of the performers | None |
| void setPerformers(std::vector\<std::string> performers) | Modifies performers | None |
| std::string getOriginalTitle() const | Returns the title of the work being performed | None |
| void setOriginalTitle(std::string title) | Modifies the name of the work being performed | None |
| bool isAgeRestricted() const | Returns if the TheaterEvent is age restricted | None |
| void setAgeRestricted(bool is_restricted) | Modifies the age restriction | None |
| DateTime getDate() const | Returns the DateTime info of the TheaterEvent | None |
| void setDate(DateTime date) | Modifies the DateTime info of the TheaterEvent| None |

### ConventionEvent (Concrete Derived Class)
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |
| ConventionEvent(int id, std::string event_name, double price, int available_tickets, std::string industry_type, int num_exhibitors, std::vector\<std::string> exhibitors,std::vector\<std::string> sponsors, int num_days, DateTime date) | Initializes ConventionEvent specific attributes and calls Convention constructor for shared attribute handling | Convention(id, event_name, price, available_tickets) |
| std::string getIndustryType() const override | Overridden fucntion returns IndustryType of the ConventionEvent | None |
| int getNumExhibitors() const | Returns the number of Exhibitiors | None |
| void setNumExhibitors(int num_exhibitors) | Modifies the number of Exhibitors | None |
| std::vector\<std::string> getExhibitors() const | Returns a list of the Exhibitors | None |
|void setExhibitors(std::vector\<std::string> exhibitors) | Modifies the Exhibitors at the ConventionEvent | None |
| std::vector\<std::string> getSponsors() const | Returns a list of the Sponsors | None |
| void setSponsors(std::vector<std::string> sponsors) | Modifies the Sponsors at the ConventionEvent | None |
| int getNumDays() const | Returns the number of days the ConventionEvent lasts | None |
| void setNumDays(int num_days) | Modifies the duration of the ConventionEvent | None |
| DateTime getDate() const | Returns the DateTime info of the ConventionEvent | None |
| void setDate(DateTime date) | Modifies the DateTime info of the ConventionEvent| None |


### ComedyEvent (Concrete Derived Class)
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |

### EventFactory
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |

### User
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |

### EventManager
| Method | Description | Calls Other Methods |
| :----- | :---------- | :------------------ |


## Main() Psuedocode
