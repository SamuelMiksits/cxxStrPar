
#include "parsingLibrary.h"

char * strPar::stringToCharPointer(std::string str) {

    int i = 0;
    while (str[i] != '\0' && str[i] != '\r' && str[i] != '\n') {
        i++;
    }

    int strlen = i;
    char *tmp = new char[strlen + 1]; //heap allocated
    i = 0;

    for(i = 0; i < strlen; i++) {
        tmp[i] = str[i];
    }

    tmp[i] = '\0';
    return tmp;

}

//Search if a char is in a string 
bool strPar::isIn(const char * str, char search) {
    
    int i = 0;
    while (str[i] != '\0' && str[i] != '\r' && str[i] != '\n') {
        if (str[i] == search) {
            return true;
        }
        i++;
    }

    return false;
}

bool strPar::isIn(std::string str, char search) {

    for (auto it = str.begin(); it != str.end(); ++it) {
        if (*it == search)
            return true;
    }

    return false;
}

//Check if a char pointer is in a char pointers
bool strPar::isIn(const char * str, const char * search) {

    //start by finding length of str and search
    int strlen = strPar::charPointerLen(str);
    int searchlen = strPar::charPointerLen(search); 
    bool searchFound = true;

    int i = 0;
    int j = 0;
    while(i + searchlen <= strlen) {
        searchFound = true;
        while(j < searchlen) {
            if (*(str + i + j) != *(search + j)) {
                searchFound = false;
                break;
            }
            j++;
        }
        if (searchFound)
            return true;
        j = 0;
        i++;
    }

    return false;
}

//Check if a string is in a string
bool strPar::isIn(std::string str, const char * search) {

    //start by finding length of str and search
    int strlen = str.size();
    int searchlen = strPar::charPointerLen(search); 
    bool searchFound = true;

    int i = 0;
    int j = 0;
    while(i + searchlen <= strlen) {
        searchFound = true;
        while(j < searchlen) {
            if (str[i + j] != *(search + j)) {
                searchFound = false;
                break;
            }
            j++;
        }
        if (searchFound)
            return true;
        j = 0;
        i++;
    }

    return false;
}

//Return length of char pointer
int strPar::charPointerLen(const char * str) {
    
    int i = 0;
    while (str[i] != '\0' && str[i] != '\r' && str[i] != '\n') {
        i++;
    }

    return i;
}

//Copy the values of a char pointer to another char pointer
char * strPar::copyCharPointer(const char * str) {

    int strlen = strPar::charPointerLen(str);
    char *cpy = new char[strlen + 1];

    int i = 0;
    for(i = 0; i<strlen; i++) {
        cpy[i] = str[i];
    }

    cpy[i] = '\0';
    return cpy;
}

//Add char at the end of a char pointer
char * strPar::appendCharToPointer(char * str, char newchar) {
    
    //Create a new char pointer, copy over old char pointer and delete it.
    int strlen = strPar::charPointerLen(str);
    char * newstr = new char[strlen + 2];

    for (int i = 0; i < strlen; i++) {
        *(newstr + i) = *(str + i);
    }

    newstr[strlen] = newchar;
    newstr[strlen + 1] = '\0';

    delete[] str;
    return newstr;
}

//Append a char to a char pointer
//NOTE: This function does not create a new char pointer and could potentially write out of bounds,
//use only if you know that your char pointer is long enough!
char * strPar::appendCharToPointerUnsafe(char * str, char newchar) {
    
    //Create a new char pointer, copy over old char pointer and delete it.
    int strlen = strPar::charPointerLen(str);
    str[strlen] = newchar;
    str[strlen + 1] = '\0';
    return str;
}

