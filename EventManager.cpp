#include "EventManager.h"
#include "EventFactory.h"

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

void EventManager::moveToAvailable(int id) {}

void EventManager::moveToUnavailable(int id) {}

void EventManager::printAvailableEvents() const {}

void EventManager::purchaseEvent(User* user, int event_id, int qty) {}

void EventManager::printBalance(User* user) const {}

void EventManager::sellTicket(User* user, int event_id) {}

void EventManager::printUserHistory(int id) const {}
