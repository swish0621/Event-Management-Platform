#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <vector>

enum EventCategory { Concert, Sport, Theater, Festival, Comedy };

class Event {
    protected:
        int id_;
        std::string event_name_;
        double price_;
        int available_tickets_;

    public:
        Event(int id, std::string event_name, double price, int available_tickets) :
            id_(id), event_name_(event_name), price_(price),
            available_tickets_(available_tickets) {}
        int getId() const {return id_; }
        virtual ~Event() = default;
        virtual EventCategory getCategory() const = 0;
        const std::string getEventName() const { return event_name_; }
        bool hasTickets(int qty) const { return (available_tickets_ - qty) >= 0; }

};

#endif 
