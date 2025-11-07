#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "EventManager.h"
#include "EventFactory.h"
#include "StringFunctions.h"
#include "User.h"
#include "Event.h"
#include <sstream>
#include <iostream>

TEST_CASE("TEST_USER_ATTENDEE_CREATION", "[USER-ATTENDEE]"){
    EventManager* manager = EventManager::getInstance();
    std::istringstream input("1\nJoe Jones\n100\n");
    std::streambuf* old = std::cin.rdbuf(input.rdbuf());
    manager->createUser();
    std::cin.rdbuf(old);
    User* user = manager->getUser(0);
    REQUIRE(user->getId() == 0);
    REQUIRE(user->getBalance() == 100);
    REQUIRE(user->getName() == "Joe Jones");
    REQUIRE(user->getRole() == Role::Attendee);
}

TEST_CASE("TEST_USER_ORGANIZER_CREATION", "[USER-ATTENDEE]"){
    EventManager* manager = EventManager::getInstance();
    std::istringstream input("2\nJoe Jones\n100\n");
    std::streambuf* old = std::cin.rdbuf(input.rdbuf());
    manager->createUser();
    std::cin.rdbuf(old);
    User* user = manager->getUser(0);
    REQUIRE(user->getId() == 0);
    REQUIRE(user->getBalance() == 100);
    REQUIRE(user->getName() == "Joe Jones");
    REQUIRE(user->getRole() == Role::Attendee);
}

TEST_CASE("TEST_CONCERT_EVENT_CREATION", "[CONCERT]"){
    EventManager* manager = EventManager::getInstance();
    std::istringstream input("2\nJoe Jones\n100\n");
}
