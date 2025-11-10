#include "EventManager.h"
#include "EventFactory.h"
#include <cmath>

// Nicholas Swisher
// Purpose: define the member functions of the EventManager

// Initialize instance_ to a null pointer
EventManager* EventManager::instance_ = nullptr;

// Supply the next user id available and increment to the next available id
int EventManager::useUserId() {
    int id = user_id_;
    user_id_++;
    return id;
}

// Supply the next event id available and increment to the next available id
int EventManager::useEventId() {
    int id = event_id_;
    event_id_++;
    return id;
}

// Return a User pointer if the id exists
User* EventManager::getUser(int id) const {
    auto user = users_.find(id);
    if(user != users_.end()){
        return user->second;
    }
    return nullptr;
}

// Add a user to the user storage 
void EventManager::addUser(User* user) {
    users_[user->getId()] = user;
}

// User prompting to create a new user and add the new user to the user storage
User* EventManager::createUser() {
    int id = useUserId();
    std::string input;
    std::string name;
    std::string s_balance;
    std::cout << "SELECT A USER TYPE:\n" << "1: ATTENDEE\n2: ORGANIZER" << std::endl;
    std::cin >> input;

    std::cout << "ENTER YOUR NAME:" << std::endl;
    std::cin.ignore(1, '\n');
    std::getline(std::cin, name);
    std::cout << "ENTER AMOUNT OF FUNDS TO OPEN ACCOUNT WITH (FORMAT XX.XX):" << std::endl;
    std::cin >> s_balance;
    double balance = std::stod(s_balance);

    User* user;
    if(std::stoi(input) == 1) {
        user = new Attendee(id, name, balance);
    }
    else {
        user = new Organizer(id, name, balance);
    }
    addUser(user);
    return user; 
}

// User prompting to create a new event and store it in the available events storage
void EventManager::createEvent(User* organizer) {

    EventCategory category;
    std::string input;
    std::cout << "ENTER EVENT CATEGORY NUMBER: \n1: Concert\n2: Sport\n3: Theater\n4: Convention\n5: Comedy" << std::endl;
    std::cin >> input;

    switch(std::stoi(input)) {
        case 1: 
            category = EventCategory::Concert;
            break;
        case 2:
            category = EventCategory::Sport;
            break;
        case 3:
            category = EventCategory::Theater;
            break;
        case 4:
            category = EventCategory::Convention;
            break;
        case 5:
            category = EventCategory::Comedy;
            break;
        default: 
            throw std::invalid_argument("Invalid Category");
    }

    Event* event = EventFactory::createEvent(useEventId(), category);
    event -> setOrganizer(organizer);
    std::vector<Event*>& history = organizer->getHistory();
    history.push_back(event);
    organizer->setHistory(history);
    available_events_[event->getId()] = event;
}

// Return an event pointer if the id exists
Event* EventManager::getEvent(int id) const {
    auto available = available_events_.find(id);
    auto unavailable = unavailable_events_.find(id);
    if(available == available_events_.end() && unavailable == unavailable_events_.end()) {
        return nullptr;
    }
    if(available != available_events_.end()){
        return (available->second);
    }
    return unavailable->second;
}

// Move an event from unavailable storage to available storage
void EventManager::moveToAvailable(int id) {
    auto event = unavailable_events_.find(id);
    if(event != unavailable_events_.end()){
        available_events_[id] = event->second;
        unavailable_events_.erase(event);
    }
}

// Move an event from available storage to unavailable storage
void EventManager::moveToUnavailable(int id) {
    auto event = available_events_.find(id);
    if(event != available_events_.end()){
        unavailable_events_[id] = event->second;
        available_events_.erase(event);
    }
}

// Prints all events stored in available event storage
void EventManager::printAvailableEvents() const {
    for(auto it : available_events_){
        std::cout << *it.second << std::endl;
    }
}

