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

    // Returns the profit values for the system
    double getServiceProfit() { return service_profit_; }

    // Modifies the service_profit_ value for the system
    void setServiceProfit(double profit) { service_profit_ = profit; }

    // Returns the current available id and increments the value 
    int useUserId();

    // Returns the current available id and increments the value 
    int useEventId();

    // Finds the user by the users id 
    User* getUser(int id) const;

    // Adds a new user to users_ 
    void addUser(User* user);

    User* createUser();

    // Call event factory and prompt user to enter event details 
    // Adds event to available events
    void createEvent(User* organizer);

    // Returns an event: searches both available and unavailable
    Event* getEvent(int id) const;
    
    // Moves an event from unavailable (for resale)
    void moveToAvailable(int id);

    // Moves an event to unavailable (sold out)
    void moveToUnavailable(int id);

    // Prints all available events 
    void printAvailableEvents() const;

    // Adds event to user history, decrements available tickets and decrements user balance 
    void purchaseEvent(User* user, int event_id, int qty);

    // Displays user balance 
    void printBalance(User* user) const;

    // Increment user balance, increment available tickets, removes from user tickets
    void sellTicket(User* user, int event_id);
    
    // Creates users and events form the values stored in csv files
    void loadFromCSV();

    // Adds funds to a users account 
    void addFunds(User* user, double funds);

};

#endif
