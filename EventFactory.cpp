#include "EventFactory.h"
#include "StringFunctions.h"
#include "Event.h"
#include <stdexcept>


EventFactory* EventFactory::instance_ = nullptr;

// intitialize event Specific values 
// pass by reference to asscoiated user prompt function to define values
// call specific event contructor and return a new object
Event* EventFactory::createEvent(int id, EventCategory category) {
    switch(category){
        case EventCategory::Concert:
        {
            std::string event_name;
            double price;
            int available_tickets;
            std::vector<std::string> artists;
            MusicGenre genre;
            DateTime event_date;

            getConcertEventValues(event_name, price, available_tickets, artists, genre, event_date);
            return new ConcertEvent(id, event_name, price, available_tickets, artists, genre, event_date);
        }
        case EventCategory::Sport:
        {
            std::string event_name;
            double price;
            int available_tickets;
            DateTime event_date;
            std::string away_team;
            std::string home_team;
            SportType sport_type;

            getSportEventValues(id, event_name, price, available_tickets, event_date, away_team, home_team, sport_type);
            return new SportEvent(id, event_name, price, available_tickets, event_date, away_team, home_team, sport_type);
        }
        case EventCategory::Theater:
        {
            std::string event_name;
            double price;
            int available_tickets;
            std::string original_title;
            std::string director;
            std::vector<std::string> performers;
            TheaterGenre genre;
            bool age_restricted;
            DateTime event_date;

            getTheaterEventValues(id, event_name, price, available_tickets, original_title, director, performers, genre, age_restricted, event_date);
            return new TheaterEvent(id, event_name, price, available_tickets, original_title, director, performers, genre, age_restricted, event_date);
        }
        case EventCategory::Convention:
        {
            std::string event_name;
            double price;
            int available_tickets;
            std::string industry_type;
            int num_exhibitors;
            std::vector<std::string> exhibitors;
            std::vector<std::string> sponsors;
            int num_days;
            DateTime event_date;

            getConventionEventValues(id, event_name, price, available_tickets, industry_type, num_exhibitors, exhibitors, sponsors, num_days, event_date);
            return new ConventionEvent(id, event_name, price, available_tickets, industry_type, num_exhibitors, exhibitors, sponsors, num_days, event_date);
        }
        case EventCategory::Comedy:
        {
            std::string event_name;
            double price;
            int available_tickets;
            std::string performer;
            bool age_restricted;
            std::vector<std::string> topics;
            DateTime event_date;

            getComedyEventValues(id, event_name, price, available_tickets, performer, age_restricted, topics, event_date);
            return new ComedyEvent(id, event_name, price, available_tickets, performer, age_restricted, topics, event_date);
        }
        default:
        {
            return nullptr;
        }
    }
}

// prompt user to input ConcertEvent values 
void EventFactory::getConcertEventValues(std::string& event_name, double& price, int& available_tickets, 
            std::vector<std::string>& artists, MusicGenre& genre, DateTime& event_date) {
                std::cout << "INPUT EVENT NAME:";
                std::getline(std::cin, event_name);
                std::cout << std::endl;

                std::cout << "INPUT EVENT PRICE:";
                std::cin >> price;
                std::cout << std::endl;

                std::cout << "INPUT NUMBER OF TICKETS AVAILABLE:";
                std::cin >> available_tickets;
                std::cin.ignore(1, '\n');
                std::cout << std::endl;

                std::cout << "INPUT COMMA SEPARATED LIST OF ARTISTS:";
                std::string artists_input; 
                std::getline(std::cin, artists_input);
                artists = split(artists_input);
                std::cout << std::endl;

                genre = getGenre();

                event_date = getDateTime();
            }


