#include "EventFactory.h"
#include "StringFunctions.h"
#include "Event.h"
#include <stdexcept>

// FACTORY ASSUMES ALL VALID INPUT!!!

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

            getSportEventValues(event_name, price, available_tickets, event_date, away_team, home_team, sport_type);
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

            getTheaterEventValues(event_name, price, available_tickets, original_title, director, performers, genre, age_restricted, event_date);
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

            getConventionEventValues(event_name, price, available_tickets, industry_type, num_exhibitors, exhibitors, sponsors, num_days, event_date);
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

            getComedyEventValues(event_name, price, available_tickets, performer, age_restricted, topics, event_date);
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
                std::string s_price;
                std::cin >> s_price;
                price = std::stod(s_price);
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


void EventFactory::getSportEventValues(std::string& event_name, double& price, int& available_tickets,
            DateTime& event_date, std::string& away_team, std::string& home_team, SportType& sport_type) {
                std::cout << "INPUT EVENT NAME:";
                std::getline(std::cin, event_name);
                std::cout << std::endl;

                std::cout << "INPUT EVENT PRICE:";
                std::string s_price;
                std::cin >> s_price;
                price = std::stod(s_price);
                std::cout << std::endl;

                std::cout << "INPUT NUMBER OF TICKETS AVAILABLE:";
                std::cin >> available_tickets;
                std::cin.ignore(1, '\n');
                std::cout << std::endl;

                event_date = getDateTime();

                std::cout << "INPUT AWAY TEAM:";
                std::getline(std::cin, away_team);
                std::cout << std::endl;

                std::cout << "INPUT HOME TEAM:";
                std::getline(std::cin, home_team);
                std::cout << std::endl;

                sport_type = getSportType();
            }

void EventFactory::getTheaterEventValues(std::string& event_name, double& price, int& available_tickets, std::string& original_title, 
            std::string& director, std::vector<std::string>& performers, TheaterGenre& genre, bool& age_restricted, DateTime& date) {
                std::cout << "INPUT EVENT NAME:";
                std::getline(std::cin, event_name);
                std::cout << std::endl;

                std::cout << "INPUT EVENT PRICE:";
                std::string s_price;
                std::cin >> s_price;
                price = std::stod(s_price);
                std::cout << std::endl;

                std::cout << "INPUT NUMBER OF TICKETS AVAILABLE:";
                std::cin >> available_tickets;
                std::cin.ignore(1, '\n');
                std::cout << std::endl;

                std::cout << "INPUT ORIGINAL TITLE:";
                std::getline(std::cin, original_title);
                std::cout << std::endl;

                std::cout << "INPUT DIRECTOR NAME:";
                std::getline(std::cin, director);
                std::cout << std::endl;

                std::cout << "INPUT COMMA SEPARATED LIST OF PERFORMERS:";
                std::string performers_input; 
                std::getline(std::cin, performers_input);
                performers = split(performers_input);
                std::cout << std::endl;

                genre = getTheaterGenre();

                std::cout << "IS THE EVENT AGE RESTRICTED?" << std::endl << "1: NO" << std::endl << "2: YES" << std::endl;
                std::string bool_age_restricted;
                std::cin >> bool_age_restricted;
                age_restricted = std::stoi(bool_age_restricted) - 1;
                std::cout << std::endl;

                date = getDateTime();

            }

void EventFactory::getConventionEventValues(std::string& event_name, double& price, int& available_tickets, 
            std::string& industry_type, int& num_exhibitors, std::vector<std::string>& exhibitors,
            std::vector<std::string>& sponsors, int& num_days, DateTime& date) {
                std::cout << "INPUT EVENT NAME:";
                std::getline(std::cin, event_name);
                std::cout << std::endl;

                std::cout << "INPUT EVENT PRICE:";
                std::string s_price;
                std::cin >> s_price;
                price = std::stod(s_price);
                std::cout << std::endl;

                std::cout << "INPUT NUMBER OF TICKETS AVAILABLE:";
                std::cin >> available_tickets;
                std::cin.ignore(1, '\n');
                std::cout << std::endl;

                std::cout << "INPUT INDUSTRY TYPE:";
                std::getline(std::cin, industry_type);
                std::cout << std::endl;

                std::cout << "INPUT NUMBER OF EXHIBITORS:";
                std::string s_num_exhibitors;
                std::cin >> s_num_exhibitors;
                num_exhibitors = std::stoi(s_num_exhibitors);
                std::cout << std::endl;

                std::cout << "INPUT COMMA SEPARATED LIST OF EXHIBITORS:";
                std::string exhibitors_input; 
                std::getline(std::cin, exhibitors_input);
                exhibitors = split(exhibitors_input);
                std::cout << std::endl;

                std::cout << "INPUT COMMA SEPARATED LIST OF SPONSORS:";
                std::string sponsors_input; 
                std::getline(std::cin, sponsors_input);
                sponsors = split(sponsors_input);
                std::cout << std::endl;

                std::cout << "INPUT NUMBER OF THE CONVENTION LASTS:";
                std::string s_num_days;
                std::cin >> s_num_days;
                num_days = std::stoi(s_num_days);
                std::cout << std::endl;

                date = getDateTime();
            }

void EventFactory::getComedyEventValues(std::string& event_name, double& price, int& available_tickets, 
            std::string& performer, bool& age_restricted, std::vector<std::string>& topics, DateTime& date) {
                std::cout << "INPUT EVENT NAME:";
                std::getline(std::cin, event_name);
                std::cout << std::endl;

                std::cout << "INPUT EVENT PRICE:";
                std::string s_price;
                std::cin >> s_price;
                price = std::stod(s_price);
                std::cout << std::endl;

                std::cout << "INPUT NUMBER OF TICKETS AVAILABLE:";
                std::cin >> available_tickets;
                std::cin.ignore(1, '\n');
                std::cout << std::endl;

                std::cout << "INPUT PERFORMER NAME:";
                std::getline(std::cin, performer);
                std::cout << std::endl;

                std::cout << "IS THE EVENT AGE RESTRICTED?" << std::endl << "1: NO" << std::endl << "2: YES" << std::endl;
                std::string bool_age_restricted;
                std::cin >> bool_age_restricted;
                age_restricted = std::stoi(bool_age_restricted) - 1;
                std::cout << std::endl;

                std::cout << "INPUT COMMA SEPARATED LIST OF TOPICS:";
                std::string topics_input; 
                std::getline(std::cin, topics_input);
                topics = split(topics_input);
                std::cout << std::endl;

                date = getDateTime();

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
//Musical, Opera, Ballet, Play
TheaterGenre EventFactory::getTheaterGenre() {
    std::cout << "SELECT THEATER GENRE:" << std::endl << "1: MUSICAL" << std::endl << "2: OPERA" << std::endl 
        << "3: BALLET" << std::endl << "4: PLAY" << std::endl;
    
    std::string input;
    std::cin >> input;
    int selection = std::stoi(input);
    switch(selection){
        case 1:
            return TheaterGenre::Musical;
        case 2:
            return TheaterGenre::Opera;
        case 3:
            return TheaterGenre::Ballet;
        case 4:
            return TheaterGenre::Play;
        default:
            throw std::invalid_argument("Invalid Genre. Aborting...");
    }
}
// read all necessary data from a csv file and call the correct helper based on the EventCategory
Event* EventFactory::createEventFromCSV(int id, std::string line_items) { return nullptr; }



