#ifndef EVENTFACTORY_H
#define EVENTFACTORY_H
#include "Event.h"
#include <iostream>
#include "StringFunctions.h"

class EventFactory {
    private:
        static EventFactory* instance_;
        EventFactory() = default;
        EventFactory& operator=(const EventFactory&) = delete;
        EventFactory(const EventFactory&) = delete;

        // Helper functions that direct user prompting to fill correct event values
        void getConcertEventValues(std::string& event_name, double& price, int& available_tickets, 
            std::vector<std::string>& artists, MusicGenre& genre, DateTime& event_date);

        void getSportEventValues(std::string& event_name, double& price, int& available_tickets,
            DateTime& event_date, std::string& away_team, std::string& home_team, SportType& sport_type);

        void getTheaterEventValues(std::string& event_name, double& price, int& available_tickets, std::string& original_title, 
            std::string& director, std::vector<std::string>& performers, TheaterGenre& genre, bool& age_restricted, DateTime& date);

        void getConventionEventValues(std::string& event_name, double& price, int& available_tickets, 
            std::string& industry_type, int& num_exhibitors, std::vector<std::string>& exhibitors,
            std::vector<std::string>& sponsors, int& num_days, DateTime& date);

        void getComedyEventValues(std::string& event_name, double& price, int& available_tickets, 
            std::string& performer, bool& age_restricted, std::vector<std::string>& topics, DateTime& date);

        // Helper functions to return enum types from user input 
        MusicGenre getGenre();

        DateTime getDateTime();
        
        SportType getSportType();

        TheaterGenre getTheaterGenre();

    public:
        static EventFactory* getInstance() {
            if(instance_ == nullptr) { 
                instance_ = new EventFactory();
                return instance_; 
            }
            return instance_;
        }

        // Prompt user to input inprmation about the event to identify/call the correct creation function 
        // Handle required side effects of event creation, adding to EventManager storage, adding to Organizer history
        Event* createEvent(int id, EventCategory category);

        // To be used when loading Event data from csv, accepts one Event at a time 
        Event* createEventFromCSV(int id, std::string line_items);
};

#endif