//Create pointer to char pointer from char pointer and delimiter
//When you want to while loop through it use while(!strcmp(list[i], "\n\n"))
char ** strPar::split(const char * str, char c) {

    int i = 0;
    int j = 0;
    int k = 0;
    int delimCount = 0;

    // Count amount of times delimiter appears
    while (str[i] != '\0') {
        if (str[i] == c) {
            delimCount++;
        }
        i++;
    }

    int strlen = i;

    char **lines = new char*[delimCount + 2]; //If there are 4 occurences of delimiter => 5 substrings + end token
    char *tmp = new char[strlen+1]; //catchall size, will max be as large as the entire string itself

    i = 0;

    while (*(str + i) != '\0') {

        if (*(str + i) == c) {

            *(tmp + k) = '\0';
            *(lines + j) = new char[k+1];

            for(int l = 0; l<=k; l++) {
                lines[j][l] = tmp[l];
            }

            delete[] tmp;
            tmp = new char[strlen+1]; //delete and create a new instance of tmp
            
            i++;
            j++;
            k = 0;
        }

        else {
            *(tmp + k) = *(str + i);
            i++;
            k++;
        }
    }

    *(tmp + k) = '\0';
    *(lines + j) = new char[k+1];

    for(int l = 0; l<=k; l++) {
        lines[j][l] = tmp[l];
    }

    delete[] tmp;
    j++;

    *(lines + j) = new char[3];
    lines[j][0] = '\n';
    lines[j][1] = '\n';
    lines[j][2] = '\0';

    return lines;
}

//Create pointer to char pointer from char pointer and delimiter
//When you want to while loop through it use while(!strcmp(list[i], "\n\n"))
char ** strPar::split(const char * str, const char * c) {

    int i = 0;
    int j = 0;
    int k = 0;
    int delimCount = 0;

    int strlen = strPar::charPointerLen(str);
    int strlen2 = strPar::charPointerLen(c);

    // Count amount of times delimiter appears
    while (i <= strlen - strlen2) {
        j = 0;
        while (j < strlen2) {
            if (str[i+j] == c[j])
                j++;
            else
                break;
        }
        if (j == strlen2)
            delimCount++;
        i++;
    }

    char **lines = new char*[delimCount + 2]; //If there are 4 occurences of delimiter => 5 substrings + end token
    char *tmp = new char[strlen+1]; //catchall size, will max be as large as the entire string itself

    i = 0;
    j = 0;

    //while (i <= strlen - strlen2) {
    while (i < strlen) {

        bool delimFound = true;

        if (i <= strlen - strlen2) {
            for (int l = 0; l < strlen2; l++) {
                if (*(str + i + l) != *(c + l))
                {
                    delimFound = false;
                    break;
                }
            }
        }
        else
            delimFound = false;

        if (delimFound) {

            *(tmp + k) = '\0';
            *(lines + j) = new char[k+1];

            for(int l = 0; l<=k; l++) {
                lines[j][l] = tmp[l];
            }

            delete[] tmp;
            tmp = new char[strlen+1]; //delete and create a new instance of tmp
            
            i += strlen2;
            j++;
            k = 0;
        }

        else {
            *(tmp + k) = *(str + i);
            i++;
            k++;
        }
    }

    *(tmp + k) = '\0';
    *(lines + j) = new char[k+1];

    for(int l = 0; l<=k; l++) {
        lines[j][l] = tmp[l];
    }

    delete[] tmp;
    j++;

    *(lines + j) = new char[3];
    lines[j][0] = '\n';
    lines[j][1] = '\n';
    lines[j][2] = '\0';

    return lines;
}

//Deletes a char ** created from split method
void strPar::deleteStringList(char ** list) {
    
    int i = 0;
    while (strcmp(list[i], "\n\n")) {
        delete[] list[i];
        i++;
    }
    delete[] list[i];
    delete[] list;
}

//Create vector of strings from string and char delimiter
std::vector<std::string> strPar::split(std::string str, char c) {

    std::vector<std::string> list = std::vector<std::string>();
    std::string tmp = std::string();

    int i = 0;
    int j = 0;
    int k = 0;
    int delimCount = 0;

    // Count amount of times delimiter appears
    while (str[i] != '\0') {
        if (str[i] == c) {
            delimCount++;
        }
        i++;
    }

    int strlen = i;

    i = 0;

    while (str[i] != '\0') {

        if (str[i] == c) {

            tmp[k] = '\0';
            list.push_back(tmp);
            tmp = std::string();
            i++;
            j++;
            k = 0;
        }

        else {
            tmp.push_back(str[i]);
            i++;
            k++;
        }
    }

    tmp[k] = '\0';
    list.push_back(tmp);
    tmp = std::string();

    return list;
}

