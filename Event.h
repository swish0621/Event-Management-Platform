#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <vector>
#include <iostream>


// Event.h initializes Event base class with derived subclasses 
// derived classes build from the base Event class to create 
// members that are specific to the Event type 

class User;

// Enums used to classify Event subtypes 
enum EventCategory { Concert, Sport, Theater, Convention, Comedy };
enum MusicGenre { Rock, Pop, Hiphop, Country, Jazz, Classical, Electronic, Metal, Indie };
enum SportType { Football, Hockey, Soccer, Basketball, Golf, MMA, Wrestling };
enum TheaterGenre { Musical, Opera, Ballet, Play };
enum TicketStatus { Available, Limited, SoldOut, ForResale };

// DateTime: stores date and time info about events
struct DateTime{
    int year;
    int month;
    int day;
    int hour;
    int minute;
};

inline std::ostream& operator<<(std::ostream& os,const DateTime& date){
    os << "Date: " << date.year << "/" << date.month << "/" << date.day << " " << date.hour << ":" << date.minute << std::endl;
    return os;
}

// abstract base class containing members that all Events share
class Event {
    protected:
        int id_;
        std::string event_name_;
        double price_;
        int available_tickets_;
        TicketStatus ticket_status_ = TicketStatus::Available;
        User* organizer_;

    public:
        // initialize shared members 
        Event(int id, std::string event_name, double price, int available_tickets) :
            id_(id), event_name_(event_name), price_(price),
            available_tickets_(available_tickets) {}
        // Virtual Destructor to be used by all derived classes that do not need a custom destructor 
        virtual ~Event() = default;

        // returns the Event id
        int getId() const { return id_; }
        // returns the price of an event
        double getPrice() const { return price_; }
        // Virtual function to be implemented by derived classes to return Event Category
        virtual EventCategory getEventCategory() const = 0;
        // returns the name of the event 
        std::string getEventName() const { return event_name_; }
        // ensure the Event has the requested amount of tickets available 
        bool hasTickets(int qty) const { return (available_tickets_ - qty) >= 0; }

        void setAvailableTickets(int num_tickets) { available_tickets_ = num_tickets; }
        
        int getAvailableTickets() { return available_tickets_; }
        // used to modify the ticket status of the event
        void setTicketStatus(TicketStatus status) { ticket_status_ = status; }
        // returns the TicketStatus of the event
        TicketStatus getTicketStatus() const { return ticket_status_; }
        // returns Event organizer
        User* getOrganizer() { return organizer_; }
        // modifies Event Organizer
        void setOrganizer(User* user) { organizer_ = user; }

        virtual void print(std::ostream& os) const = 0;

        friend std::ostream& operator <<(std::ostream& os, const Event& event) {
            event.print(os);
            return os;
        }
};

// abstract class derived from Event to add shared category of all Concert type Events
// acts as base class for all ConcertEvents 
class Concert : public Event {
    protected:
        EventCategory category_ = EventCategory::Concert;
    
    public:
        // calls base class constructor to initialize shared members 
        Concert(int id, std::string event_name, double price, int available_tickets) : 
            Event(id, event_name, price, available_tickets) {}

        // virtual function to be implemented by specific ConcertEvent objects to return the genre of the event
        virtual MusicGenre getGenre() const = 0;
        // implements an overridden function to return the shared attribute category of all Concert events
        EventCategory getEventCategory() const override { return category_; }
};

// concrete class derived from Concert type events
// initializes all specific event attributes and functions 
class ConcertEvent : public Concert {
    protected:
        std::vector<std::string> artists_;
        DateTime event_date_;
        MusicGenre genre_;
    
    public:
        // calls Concert constructor to initialize shared attributes
        // assigns all event specific attributes 
        ConcertEvent(int id, std::string event_name, double price, int available_tickets, 
            std::vector<std::string> artists, MusicGenre genre, DateTime event_date) :
            Concert(id, event_name, price, available_tickets), artists_(artists), event_date_(event_date), genre_(genre) {}
        
        // overrides base function to return genre of the ConcertEvent
        MusicGenre getGenre() const override { return genre_; }
        
        // returns list of stored artists at the event 
        std::vector<std::string> getArtists() const { return artists_; }
        // modifies artists at the event
        void setArtists(std::vector<std::string> artists) { artists_ = artists; }
        
        // returns date and time info about the event
        DateTime getDate() const { return event_date_; }
        // modifies date and time info about the event
        void setDate(DateTime date) { event_date_ = date; }

        void print(std::ostream& os) const override { 
            os <<id_ << ": " << event_name_ << "\n" << 
            "GENRE: " << genre_ << "\n" <<
            "ARTISTS";
            for(auto it : artists_){
                os << it << ",";
            }
            os << "\nPRICE: " << price_ << "\n" << event_date_;
        }
};

// abstract class derived from Event to add shared category of all Sport type Events
// acts as base class for all SportEvents 
class Sport : public Event {
    protected:
        EventCategory category_ = EventCategory::Sport;
    
    public:
        // calls base class constructor to assign shared attributes 
        Sport(int id, std::string event_name, double price, int available_tickets) : 
            Event(id, event_name, price, available_tickets) {}
        
