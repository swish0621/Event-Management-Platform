#include <string>
#include <vector>

// removes spaces in the front and back of a item if present 
std::string stripSpaces(std::string input){
    if(input.empty()){
        return input;
    }

    std::size_t start = 0;
    std::size_t end = input.size();

    if(input.front() == ' ') { start += 1; }
    if(input.back() == ' ') { end -= 1; }
    
    return input.substr(start, end - start);
}

// tranforms comma separated strings into a vector of strings
std::vector<std::string> split(std::string input, char delimiter){
    std::vector<std::string> store;
    int i = 0;
    int start = 0; 
    for(auto it = input.begin(); it != input.end(); it++, i++){
        if(*it == delimiter){
            store.push_back(stripSpaces(input.substr(start, i - start)));
            start = i + 1;
        }
    }
    store.push_back(stripSpaces(input.substr(start)));

    return store;
}
