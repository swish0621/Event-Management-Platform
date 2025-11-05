#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <string> 
#include <vector> 
#include <unordered_map>
#include <fstream>
#include "Event.h"
#include "User.h"

class EventManager {
  private:
    EventManager(){}
    static EventManager* instance_;
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;
    
    std::unordered_map<int, User*> users_;
    std::unordered_map<int, Event*> available_events_;
    std::unordered_map<int, Event*> unavailable_events_;

    int user_id_;
    int event_id_;

    double service_profit_;

  public:
    // get instance function will return the singular EventManager object or create it if not already exists. 
    static EventManager* getInstance(){
      if(instance_ == nullptr){
        instance_ = new EventManager();
        instance_->event_id_ = 0;
        instance_->user_id_ = 0;
        instance_->service_profit_ = 0;
      }
      return instance_;
    }

    double getServiceProfit() { return service_profit_; }

    void setServiceProfit(double profit) { service_profit_ = profit; }

    int useUserId();

    int useEventId();

    // finds the user by the users id 
    User* getUser(int id) const;

    // adds a new user to users_ 
    void addUser(User* user);

    User* createUser();

    // call event factory and prompt user to enter event details 
    // adds event to available events
    void createEvent(User* organizer);

    // returns an event: searches both available and unavailable
    Event* getEvent(int id) const;
    
    // moves an event from unavailable (for resale)
    void moveToAvailable(int id);

    // moves an event to unavailable (sold out)
    void moveToUnavailable(int id);

    // prints all available events 
    void printAvailableEvents() const;

    // adds event to user history, decrements available tickets and decrements user balance 
    void purchaseEvent(User* user, int event_id, int qty);

    // displays user balance 
    void printBalance(User* user) const;

    // increment user balance, increment available tickets, removes from user tickets
    void sellTicket(User* user, int event_id);
    
    void loadFromCSV();

};

#endif