        // virtual function to be implemented by all SportEvents to return the sport type 
        virtual SportType getSportType() const = 0;
        // overridden function to return category shared by all Sport events
        EventCategory getEventCategory() const override { return category_; }
};

// concrete class derived from sport type events 
// initializes all sport event specific members and functions
class SportEvent : public Sport {
    protected:
        std::string away_team_;
        std::string home_team_;
        SportType sport_type_;
        DateTime event_date_;
    
    public: 
        // calls Sport class constructor for shared sport members 
        // assigns sport event specific attributes 
        SportEvent(int id, std::string event_name, double price, int available_tickets,
            DateTime event_date, std::string away_team, std::string home_team, SportType sport_type) :
            Sport(id, event_name, price, available_tickets), away_team_(away_team),
            home_team_(home_team),sport_type_(sport_type), event_date_(event_date) {}

        // overridden Sport function to return the sport type 
        SportType getSportType() const override { return sport_type_; }

        // returns away team 
        std::string getAwayTeam() const { return away_team_; }
        // modifies away team 
        void setAwayTeam(std::string away_team) { away_team_ = away_team; }

        // returns home team 
        std::string getHomeTeam() const { return home_team_; }
        // modifies home team 
        void setHomeTeam(std::string home_team) { home_team_ = home_team; }

        // returns date and time information for the specific sport event 
        DateTime getDate() const { return event_date_; }
        // modifies date and time information for the specific sport event 
        void setDate(DateTime date) { event_date_ = date; } 

        void print(std::ostream& os) const override {
            os << id_ << ": " << event_name_ << "\n" << home_team_ << " vs " << away_team_;
            os << "\nPRICE: " << price_ << "\n" << event_date_;
        }

};

// abstract class derived from Event to add shared category of all Theater type Events
// acts as base class for all TheaterEvents 
class Theater : public Event {
    protected: 
        EventCategory category_ = EventCategory::Theater;

    public:
        // calls base class constructor to assign shared attributes 
        Theater(int id, std::string event_name, double price, int available_tickets) : 
            Event(id, event_name, price, available_tickets) {}

        // overridden function to return category shared by all Theater events
        EventCategory getEventCategory() const override { return category_; }
        // virtual function to be overridden by TheaterEvent to return theater genre
        virtual TheaterGenre getTheaterGenre() const = 0;

};

// concrete class derived from theater type events 
// initializes all theater event specific members and functions
class TheaterEvent : public Theater {
    protected:
        std::string original_title_;
        std::string director_;
        std::vector<std::string> performers_;
        TheaterGenre genre_;
        bool age_restricted_;
        DateTime event_date_;

    public:
        // calls Theater class constructor for shared theater members 
        // assigns theater event specific attributes 
        TheaterEvent(int id, std::string event_name, double price, int available_tickets, std::string original_title, 
            std::string director, std::vector<std::string> performers, TheaterGenre genre, bool age_restricted, DateTime date) :
            Theater(id, event_name, price, available_tickets), original_title_(original_title), director_(director), 
            performers_(performers), genre_(genre), age_restricted_(age_restricted), event_date_(date) {}

        // overridden function to return the theater event genre
        TheaterGenre getTheaterGenre() const override { return genre_; }

        // returns a list of perfomers for the theater event 
        std::vector<std::string> getPerformers() const { return performers_; }
        // modifies the performers for the theater event 
        void setPerformers(std::vector<std::string> performers) { performers_ = performers; }

        // returns the actual title of the work being performed 
        std::string getOriginalTitle() const { return original_title_; }
        // modifies the title of the work being performed 
        void setOriginalTitle(std::string title) { original_title_ = title; }

        // returns whether the theater event is age restricted 
        bool isAgeRestricted() const { return age_restricted_; }
        // modifies if the theater event is age restricted 
        void setAgeRestricted(bool is_restricted) { age_restricted_ = is_restricted; }

        // returns date and time information for the specific theater event 
        DateTime getDate() const { return event_date_; }
        // modifies date and time information for the specific theater event 
        void setDate(DateTime date) { event_date_ = date; } 

        void print(std::ostream& os) const override {
            os << id_ << ": " << event_name_ << 
            "\nTITLE: " << original_title_ <<
            "\nDIRECTOR: " << director_ <<
            "\nPERFORMERS: ";
            for(auto it : performers_){
                os << it << ",";
            }
            os << "\n PRICE: " << price_ <<
            "\n" << event_date_;
        }
};

// abstract class derived from Event to add shared category of all Convention type Events
// acts as base class for all ConventionEvents 
class Convention : public Event {
    protected:
        EventCategory category_ = EventCategory::Convention;

    public:
        // calls base class constructor to assign shared attributes 
        Convention(int id, std::string event_name, double price, int available_tickets) :
            Event(id, event_name, price, available_tickets) {}
        
        // overridden function to return category shared by all Convention events
        EventCategory getEventCategory() const override { return category_; }
        // virtual function to be overriden by ConventionEvent to return the industry type of the convention
        virtual std::string getIndustryType() const = 0;
};

