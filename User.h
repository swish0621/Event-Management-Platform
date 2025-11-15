#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include <iostream>

class Event;
enum class Role { Organizer, Attendee };

class User {
    protected:
        // Personal information 
        int id_;
        std::string first_name_;
        std::string last_name_;
        std::string user_name_;
        std::string password_;
        std::string email_address_;
        std::string address_;
        std::string city_;
        std::string state_;
        std::string zipcode_;

        // account specific details 
        double balance_;
        std::vector<Event*> history_;
        std::vector<std::string> interests_; 
        Role role_;

    
    public:
        User(int id, std::string first_name, std::string last_name, double balance, std::string user_name, std::string password, 
            std::string email_address, std::string address, std::string city, std::string state, std::string zipcode) 
            : 
            id_(id), first_name_(first_name), last_name_(last_name), balance_(balance), user_name_(user_name), password_(password), 
            email_address_(email_address), address_(address), city_(city), state_(state), zipcode_(zipcode) {}

        virtual ~User() = default;
        virtual Role getRole() const = 0;

        int getId() const { return id_; }

        std::string getFirstName() const { return first_name_; }
        void setFirstName(std::string first_name) { first_name_ = first_name; }

        std::string getLastName() const { return last_name_; }
        void setLastName(std::string last_name) { last_name_ = last_name; }

        std::string getUserName() const { return user_name_; }
        void setUserName(std::string username) { user_name_ = username; }

        std::string getPassword() const { return password_; }
        void setPassword(std::string password) { password_ = password; }

        std::string getEmailAddress() const { return email_address_; }
        void setEmailAddress(std::string email_address) { email_address_ = email_address; }

        std::string getAddress() const { return address_; }
        void setAddress(std::string address) { address_ = address; }

        std::string getCity() const { return city_; }
        void setCity(std::string city) { city_ = city; }

        std::string getState() const { return state_; }
        void setState(std::string state) { state_ = state; }

        std::string getZipCode() const { return zipcode_; }
        void setZipCode(std::string zipcode) { zipcode_ = zipcode; }

        double getBalance() const { return balance_; }
        void setBalance(double new_balance) { balance_ = new_balance; }

        std::vector<Event*>& getHistory() { return history_; }
        void setHistory(std::vector<Event*> history) { history_ = history; }

        std::vector<std::string> getInterests() const { return interests_; }
        void setInterests(std::vector<std::string> interests) { interests_ = interests; }
};

class Organizer : public User {
    public: 
        Organizer(int id, std::string first_name, std::string last_name, double balance, std::string user_name, std::string password, 
            std::string email_address, std::string address, std::string city, std::string state, std::string zipcode) 
            :
            User(id, first_name, last_name, balance, user_name, password, email_address, address, city, state, zipcode) 
            { role_ = Role::Organizer; }

        Role getRole() const override { return role_; }
};

class Attendee : public User {
    public: 
        Attendee(int id, std::string first_name, std::string last_name, double balance, std::string user_name, std::string password, 
            std::string email_address, std::string address, std::string city, std::string state, std::string zipcode) 
            :
            User(id, first_name, last_name, balance, user_name, password, email_address, address, city, state, zipcode) 
            { role_ = Role::Attendee; }
            
        Role getRole() const override { return role_; }
};

#endif