// Handles all side effects of purchasing an event 
// Handles if the user doesnt have the available funds
// Handles if the event doesnt have the requested tickets
void EventManager::purchaseEvent(User* user, int event_id, int qty) {
    Event* event = getEvent(event_id);
    // ensure event was found 
    if(!event){
        std::cout << "EVENT NOT FOUND." << std::endl;
        return;
    }
    double balance = user->getBalance();
    double price = event->getPrice();
    bool has_tickets = event->hasTickets(qty);
    bool has_balance = balance >= (price * qty);
    bool purchase = has_balance && has_tickets;

    // Event doesnt have enough tickets 
        // set qty to tickets available
        // set new user balance
        // take fees for service
        // set new organizer balance
        // set new ticket amount and status 
        // add event to user history 
    if(!has_tickets){
        std::cout << "EVENT ONLY HAS " << event->getAvailableTickets() << " LEFT:\n" 
            << "PURCHASE?\n1: YES\n2: NO" << std::endl;
        std::string input; 
        std::cin >> input;
        int choice = std::stoi(input);
        if(choice == 1){
            qty = event->getAvailableTickets();
            user->setBalance(balance - (price * qty));
            event->setAvailableTickets(event->getAvailableTickets() - qty);
            if(event->getAvailableTickets() <= 25){
                event->setTicketStatus(TicketStatus::Limited);
                if(event->getAvailableTickets() == 0){
                    event->setTicketStatus(TicketStatus::SoldOut);
                    moveToUnavailable(event_id);
                }
            }
            std::vector<Event*>& history = user->getHistory();
            for(int i = 0; i < qty; i++){
                history.push_back(event);
            }
            double service_profit = std::round(price * .05 * qty * 100) / 100;
            User* organizer = event->getOrganizer();
            organizer->setBalance(organizer->getBalance() + ((price * qty) - service_profit));
            setServiceProfit(getServiceProfit() + service_profit);
        }
        return;
    }

    // User doesnt have enough money 
        // set qty to max tickets purchasable
        // set new user balance
        // take fees for service
        // set new organizer balance
        // set new ticket amount and status 
        // add event to user history 
    if(!has_balance){
        int can_purchase = balance / price;
        if(can_purchase == 0){
            std::cout << "NOT ENOUGH FUNDS." << std::endl;
            return;
        }
        std::cout << "NOT ENOUGH FUNDS.\nYOU CAN PURCHASE " << can_purchase << " TICKETS.\nPURCHASE?\n1: YES\n2: NO" << std::endl;
        std::string input; 
        std::cin >> input;
        int choice = std::stoi(input);
        if(choice == 1){
            qty = can_purchase;
            user->setBalance(balance - (price * qty));
            event->setAvailableTickets(event->getAvailableTickets() - qty);
            if(event->getAvailableTickets() <= 25){
                event->setTicketStatus(TicketStatus::Limited);
                if(event->getAvailableTickets() == 0){
                    event->setTicketStatus(TicketStatus::SoldOut);
                    moveToUnavailable(event_id);
                }
            }
            std::vector<Event*>& history = user->getHistory();
            for(int i = 0; i < qty; i++){
                history.push_back(event);
            }
            double service_profit = std::round(price * .05 * qty * 100) / 100;
            User* organizer = event->getOrganizer();
            organizer->setBalance(organizer->getBalance() + ((price * qty) - service_profit));
            setServiceProfit(getServiceProfit() + service_profit);
        }
        return;
    }

    
    // Event has enough tickets and user has enough money 
        // set new user balance
        // take fees for service
        // set new organizer balance
        // set new ticket amount and status 
        // add event to user history 
    if(purchase) {
        user->setBalance(balance - (price * qty));
        event->setAvailableTickets(event->getAvailableTickets() - qty);
        if(event->getAvailableTickets() <= 25){
            event->setTicketStatus(TicketStatus::Limited);
            if(event->getAvailableTickets() == 0){
                event->setTicketStatus(TicketStatus::SoldOut);
                moveToUnavailable(event_id);
            }
        }
        std::vector<Event*>& history = user->getHistory();
        for(int i = 0; i < qty; i++){
            history.push_back(event);
        }
        double service_profit = std::round(price * .05 * qty * 100) / 100;
        User* organizer = event->getOrganizer();
        organizer->setBalance(organizer->getBalance() + ((price * qty) - service_profit));
        setServiceProfit(getServiceProfit() + service_profit);
        return;
    }
}

// Prints the users balance 
void EventManager::printBalance(User* user) const {
    std::cout << "BALANCE: " << user->getBalance() << std::endl;
}

// Handles side effects of selling a ticket to an event
void EventManager::sellTicket(User* user, int event_id) {
    Event* event = nullptr;
    std::vector<Event*>& history = user->getHistory();
    for(auto it = history.begin(); it != history.end(); it++){
        if((*it)->getId() == event_id){
            event = *it;
            history.erase(it);
            break;
        }
    }
    if(event == nullptr){
        std::cout << "EVENT NOT FOUND... ";
        return;
    }
    double price = event->getPrice() * .95;
    user->setBalance(user->getBalance() + price);
    if(event->getTicketStatus() == TicketStatus::SoldOut){
        event->setTicketStatus(TicketStatus::ForResale);
    }
    double profit = event->getPrice() * .05;
    setServiceProfit(getServiceProfit() + profit);
    event->setAvailableTickets(event->getAvailableTickets() + 1);

    std::cout << "TICKET SOLD." << std::endl;
}

void EventManager::loadFromCSV() {
    std::ifstream events("Events.csv");
    std::string e_line;
    while(std::getline(events, e_line)){
        if(e_line.empty()){
            continue;
        }
        Event* event = EventFactory::createEventFromCSV(useEventId(), e_line);
        if(event){
            available_events_[event->getId()] = event;
        }
    }
    std::fstream users("Users.csv");
    std::string u_line;
    while(std::getline(users, u_line)){
        if(u_line.empty()){
            continue;
        }
        std::vector<std::string> variables = split(u_line, ',');
        if(variables.at(0) == "Attendee"){
            User* user = new Attendee(useUserId(), variables.at(1), std::stod(variables.at(2)));
            if(variables.size() > 3){
                std::vector<std::string> s_history = split(variables.at(3), '|');
                std::vector<Event*> history;
                for(auto it : s_history){
                    if(it.empty()){
                        continue;
                    }
                    Event* event = getEvent(std::stoi(it));
                    if(event){
                        history.push_back(event);
                    }
                }
                user->setHistory(history);
            }
            users_[user->getId()] = user;
        }
        else {
            User* user = new Organizer(useUserId(), variables.at(1), std::stod(variables.at(2)));
            if(variables.size() > 3){
                std::vector<std::string> s_history = split(variables.at(3), '|');
                std::vector<Event*> history;
                for(auto it : s_history){
                    if(it.empty()){
                        continue;
                    }
                    Event* event = getEvent(std::stoi(it));
                    if(event){
                        history.push_back(event);
                        event->setOrganizer(user);
                    }
                }
                user->setHistory(history);
            }
            users_[user->getId()] = user;
        }
    }
}

void EventManager::addFunds(User* user, double funds) {
    user->setBalance(user->getBalance() + funds);
}
