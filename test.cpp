#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cassert>
#include "parsingLibrary.h"

int main() {

    
    std::string str = std::string("apple::");
    std::vector<std::string> list = strPar::split(str, "::");
    
    std::cout << (list[1] == std::string("1")) << std::endl;

    /*
    const char * str = "apple::1";
    char ** list = strPar::split(str, "::");

    std::cout << (std::string("a") == std::string("b")) << std::endl;
    */
   
    return 0;
}