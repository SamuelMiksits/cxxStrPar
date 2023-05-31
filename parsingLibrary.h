#ifndef PARSINGLIBRARY_H
#define PARSINGLIBRARY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

namespace strPar {

//If you want to create a char pointer from a string, be my guest
char* stringToCharPointer(std::string str);

//Check if a char is in a char pointer
bool isIn(const char * str, char search);

//Check if a char is in a string
bool isIn(std::string str, char search);

//Check if a char pointer is in a char pointers
bool isIn(const char * str, const char * search);

//Check if a string is in a string
bool isIn(std::string str, const char * search);

//Calculate the "length" of a char pointer 
//NOTE: There is no 100% way of knowing how long a char pointer is, use with caution
int charPointerLen(const char * str);

//Returns a copy of a char pointer. Heap allocated so remember to delete[]
char * copyCharPointer(const char * str);

//Append a char to a char pointer.
char * appendCharToPointer(char * str, char newchar);

//Append a char to a char pointer
//NOTE: This function does not create a new char pointer and could potentially write out of bounds,
//use only if you know that your char pointer is long enough!
char * appendCharToPointerUnsafe(char * str, char newchar);

//Create vector of strings from char pointer and delimiter
char ** split(const char * str, char c = ' ');
//Create vector of strings from char pointer and delimiter
char ** split(const char * str, const char * c);

//Deletes a char ** created from splitString method
void deleteStringList(char ** list);

//Create vector of strings from string and delimiter
std::vector<std::string> split(std::string str, char c = ' ');

//Create vector of strings from string and delimiter
std::vector<std::string> split(std::string str, const char * c);

//Method that strips a char from the left side of a char *
void lstrip(char * &str, char c = ' ');
//Method that strips a char from the left side of a string
void lstrip(std::string &str, char c = ' ');
//Method that strips a char * from the left side of a char *
void lstrip(char * &str, const char * c);
//Method that strips a char * from the left side of a string
void lstrip(std::string &str, const char * c);

//Method that strips a char from both sides of a char *
void rstrip(char * &str, char c = ' ');
//Method that strips a char from both sides of a string
void rstrip(std::string &str, char c = ' ');
//Method that strips a char * from both sides of a char *
void rstrip(char * &str, const char * c);
//Method that strips a char * from both sides of a string
void rstrip(std::string &str, const char * c);

//Method that strips a char from both sides of a char *
void strip(char * &str, char c = ' ');
//Method that strips a char from both sides of a string
void strip(std::string &str, char c = ' ');
//Method that strips a char * from both sides of a char *
void strip(char * &str, const char * c);
//Method that strips a char * from both sides of a string
void strip(std::string &str, const char * c);

//Call with a filename, returns a vector of strings
std::vector<std::string> vectorFromFile(const char * filename);
//Call with a filename, returns a vector of ints
std::vector<int> intVectorFromFile(const char * filename);
//Call with a filename and char delimiter, returns a vector of vectors of strings
std::vector<std::vector<std::string>> vectorFromFileDelimiter(const char * filename, char c = ' ');
//Call with a filename and string delimiter, returns a vector of vectors of strings
std::vector<std::vector<std::string>> vectorFromFileDelimiter(const char * filename, const char * str = " ");

}

#endif