void EventFactory::getSportEventValues(int& id, std::string& event_name, double& price, int& available_tickets,
            DateTime& event_date, std::string& away_team, std::string& home_team, SportType& sport_type) {
                std::cout << "INPUT EVENT NAME:";
                std::getline(std::cin, event_name);
                std::cout << std::endl;

                std::cout << "INPUT EVENT PRICE:";
                std::cin >> price;
                std::cout << std::endl;

                std::cout << "INPUT NUMBER OF TICKETS AVAILABLE:";
                std::cin >> available_tickets;
                std::cin.ignore(1, '\n');
                std::cout << std::endl;

                event_date = getDateTime();

                std::cout << "INPUT AWAY TEAM:";
                std::cin >> away_team;
                std::cout << std::endl;

                std::cout << "INPUT HOME TEAM:";
                std::cin >> home_team;
                std::cout << std::endl;


            }
// prompt user selection to return the correct music genre
MusicGenre EventFactory::getGenre() {

    std::cout << "SELECT MUSIC GENRE:" << std::endl << "1: ROCK" << std::endl << "2: POP" << std::endl 
        << "3: HIPHOP" << std::endl << "4: COUNTRY" << std::endl << "5: JAZZ" << std::endl << "6: Classical"
        << std::endl << "7: Electronic" << std::endl << "8: METAL" << std::endl << "9: INDIE" << std::endl;
    
    std::string input;
    std::cin >> input;
    int selection = std::stoi(input);
    switch(selection){
        case 1:
            return MusicGenre::Rock;
        case 2:
            return MusicGenre::Pop;
        case 3:
            return MusicGenre::Hiphop;
        case 4:
            return MusicGenre::Country;
        case 5:
            return MusicGenre::Jazz;
        case 6:
            return MusicGenre::Classical;
        case 7:
            return MusicGenre::Electronic;
        case 8:
            return MusicGenre::Metal;
        case 9:
            return MusicGenre::Indie;
        default:
            throw std::invalid_argument("Invalid Genre. Aborting...");
    }
}

DateTime EventFactory::getDateTime() {
    std::string s_year;
    std::cout << "ENTER YEAR OF EVENT, FORMAT(2025):" << std::endl;
    std::cin >> s_year;
    int year = std::stoi(s_year);

    std::string s_month;
    std::cout << "ENTER MONTH OF EVENT, FORMAT(09):" << std::endl;
    std::cin >> s_month;
    int month = std::stoi(s_month);

    std::string s_day;
    std::cout << "ENTER DAY OF EVENT, FORMAT(09):" << std::endl;
    std::cin >> s_day;
    int day = std::stoi(s_day);

    std::string s_hour;
    std::cout << "ENTER HOUR OF EVENT, MILITARY FORMAT(18):" << std::endl;
    std::cin >> s_hour;
    int hour = std::stoi(s_hour);

    std::string s_min;
    std::cout << "ENTER MINUTE OF EVENT, FORMAT(58):" << std::endl;
    std::cin >> s_min;
    int min = std::stoi(s_min);
    DateTime date = {year, month, day, hour, min};
    return date;
}

SportType EventFactory::getSportType() {
    std::cout << "SELECT SPORT TYPE:" << std::endl << "1: FOOTBALL" << std::endl << "2: HOCKEY" << std::endl 
        << "3: SOCCER" << std::endl << "4: BASKETBALL" << std::endl << "5: GOLF" << std::endl << "6: MMA"
        << std::endl << "7: WESTLING" << std::endl;
    
    std::string input;
    std::cin >> input;
    int selection = std::stoi(input);
    switch(selection){
        case 1:
            return SportType::Football;
        case 2:
            return SportType::Hockey;
        case 3:
            return SportType::Soccer;
        case 4:
            return SportType::Basketball;
        case 5:
            return SportType::Golf;
        case 6:
            return SportType::MMA;
        case 7:
            return SportType::Wrestling;
        default:
            throw std::invalid_argument("Invalid Type. Aborting...");
    }
}
// read all necessary data from a csv file and call the correct helper based on the EventCategory
Event* EventFactory::createEventFromCSV(int id, std::string line_items) { return nullptr; }



