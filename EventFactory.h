#ifndef EVENTFACTORY_H
#define EVENTFACTORY_H
#include "Event.h"

class EventFactory {
    private:
        static EventFactory* instance_;
        EventFactory() = default;
        EventFactory& operator=(const EventFactory&) = delete;
        EventFactory(const EventFactory&) = delete;


        // uses the ConcertEvent constructor to create a new ConcertEvent 
        Event* createConcertEvent(int id, std::string event_name, double price, int available_tickets, 
            std::vector<std::string> artists, MusicGenre genre, DateTime event_date);
        
        // uses the SportEvent constructor to create a new SportEvent
        Event* createSportEvent(int id, std::string event_name, double price, int available_tickets,
            DateTime event_date, std::string away_team, std::string home_team, SportType sport_type);
        
        // uses the TheaterEvent constructor to create a new TheaterEvent
        Event* createTheaterEvent(int id, std::string event_name, double price, int available_tickets, std::string original_title, 
            std::string director, std::vector<std::string> performers, TheaterGenre genre, bool age_restricted, DateTime date);

        // uses the ConventionEvent constructor to create a new ConventionEvent
        Event* createConventionEvent(int id, std::string event_name, double price, int available_tickets, 
            std::string industry_type, int num_exhibitors, std::vector<std::string> exhibitors,
            std::vector<std::string> sponsors, int num_days, DateTime date);

        // uses the ComedyEvent constructor to create a new ComedyEvent
        Event* createComedyEvent(int id, std::string event_name, double price, int available_tickets, 
            std::string performer, bool age_restricted, std::vector<std::string> topics, DateTime date);

    public:
        static EventFactory* getInstance() {
            if(instance_ == nullptr) { 
                instance_ = new EventFactory();
                return instance_; 
            }
            return instance_;
        }

        // will prompt user to input inprmation about the event to identify/call the correct creation function 
        // handle required side effects of event creation, adding to EventManager storage, adding to Organizer history
        Event* createEvent(EventCategory category);

        // to be used when loading Event data from csv, accepts one Event at a time 
        Event* createEventFromCSV(int id, std::string line_items);
};

#endif

