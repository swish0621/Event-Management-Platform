#include "EventManager.h"

User* EventManager::getUser(int id) const {}

void EventManager::addUser(User* user) {}

void EventManager::createEvent(User* organizer) {}

Event* EventManager::getEvent(int id) const {}

void EventManager::moveToAvailable(int id) {}

void EventManager::moveToUnavailable(int id) {}

void EventManager::printAvailableEvents() const {}

void EventManager::purchaseEvent(User* user, int event_id, int qty) {}

void EventManager::printBalance(User* user) const {}

void EventManager::sellTicket(User* user, int event_id) {}

void EventManager::printUserHistory(int id) const {}
