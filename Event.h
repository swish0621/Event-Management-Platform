#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <vector>

enum EventCategory { Concert, Sport, Theater, Convention, Comedy };
enum MusicGenre { Rock, Pop, Hiphop, Country, Jazz, Classical, Electronic, Metal, Indie };
enum SportType { Football, Hockey, Soccer, Basketball, Golf, MMA, Wrestling };
enum TheaterGenre { Musical, Opera, Ballet, Play };

struct DateTime{
    int year;
    int month;
    int day;
    int hour;
    int minute;

};

class Event {
    protected:
        int id_;
        std::string event_name_;
        double price_;
        int available_tickets_;

    public:
        Event(int id, std::string event_name, double price, int available_tickets) :
            id_(id), event_name_(event_name), price_(price),
            available_tickets_(available_tickets) {}
        virtual ~Event() = default;

        int getId() const { return id_; }
        double getPrice() const { return price_; }
        virtual EventCategory getEventCategory() const = 0;
        const std::string getEventName() const { return event_name_; }
        bool hasTickets(int qty) const { return (available_tickets_ - qty) >= 0; }

};

class Concert : public Event {
    protected:
        EventCategory category_ = EventCategory::Concert;
    
    public:
        Concert(int id, std::string event_name, double price, int available_tickets) : 
            Event(id, event_name, price, available_tickets) {}
        virtual ~Concert() = default;
        virtual MusicGenre getGenre() const = 0;
        EventCategory getEventCategory() const override { return category_; }
};

class ConcertEvent : public Concert {
    protected:
        std::vector<std::string> artists_;
        DateTime event_date_;
        MusicGenre genre_;
    
    public:
        ConcertEvent(int id, std::string event_name, double price, int available_tickets, 
            std::vector<std::string> artists, MusicGenre genre, DateTime event_date) :
            Concert(id, event_name, price, available_tickets), artists_(artists), event_date_(event_date), genre_(genre) {}

        virtual ~ConcertEvent() = default;
        MusicGenre getGenre() const override { return genre_; }

        std::vector<std::string> getArtists() const { return artists_; }
        void setArtists(std::vector<std::string> artists) { artists_ = artists; }

        DateTime getDate() const { return event_date_; }
        void setDate(DateTime date) { event_date_ = date; }

};

class Sport : public Event {
    protected:
        EventCategory category_ = EventCategory::Sport;
        SportType type_;
    
    public:
        Sport(int id, std::string event_name, double price, int available_tickets) : 
            Event(id, event_name, price, available_tickets) {}
        
        virtual ~Sport() = default;
        virtual SportType getSportType() const = 0;
        EventCategory getEventCategory() const override { return category_; }
};

class SportEvent : public Sport {
    protected:
        std::string away_team_;
        std::string home_team_;
        SportType sport_type_;
        DateTime event_date_;
    
    public: 
        SportEvent(int id, std::string event_name, double price, int available_tickets,
            DateTime event_date, std::string away_team, std::string home_team, SportType sport_type) :
            Sport(id, event_name, price, available_tickets), away_team_(away_team),
            home_team_(home_team),sport_type_(sport_type), event_date_(event_date) {}

        virtual ~SportEvent() = default;
        SportType getSportType() const override { return sport_type_; }

        std::string getAwayTeam() const { return away_team_; }
        void setAwayTeam(std::string away_team) { away_team_ = away_team; }

        std::string getHomeTeam() const { return home_team_; }
        void setHomeTeam(std::string home_team) { home_team_ = home_team; }

        DateTime getDate() const { return event_date_; }
        void setDate(DateTime date) { event_date_ = date; } 

};

class Theater : public Event {
    protected: 
        EventCategory category_ = EventCategory::Theater;

    public:
        Theater(int id, std::string event_name, double price, int available_tickets) : 
            Event(id, event_name, price, available_tickets) {}

        virtual ~Theater() = default;
        EventCategory getEventCategory() const override { return category_; }
        virtual TheaterGenre getTheaterGenre() const = 0;

};

class TheaterEvent : public Theater {
    protected:
        std::string original_title_;
        std::string director_;
        std::vector<std::string> performers_;
        TheaterGenre genre_;
        bool age_restricted_;
        DateTime event_date_;

