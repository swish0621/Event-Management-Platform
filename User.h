#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include "Event.h"

class User {
    protected:
        int id_;
        std::string name_;
        double balance_;
        std::vector<Event*> history_;
    
    public:
        User(int id, std::string name, double balance) : id_(id), name_(name), balance_(balance){}
        virtual ~User() = default;
        virtual std::string getRole() const = 0;

        int getId() const { return id_; }
        std::string getName() const { return name_; }
        double getBalance() const { return balance_; }
        void setBalance(double new_balance) { balance_ = new_balance; }
        std::vector<Event*> getHistory() const { return history_; }
        void setHistory(std::vector<Event*> history) { history_ = history; }
};

class Organizer : public User {
    public: 
        Organizer(int id, std::string name, double balance) :
        User(id, name, balance) {}
        std::string getRole() const override { return "Organizer"; }
};

class Attendee : public User {
    public: 
        Attendee(int id, std::string name, double balance) :
        User(id, name, balance) {}
        std::string getRole() const override { return "Attendee"; }
};

#endif
