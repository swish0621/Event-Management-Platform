#include "EventManager.h"
#include "EventFactory.h"
#include <cmath>

EventManager* EventManager::instance_ = nullptr;

int EventManager::useUserId() {
    int id = user_id_;
    user_id_++;
    return id;
}

int EventManager::useEventId() {
    int id = event_id_;
    event_id_++;
    return id;
}

User* EventManager::getUser(int id) const {
    auto user = users_.find(id);
    if(user != users_.end()){
        return user->second;
    }
    return nullptr;
}

void EventManager::addUser(User* user) {
    users_[user->getId()] = user;
}

User* EventManager::createUser(int id) {
    std::string input;
    std::string name;
    std::string s_balance;
    std::cout << "SELECT A USER TYPE:\n" << "1: ATTENDEE\n2:ORGANIZER" << std::endl;
    std::cin >> input;

    std::cout << "ENTER YOUR NAME:" << std::endl;
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

void EventManager::createEvent(User* organizer) {
    EventFactory* factory = EventFactory::getInstance();

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

    Event* event = factory->createEvent(useEventId(), category);
    event -> setOrganizer(organizer);
    available_events_[event->getId()] = event;
}

Event* EventManager::getEvent(int id) const {
    auto available = available_events_.find(id);
    auto unavailable = unavailable_events_.find(id);
    if(available == available_events_.end() && unavailable == unavailable_events_.end()) {
        return nullptr;
    }
    if(available != available_events_.end()){
        return available->second;
    }
    return unavailable->second;
}

void EventManager::moveToAvailable(int id) {
    auto event = unavailable_events_.find(id);
    if(event != unavailable_events_.end()){
        available_events_[id] = event->second;
        unavailable_events_.erase(event);
    }
}

void EventManager::moveToUnavailable(int id) {
    auto event = available_events_.find(id);
    if(event != available_events_.end()){
        unavailable_events_[id] = event->second;
        available_events_.erase(event);
    }
}

void EventManager::printAvailableEvents() const {}

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
    bool has_balance = balance >= price * qty;
    bool purchase = has_balance && has_tickets;
    
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
        int can_purchase = std::floor(balance / price);
        if(can_purchase == 0){
            return;
        }
        std::cout << "NOT ENOUGH FUNDS.\nYOU CAN PURCHASE" << can_purchase << "TICKETS\nPURCHASE?\n1: YES\n2: NO" << std::endl;
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
}

void EventManager::printBalance(User* user) const {}

void EventManager::sellTicket(User* user, int event_id) {}

void EventManager::printUserHistory(int id) const {}
