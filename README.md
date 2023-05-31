# cxxStrPar
## About

Library for ```str```ing ```par```sing in a Python-esque syntax. There are already powerful repos that support this like [pystring](https://github.com/imageworks/pystring), but this one has support for C style strings, and has features that makes this very useful for porting Advent Of Code projects from Python to C++, such as functions that allow you to generate a vector of strings from a file name, and convert them to integers, or split into a vector of vectors of strings if you want to split every row on a per whitespace basis or another delimiter token.

---

## Functions/Code examples

### ```strPar::stringToCharPointer```: 

The function ```stringToCharPointer``` returns a heap allocated (needs to be removed with ```delete[]``` afterwards) char pointer from a string:

```c++
char* stringToCharPointer(std::string str);
```

Example:

```c++
std::string str = std::string("hello");
char* strout = strPar::stringToCharPointer(str);
delete[] strout; //delete[] to avoid memory leak
```

```strout``` will be a char pointer with allocated size 6 chars containing ```{'h','e','l','l','o','\0'}```. Note: If your string has a trailing nullchar (```'\0'```), carriage return (```'\r'```) or newline (```'\n'```) the function will remove it.

---

### ```strPar::isIn```:
The function ```isIn``` can search if a ```std::string``` contains either a ```char``` or a ```char*``` or if a ```char*``` contains a ```char``` or a ```char*```, returns ```bool``` type. All function overloads:

```c++
//Check if a char is in a char pointer
bool isIn(const char * str, char search);
//Check if a char is in a string
bool isIn(std::string str, char search);
//Check if a char pointer is in a char pointer
bool isIn(const char * str, const char * search);
//Check if a string is in a string
bool isIn(std::string str, const char * search);
```

Examples:


```c++
std::string str = std::string("hello");
const char * str2 = "hello";

assert(strPar::isIn(str, 'a') == false); //Search string for char
assert(strPar::isIn(str, 'o') == true); 

assert(strPar::isIn(str2, 'a') == false); //Search char* for char
assert(strPar::isIn(str2, 'l') == true);

assert(strPar::isIn(str, "la") == false); //Search string for char*
assert(strPar::isIn(str, "lo") == true);

assert(strPar::isIn(str2, "al") == false); //Search char* for char*
assert(strPar::isIn(str2, "ell") == true);
```
---

### ```strPar::charPointerLen```:

This function returns the length of a ```char*```. Ends counting when either nullchar (```'\0'```), carriage return (```'\r'```) or newline (```'\n'```) occurs. **NOTE:** this function will cause issues if the ```char*``` is not properly terminated.

```c++
//Calculate the "length" of a char pointer 
//NOTE: There is no 100% way of knowing how long a char pointer is, use with caution
int charPointerLen(const char * str);
```

Example:

```c++
const char * str = "hello";
const char * str2 = "hello\r";

assert(strPar::charPointerLen(str) == 5);
assert(strPar::charPointerLen(str2) == 5); //Same length, because charPointerLen discards carriage return
```

There are already built in functions that can do the same thing such as ```strlen``` and ```std::char_traits::length```, but those only work for nullchar (```'\0'```) terminated ```char*```.

---
### ```strPar::copyCharPointer```:

Create a heap allocated copy of a ```char*```: 

```c++
char * copyCharPointer(const char * str);
```

Example:

```c++
const char * str = "hello";
char * str2 = strPar::copyCharPointer(str);
assert(!strcmp(str, str2)); //strcmp returns 0 if they are the same
delete[] str2; //the copy is heap allocated, need to delete[] to not leak memory
```

---

### ```strPar::appendCharToPointer```:

Has one function that creates a new larger ```char*``` which guarantees that the ```char``` will fit, and an unsafe version which assumes that you know that your ```char``` will fit in your current ```char*```. The unsafe version is faster as it doesn't have to allocate a bunch more memory on the heap and copy over all of the values.

```c++
char * appendCharToPointer(char * str, char newchar);
//NOTE: This function does not create a new char pointer and could potentially write out of bounds,
//use only if you know that your char pointer is long enough!
char * appendCharToPointerUnsafe(char * str, char newchar);
```

Examples:
```c++
//Safe version
char * str = new char[10];
str = strcpy(str,"hello"); // """safe""", should be using strncopy 
str = strPar::appendCharToPointer(str, 'a');
assert(!strcmp(str, "helloa"));
delete[] str;
char * str2 = new char[10];
str2 = strcpy(str2,"hello");
str2 = strPar::appendCharToPointerUnsafe(str2, 'a');
assert(!strcmp(str2, "helloa"));
delete[] str2;
```

---

### ```strPar::split```:

Function for splitting ```std::string``` and ```char*```, based on a ```char``` or ```char*``` delimiter. The ```char*``` versions return a custom data structure with heap allocated ```char**``` that needs to be deleted afterwards with the function ```strPar::deleteStringList``` afterwards, and the ```std::string``` version returns a ```std::vector<std::string>```

```c++
char ** split(const char * str, char c = ' '); //defaults to one whitespace 
char ** split(const char * str, const char * c);
//Deletes a char ** created from split method
void deleteStringList(char ** list);

std::vector<std::string> split(std::string str, char c = ' '); //defaults to one whitespace 
std::vector<std::string> split(std::string str, const char * c);
```

Examples:

```c++
const char * str = "hello1:hello2:hello3:";
char ** list = strPar::split(str, ':');
assert(!strcmp(list[0], "hello1") && !strcmp(list[1], "hello2") && !strcmp(list[2], "hello3") && !strcmp(list[3], "") && !strcmp(list[4], "\n\n"));
strPar::deleteStringList(list); //run in valgrind to make sure that this doesn't leak memory

const char * str2 = "hello1::hello2::hello3::";
char ** list2 = strPar::split(str2, "::");
assert(!strcmp(list2[0], "hello1") && !strcmp(list2[1], "hello2") && !strcmp(list2[2], "hello3") && !strcmp(list2[3], "") && !strcmp(list2[4], "\n\n"));
strPar::deleteStringList(list2); //run in valgrind to make sure that this doesn't leak memory

std::string str3 = std::string(str);
std::vector<std::string> list3 = strPar::split(str3, ':');
assert(list3[0] == std::string("hello1") && list3[1] == std::string("hello2") && list3[2] == std::string("hello3") && list3[3] == std::string(""));

std::string str4 = std::string(str2);
std::vector<std::string> list4 = strPar::split(str4, "::");
assert(list4[0] == std::string("hello1") && list4[1] == std::string("hello2") && list4[2] == std::string("hello3") && list4[3] == std::string(""));
```

---

### ```strPar::lstrip```, ```strPar::rstrip```, ```strPar::strip```:

Functions that strip either the left, right or both sides of a ```std::string``` and ```char*```. It defaults to removing trailing whitespaces (```' '```). These functions work for either removing a ```char``` or ```char*``` from the specified side of a ```std::string``` or ```char*```. Returns ```void``` arguments are passed-by-reference:
 
```c++
void lstrip(char * &str, char c = ' ');
void lstrip(std::string &str, char c = ' ');
void lstrip(char * &str, const char * c);
void lstrip(std::string &str, const char * c);

void rstrip(char * &str, char c = ' ');
void rstrip(std::string &str, char c = ' ');
void rstrip(char * &str, const char * c);
void rstrip(std::string &str, const char * c);

void strip(char * &str, char c = ' ');
void strip(std::string &str, char c = ' ');
void strip(char * &str, const char * c);
void strip(std::string &str, const char * c);
```

Examples:

```c++
//lstrip
//char ptr versions
char * str = strPar::copyCharPointer("aahello");
strPar::lstrip(str, 'a');
assert(!strcmp(str, "hello")); //strips both occurences of 'a'
delete[] str;
char * str2 = strPar::copyCharPointer("abahello");
strPar::lstrip(str2,"ab");
assert(!strcmp(str2, "ahello"));
delete[] str2;
//std::string versions
std::string str3 = std::string("aahello");
strPar::lstrip(str3, 'a');
assert(str3 == std::string("hello"));
std::string str4 = std::string("abahello");
strPar::lstrip(str4,"ab");
assert(str4 == std::string("ahello"));
//strip
//char ptr versions
char * str5 = strPar::copyCharPointer("aaahelloaa");
strPar::strip(str5, 'a');
assert(!strcmp(str5, "hello"));
delete[] str5;
```

Some overrides were left without examples, otherwise this code block would be very long.

---


### ```strPar::vectorFromFile```:

Different functions for creating different types of vectors:

```c++
//Call with a filename, returns a vector of strings
std::vector<std::string> vectorFromFile(const char * filename);
//Call with a filename, returns a vector of ints
std::vector<int> intVectorFromFile(const char * filename);
//Call with a filename and char delimiter, returns a vector of vectors of strings
std::vector<std::vector<std::string>> vectorFromFileDelimiter(const char * filename, char c = ' ');
//Call with a filename and string delimiter, returns a vector of vectors of strings
std::vector<std::vector<std::string>> vectorFromFileDelimiter(const char * filename, const char * str = " ");
```

Three example files have been provided with this repository:

 - ```input.txt``` - Contains the following: 
```
apple:1
banana:2
orange:3
lime:4
```
 - ```input2.txt``` - Same as the above, but with double the delimiter:
```
apple::1
banana::2
orange::3
lime::4
```
 - ```input3.txt``` - Contains some integer numbers, used with ```strPar::intVectorFromFile```:
```
1
3
5
4
10
13
```

Examples:

Create a ```std::vector<std::string>``` where each line in the file is converted to a ```std::string```:
```c++
std::vector<std::string> list = strPar::vectorFromFile("input.txt");
```
will yield the following vector:
```c++
{"apple:1", "banana:2", "orange:3", "lime:4"}
```

Create a ```std::vector<std::vector<std::string>>```, where every element in the outer ```std::vector``` is the function ```strPar::split``` executed for that line in the input file, with the specified delimiter:

```c++
std::vector<std::vector<std::string>> list2 = strPar::vectorFromFileDelimiter("input.txt", ':');
```
will yield the following vector:
```c++
{{"apple","1"}, {"banana", "2"}, {"orange", "3"}, {"lime, 4"}}
```

Same function as above, but instead of a ```char``` delimiter a ```char*```:

```c++
std::vector<std::vector<std::string>> list3 = strPar::vectorFromFileDelimiter("input2.txt", "::");
```

The vector will look the same as the one above.

If you want to compute the sum of all numbers in the file ```input3.txt```, you can do the following with ```strPar::intVectorFromFile```:

```c++
std::vector<int> list4 = strPar::intVectorFromFile("input3.txt");
int sum = 0;
for (int i = 0; i < list4.size(); i++) {
    sum += list4[i];
}
```

which should result in 36.

---

## Testing

The ```examples.cpp``` file contains enough to act as a unit test on its own. It tests all of the functions in the module. Here are two provided methods for building the file:

1. ```CMake```
2. Manually with ```g++```
---
### ```CMake```

Create a build folder from the base folder:
```
mkdir build
```
The test needs the input files in the same folder, copy them them into the build folder with:
```
cp input*.txt ./build
```
Move into the build folder:
```
cd build
```

Configure ```CMake``` with parent folder as source, and current folder as destination with:

```
cmake ..
```

Build the files and run the test:
```
make all
make test
```

---

### Manually with ```g++```

From the base folder, run:

```
g++ examples.cpp parsingLibrary.cpp -o examples
./examples
```

---

Also, verify that the program does not leak memory. Either you can run with:

```
valgrind ./examples
```

or compile and run with fsanitize:

```
g++ examples.cpp parsingLibrary.cpp -o examples -fsanitize=leak
./examples
```