// concrete class derived from convention type events 
// initializes all convention event specific members and functions
class ConventionEvent : public Convention {
    protected:
        std::string industry_type_;
        int num_exhibitors_;
        std::vector<std::string> exhibitors_;
        std::vector<std::string> sponsors_;
        int num_days_;
        DateTime event_date_;

    public:
        // calls Convention class constructor for shared convention members 
        // assigns convention event specific attributes 
        ConventionEvent(int id, std::string event_name, double price, int available_tickets, 
            std::string industry_type, int num_exhibitors, std::vector<std::string> exhibitors,
            std::vector<std::string> sponsors, int num_days, DateTime date) :
            Convention(id, event_name, price, available_tickets), industry_type_(industry_type),
            num_exhibitors_(num_exhibitors), exhibitors_(exhibitors), sponsors_(sponsors), 
            num_days_(num_days), event_date_(date) {}

        // overriden function to return the industry type of the specific convention event
        std::string getIndustryType() const override { return industry_type_; }

        // return the number of exhibitors at the convention event 
        int getNumExhibitors() const { return num_exhibitors_; }
        // modifies the number of exhibitors at the convention event 
        void setNumExhibitors(int num_exhibitors) { num_exhibitors_ = num_exhibitors; }

        // returns a list of the exhibitors at the specific convention event 
        std::vector<std::string> getExhibitors() const { return exhibitors_; }
        // modifies the exhibitors at the specific convention event
        void setExhibitors(std::vector<std::string> exhibitors) { exhibitors_ = exhibitors; }

        // returns a list of the sponsors at the convention event
        std::vector<std::string> getSponsors() const { return sponsors_; }
        // modifies the sponsors at the convention event 
        void setSponsors(std::vector<std::string> sponsors) { sponsors_ = sponsors; }

        //returns the number of days the event lasts 
        int getNumDays() const { return num_days_; }
        // modifies the number of days the event lasts 
        void setNumDays(int num_days) { num_days_ = num_days; }

        // returns date and time information for the specific ConventionEvent 
        DateTime getDate() const { return event_date_; }
        // modifies date and time information for the specific ConventionEvent 
        void setDate(DateTime date) { event_date_ = date; } 

        void print(std::ostream& os) const override {
            os << id_ << ": " << event_name_ <<
            "\nINDUSTRY TYPE: " << industry_type_ << 
            "\nEXHIBITORS: ";
            for(auto it : exhibitors_){
                os << it << ", ";
            }
            os << "\nSPONSORS: ";
            for(auto it : sponsors_){
                os << it << ", ";
            }
            os << "\nDURATION: " << num_days_ << 
            "\nPrice: " << price_ << "\n" << event_date_;
        }
};

// abstract class derived from Event to add shared category of all Comedy type Events
// acts as base class for all ComedyEvents 
class Comedy : public Event {
    protected:
        EventCategory category_ = EventCategory::Comedy;
    
    public:
        // calls base class constructor to assign shared attributes 
        Comedy(int id, std::string event_name, double price, int available_tickets) : 
            Event(id, event_name, price, available_tickets) {}

        // overridden function to return category shared by all Comedy events
        EventCategory getEventCategory() const override { return category_; }
        // virtual function to be overridden by ComedyEvent to return the specific ComedyEvent performer
        virtual std::string getPerformer() const = 0;
};

// concrete class derived from comedy type events 
// initializes all comedy event specific members and functions
class ComedyEvent : public Comedy {
    protected:
        std::string performer_;
        bool age_restricted_;
        std::vector<std::string> topics_;
        DateTime event_date_;
    
    public:
        // calls Comedy class constructor for shared comedy members 
        // assigns comedy event specific attributes 
        ComedyEvent(int id, std::string event_name, double price, int available_tickets, 
            std::string performer, bool age_restricted, std::vector<std::string> topics, DateTime date) :
            Comedy(id, event_name, price, available_tickets), performer_(performer), 
            age_restricted_(age_restricted), topics_(topics), event_date_(date) {}

        // overridden function to return the ComedyEvent specific performer
        std::string getPerformer() const override { return performer_; }

        // returns if the event is age restricted 
        bool getAgeRestricted() const { return age_restricted_; }
        // modifies if the event is age restricted
        void setAgeRestricted(bool age_restricted) {age_restricted_ = age_restricted; }

        // returns a list of the topics covered by the performer
        std::vector<std::string> getTopics() const { return topics_; }
        // modifies the topics covered by the performer
        void setTopics(std::vector<std::string> topics) { topics_ = topics; }

        // returns date and time information for the specific ComedyEvent 
        DateTime getDate() const { return event_date_; }
        // modifies date and time information for the specific Comedyvent 
        void setDate(DateTime date) { event_date_ = date; } 

        void print(std::ostream& os) const override {
            os << id_ << ": " << event_name_ <<
            "\nPERFORMER: " << performer_ <<
            "\nTOPICS: ";
            for(auto it : topics_){
                os << it << ", ";
            }
            os << "\nPRICE: " << price_ << "\n" << event_date_;
        }

};

#endif 