//Create vector of strings from string and char delimiter
std::vector<std::string> strPar::split(std::string str, const char * c) {

    std::vector<std::string> list = std::vector<std::string>();
    std::string tmp = std::string();

    int i = 0;
    int j = 0;
    int k = 0;
    int delimCount = 0;

    int strlen2 = strPar::charPointerLen(c);

    // Count amount of times delimiter appears
    while (i <= str.size() - strlen2) {
        j = 0;
        while (j < strlen2) {
            if (str[i+j] == c[j])
                j++;
            else
                break;
        }
        if (j == strlen2)
            delimCount++;
        i++;
    }

    i = 0;
    j = 0;

    while (i < str.size()) {

        bool delimFound = true;
        
        if (i <= str.size() - strlen2) {
            for (int l = 0; l < strlen2; l++) {
                if (str[i + l] != *(c + l))
                {
                    delimFound = false;
                    break;
                }
            }
        }
        else
            delimFound = false;

        if (delimFound) {
            tmp[k] = '\0';
            list.push_back(tmp);
            tmp = std::string();
            i += strlen2;
            j++;
            k = 0;
        }

        else {
            tmp.push_back(str[i]);
            i++;
            k++;
        }
    }

    tmp[k] = '\0';
    list.push_back(tmp);
    tmp = std::string();

    return list;
}

//Method that strips a char from the left side of a char *
void strPar::lstrip(char * &str, char c) {
    
    while (*str == c){
        int strlen = strPar::charPointerLen(str);
        char * tmp = new char[strlen];
        for(int i = 1; i <= strlen; i++){
            *(tmp + i - 1) = *(str + i);
        }
        delete[] str;
        str = tmp;
    }
}

//Method that strips a char from the left side of a string
void strPar::lstrip(std::string &str, char c) {
    
    while(str[0] == c)
        str = str.substr(1,str.size() - 1);
}

//Method that strips a char * from the left side of a char *
void strPar::lstrip(char * &str, const char * c) {

    int strlen = strPar::charPointerLen(str);
    int strlen2 = strPar::charPointerLen(c);

    if (strlen2 == 0 || strlen2 > strlen)
        return;

    int i = 0;
    while(i < strlen) {
        if (i == strlen2) {

            char * tmp = new char[strlen];
            for(int i = strlen2; i <= strlen; i++){
                *(tmp + i - strlen2) = *(str + i);
            }
            delete[] str;
            str = tmp;

            i = 0;
            strlen = strPar::charPointerLen(str);
            if (strlen2 > strlen)
                return;
        }
        if (*(str + i) != *(c + i))
            return;
        i++;
    }

}

//Method that strips a char * from the left side of a string
void strPar::lstrip(std::string &str, const char * c) {
    
    int strlen = str.size();
    int strlen2 = strPar::charPointerLen(c);

    if (strlen2 == 0 || strlen2 > strlen)
        return;

    int i = 0;
    while(i < strlen) {
        if (i == strlen2) {
            i = 0;
            str = str.substr(strlen2, str.size() - 1);
            strlen = str.size();
            if (strlen2 > strlen)
                return;
        }
        if (str[i] != *(c + i))
            return;
        i++;
    }
}

//Method that strips a char from the right side of a char *
void strPar::rstrip(char * &str, char c) {

    int strlen = strPar::charPointerLen(str);

    while (*(str + strlen - 1) == c){
        char * tmp = new char[strlen];
        for(int i = 0; i < strlen - 1; i++){
            *(tmp + i) = *(str + i);
        }
        *(tmp + strlen - 1) = '\0'; 
        delete[] str;
        str = tmp;
        strlen = strPar::charPointerLen(str);
    }
}

//Method that strips a char from the right side of a string
void strPar::rstrip(std::string &str, char c) {
    
    while(str[str.size()-1] == c)
        str.pop_back();
}

