#include "EventManager.h"

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
        User* user = new Attendee(id, name, balance);
    }
    else {
        User* user = new Organizer(id, name, balance);
    }
    addUser(user);
    return user; 
}

void EventManager::createEvent(User* organizer) {}

Event* EventManager::getEvent(int id) const {}

void EventManager::moveToAvailable(int id) {}

void EventManager::moveToUnavailable(int id) {}

void EventManager::printAvailableEvents() const {}

void EventManager::purchaseEvent(User* user, int event_id, int qty) {}

void EventManager::printBalance(User* user) const {}

void EventManager::sellTicket(User* user, int event_id) {}

void EventManager::printUserHistory(int id) const {}
