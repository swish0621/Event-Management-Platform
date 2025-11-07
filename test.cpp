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

TEST_CASE("TEST_EVENT_CREATION", "[EVENT]"){
    EventManager* manager = EventManager::getInstance();
    std::istringstream input("2\nJoe Jones\n100\n");
    std::streambuf* old = std::cin.rdbuf(input.rdbuf());
    manager->createUser();
    std::cin.rdbuf(old);
    User* user = manager->getUser(0);
    
    SECTION("CONCERT"){
        std::istringstream input1("1\nConcert\n99.99\n100\nJake,John,James\n1\n2025\n12\n05\n12\n30\n");
        std::streambuf* old1 = std::cin.rdbuf(input1.rdbuf());
        manager->createEvent(user);
        std::cin.rdbuf(old1);

        Event* event = manager->getEvent(0);
        REQUIRE(event->getEventName() == "Concert");
        REQUIRE(event->getOrganizer() == user);
        REQUIRE(event->getPrice() == 99.99);
        REQUIRE(event->getAvailableTickets() == 100);
        REQUIRE(event->getEventCategory() == EventCategory::Concert);
    }
    SECTION("SPORT"){
        std::istringstream input1("2\nSport\n99.99\n100\n2025\n12\n05\n12\n30\nRangers\nCardinals\n8\n");
        std::streambuf* old1 = std::cin.rdbuf(input1.rdbuf());
        manager->createEvent(user);
        std::cin.rdbuf(old1);

        Event* event = manager->getEvent(1);
        REQUIRE(event->getEventName() == "Sport");
        REQUIRE(event->getOrganizer() == user);
        REQUIRE(event->getPrice() == 99.99);
        REQUIRE(event->getAvailableTickets() == 100);
        REQUIRE(event->getEventCategory() == EventCategory::Sport);
    }
}