//Method that strips a char * from the right side of a char *
void strPar::rstrip(char * &str, const char * c) {

    int strlen = strPar::charPointerLen(str);
    int strlen2 = strPar::charPointerLen(c);

    if (strlen2 == 0 || strlen2 > strlen)
        return;

    int i = 0;
    while(i < strlen) {
        if (i == strlen2) {

            char * tmp = new char[strlen];
            for(int i = 0; i < (strlen - strlen2); i++){
                *(tmp + i) = *(str + i);
            }
            *(tmp + strlen - strlen2) = '\0';
            delete[] str;
            str = tmp;

            i = 0;
            strlen = strPar::charPointerLen(str);
            if (strlen2 > strlen)
                return;
        }
        if (*(str + strlen - 1 - i) != *(c + strlen2 - 1 - i))
            return;
        i++;
    }

}

//Method that strips a char * from the right side of a string
void strPar::rstrip(std::string &str, const char * c) {

    int strlen = str.size();
    int strlen2 = strPar::charPointerLen(c);

    if (strlen2 == 0 || strlen2 > strlen)
        return;

    int i = 0;
    while(i < strlen) {
        if (i == strlen2) {
            i = 0;
            for(int j = 0; j < strlen2; j++) {
                str.pop_back();
            }
            strlen = str.size();
            if (strlen2 > strlen)
                return;
        }
        if (str[strlen - 1 - i] != *(c + strlen2 - 1 - i))
            return;
        i++;
    }
}

//Method that strips a char from both sides of a char *
void strPar::strip(char * &str, char c) {
    
    //left side 
    strPar::lstrip(str,c);
    //right side
    strPar::rstrip(str,c);

}

//Method that strips a char from both sides of a string
void strPar::strip(std::string &str, char c) {
    
    //left side 
    strPar::lstrip(str,c);
    //right side
    strPar::rstrip(str,c);
}

//Method that strips a char * from both sides of a char *
void strPar::strip(char * &str, const char * c) {
    
    //left side 
    strPar::lstrip(str,c);
    //right side
    strPar::rstrip(str,c);
}

//Method that strips a char * from both sides of a string
void strPar::strip(std::string &str, const char * c) {
    
    //left side 
    strPar::lstrip(str,c);
    //right side
    strPar::rstrip(str,c);
}

//Call with a filename, returns a vector of strings
std::vector<std::string> strPar::vectorFromFile(const char * filename) {

    std::vector<std::string> list = std::vector<std::string>();
    std::string tmp = std::string();
    std::ifstream file(filename);

    if (file.is_open()) {
        while(getline(file, tmp)) {
        list.push_back(tmp);
        }
    }
    
    file.close();

    return list;
}

//Call with a filename, returns a vector of ints
std::vector<int> strPar::intVectorFromFile(const char * filename) {

    std::vector<int> list = std::vector<int>();
    std::string tmp = std::string();
    std::ifstream file(filename);

    if (file.is_open()) {
        while(getline(file, tmp)) {
        list.push_back(stoi(tmp));
        }
    }
    
    file.close();

    return list;
}

//Call with a filename and char delimiter, returns a vector of vectors of strings
std::vector<std::vector<std::string>> strPar::vectorFromFileDelimiter(const char * filename, char c) {
    
    std::vector<std::vector<std::string>> listlist = std::vector<std::vector<std::string>>();
    std::vector<std::string> list = std::vector<std::string>();
    std::string tmp = std::string();
    std::ifstream file(filename);

    if (file.is_open()) {
        while(getline(file, tmp)) {
            list = strPar::split(tmp, c);
            listlist.push_back(list);
        }
    }
    
    file.close();
    return listlist;
}

std::vector<std::vector<std::string>> strPar::vectorFromFileDelimiter(const char * filename, const char * str) {

    std::vector<std::vector<std::string>> listlist = std::vector<std::vector<std::string>>();
    std::vector<std::string> list = std::vector<std::string>();
    std::string tmp = std::string();
    std::ifstream file(filename);

    if (file.is_open()) {
        while(getline(file, tmp)) {
            list = strPar::split(tmp, str);
            listlist.push_back(list);
        }
    }
    
    file.close();
    return listlist;
}
