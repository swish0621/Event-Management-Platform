#include "EventManager.h"

int main() {
    EventManager* manager = EventManager::getInstance();
    manager->loadFromCSV();
    std::cout <<    "WELCOME TO EVENTPASS\n" <<
                    "CREATE NEW USER OR LOGIN:\n" <<
                    "1: CREATE NEW USER\n" <<
                    "2: LOGIN" << std::endl;
    std::string login_input;
    std::cin >> login_input;
    
    User* user;
    if(std::stoi(login_input) == 1){
        user = manager->createUser();
    }
    else {
        std::cout << "ENTER USER ID: " << std::endl;
        std::string id_input;
        std::cin >> id_input;
       user = manager->getUser(std::stoi(id_input));
    }
    bool quit = false;
    while(!quit){
        if(user->getRole() == Role::Attendee){
            std::cout <<    "MAKE A SELECTION;\n" <<
                            "1: LIST AVAILABLE EVENTS\n" <<
                            "2: PURCHASE EVENT\n" <<
                            "3: SELL TICKET\n" <<
                            "4: SHOW HISTORY\n" <<
                            "5: CHECK BALANCE\n" <<
                            "6: QUIT" << std::endl;
            std::string selection;
            std::cin >> selection;
            switch(std::stoi(selection)){
                case 1:
                    manager->printAvailableEvents();
                    break;
                case 2:
                {
                    std::cout << "ENTER EVENT ID TO PURCHASE:" << std::endl;
                    std::string id;
                    std::cin >> id;
                    std::cout << "ENTER QUANTITY TO PURCHASE:" << std::endl;
                    std::string qty;
                    std::cin >> qty;
                    manager->purchaseEvent(user, std::stoi(id), std::stoi(qty));
                    break;
                }
                case 3:
                {
                    std::cout << "ENTER EVENT ID TO SELL:" << std::endl;
                    std::string id;
                    std::cin >> id;
                    manager->sellTicket(user, std::stoi(id));
                    break;
                }
                case 4:
                    for(auto it : user->getHistory()){
                        std::cout << it;
                    }
                    break;
                case 5:
                    user->getBalance();
                case 6:
                    quit = true;
                    break;
                default:
                    std::cout << "INVALID SELECITON" << std::endl;
            }

        }
        else {
            std::cout <<    "MAKE A SELECTION;\n" <<
                            "1: CREATE NEW EVENT\n" <<
                            "2: SHOW HISTORY\n" <<
                            "3: CHECK BALANCE\n" <<
                            "4: QUIT" << std::endl;
            std::string selection;
            std::cin >> selection;
            switch(std::stoi(selection)){
                case 1:
                    manager->createEvent(user);
                    break;
                case 2:
                {
                    for(auto it : user->getHistory()){
                        std::cout << it;
                    }
                    break;
                }
                case 3:
                    user->getBalance();
                    break;
                case 4:
                    quit = true;
                    break;
                default:
                    std::cout << "INVALID SELECITON" << std::endl;
            }
        }
    }
    return 0;
};