    public:
        TheaterEvent(int id, std::string event_name, double price, int available_tickets, std::string original_title, 
            std::string director, std::vector<std::string> performers, TheaterGenre genre, bool age_restricted, DateTime date) :
            Theater(id, event_name, price, available_tickets), original_title_(original_title), director_(director), 
            performers_(performers), genre_(genre), age_restricted_(age_restricted), event_date_(date) {}

        virtual ~TheaterEvent() = default;
        TheaterGenre getTheaterGenre() const override { return genre_; }

        std::vector<std::string> getPerformers() const { return performers_; }
        void setPerformers(std::vector<std::string> performers) { performers_ = performers; }

        std::string getOriginalTitle() const { return original_title_; }
        void setOriginalTitle(std::string title) { original_title_ = title; }

        bool isAgeRestricted() const { return age_restricted_; }
        void setAgeRestricted(bool is_restricted) { age_restricted_ = is_restricted; }

        DateTime getDate() const { return event_date_; }
        void setDate(DateTime date) { event_date_ = date; } 
};

class Convention : public Event {
    protected:
        EventCategory category_ = EventCategory::Convention;

    public:
        Convention(int id, std::string event_name, double price, int available_tickets) :
            Event(id, event_name, price, available_tickets) {}
        virtual ~Convention() = default;
        EventCategory getEventCategory() const override { return category_; }
        virtual std::string getIndustryType() const = 0;
};

class ConventionEvent : public Convention {
    protected:
        std::string industry_type_;
        int num_exhibitors_;
        std::vector<std::string> exhibitors_;
        std::vector<std::string> sponsors_;
        int num_days_;
        DateTime event_date_;

    public:
        ConventionEvent(int id, std::string event_name, double price, int available_tickets, 
            std::string industy_type, int num_exhibitors, std::vector<std::string> exhibitors,
            std::vector<std::string> sponsors, int num_days, DateTime date) :
            Convention(id, event_name, price, available_tickets), industry_type_(industy_type),
            num_exhibitors_(num_exhibitors), exhibitors_(exhibitors), sponsors_(sponsors), 
            num_days_(num_days), event_date_(date) {}

        virtual ~ConventionEvent() = default;
        std::string getIndustryType() const override { return industry_type_; }

        int getNumExhibitors() const { return num_exhibitors_; }
        void setNumExhibitors(int num_exhibitors) { num_exhibitors_ = num_exhibitors; }

        std::vector<std::string> getExhibitors() const { return exhibitors_; }
        void setExhibitors(std::vector<std::string> exhibitors) { exhibitors_ = exhibitors; }

        std::vector<std::string> getSponsors() const { return sponsors_; }
        void setSponsors(std::vector<std::string> sponsors) { sponsors_ = sponsors; }

        int getNumDays() const { return num_days_; }
        void setNumDays(int num_days) { num_days_ = num_days; }
};

class Comedy : public Event {
    protected:
        EventCategory category_ = EventCategory::Comedy;
    
    public:
        Comedy(int id, std::string event_name, double price, int available_tickets) : 
            Event(id, event_name, price, available_tickets) {}
        virtual ~Comedy() = default;
        EventCategory getEventCategory() const override { return category_; }
        virtual std::string getPerformer() const = 0;
};

class ComedyEvent : public Comedy {
    protected:
        std::string performer_;
        bool age_restricted_;
        std::vector<std::string> topics_;
        DateTime event_date_;
    
    public:
        ComedyEvent(int id, std::string event_name, double price, int available_tickets, 
            std::string performer, bool age_restricted, std::vector<std::string> topics, DateTime date) :
            Comedy(id, event_name, price, available_tickets), performer_(performer), 
            age_restricted_(age_restricted), topics_(topics), event_date_(date) {}

        virtual ~ComedyEvent() = default;
        std::string getPerformer() const override { return performer_; }

        bool getAgeRestricted() const { return age_restricted_; }
        void setAgeRestricted(bool age_restricted) {age_restricted_ = age_restricted; }

        std::vector<std::string> getTopics() const { return topics_; }
        void setTopics(std::vector<std::string> topics) { topics_ = topics; }

};

#endif 
