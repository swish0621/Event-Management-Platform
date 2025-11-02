#include "EventFactory.h"

EventFactory* EventFactory::instance_ = nullptr;

// intitialize event Specific values 
// pass by reference to asscoiated user prompt function to define values
// call specific event contructor and return a new object
Event* EventFactory::createEvent(int id, EventCategory event) {
    switch(event){
        case EventCategory::Concert:
        {
            std::string event_name;
            double price;
            int available_tickets;
            std::vector<std::string> artists;
            MusicGenre genre;
            DateTime event_date;

            getConcertEventValues(id, event_name, price, available_tickets, artists, genre, event_date);
            return new ConcertEvent(id, event_name, price, available_tickets, artists, genre, event_date);
        }
        case EventCategory::Sport:
        {
            std::string event_name;
            double price;
            int available_tickets;
            DateTime event_date;
            std::string away_team;
            std::string home_team;
            SportType sport_type;

            getSportEventValues(id, event_name, price, available_tickets, event_date, away_team, home_team, sport_type);
            return new SportEvent(id, event_name, price, available_tickets, event_date, away_team, home_team, sport_type);
        }
        case EventCategory::Theater:
        {
            std::string event_name;
            double price;
            int available_tickets;
            std::string original_title;
            std::string director;
            std::vector<std::string> performers;
            TheaterGenre genre;
            bool age_restricted;
            DateTime event_date;

            getTheaterEventValues(id, event_name, price, available_tickets, original_title, director, performers, genre, age_restricted, event_date);
            return new TheaterEvent(id, event_name, price, available_tickets, original_title, director, performers, genre, age_restricted, event_date);
        }
        case EventCategory::Convention:
        {
            std::string event_name;
            double price;
            int available_tickets;
            std::string industry_type;
            int num_exhibitors;
            std::vector<std::string> exhibitors;
            std::vector<std::string> sponsors;
            int num_days;
            DateTime event_date;

            getConventionEventValues(id, event_name, price, available_tickets, industry_type, num_exhibitors, exhibitors, sponsors, num_days, event_date);
            return new ConventionEvent(id, event_name, price, available_tickets, industry_type, num_exhibitors, exhibitors, sponsors, num_days, event_date);
        }
        case EventCategory::Comedy:
        {
            std::string event_name;
            double price;
            int available_tickets;
            std::string performer;
            bool age_restricted;
            std::vector<std::string> topics;
            DateTime event_date;

            getComedyEventValues(id, event_name, price, available_tickets, performer, age_restricted, topics, event_date);
            return new ComedyEvent(id, event_name, price, available_tickets, performer, age_restricted, topics, event_date);
        }
        default:
        {
            return nullptr;
        }
    }
}

// read all necessary data from a csv file and call the correct helper based on the EventCategory
Event* EventFactory::createEventFromCSV(int id, std::string line_items) { return nullptr; }



