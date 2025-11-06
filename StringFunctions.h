#ifndef STRINGFUNCTIONS_H
#define STRINGFUNCTIONS_H
#include <string>
#include <vector>

// removes spaces in the front and back of a item if present 
std::string stripSpaces(std::string input);

// tranforms comma separated strings into a vector of strings
std::vector<std::string> split(std::string input, char delimiter);

#endif
