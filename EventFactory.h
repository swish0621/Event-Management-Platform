#ifndef EVENTFACTORY_H
#define EVENTFACTORY_H
#include "Event.h"

class EventFactory {
    private:
        static EventFactory* instance_;
        EventFactory() = default;
        EventFactory& operator=(const EventFactory&) = delete;
        EventFactory(const EventFactory&) = delete;

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

