#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cassert>
#include "parsingLibrary.h"

void example_stringToCharPointer() { // Test constructors
    std::string str = std::string("hello");
    char * strout = strPar::stringToCharPointer(str);
    assert(!strcmp(strout, "hello"));

    std::string str2 = std::string("hello\r"); //this can occur when you read from a file 
    char * strout2 = strPar::stringToCharPointer(str2);
    assert(!strcmp("hello",strout2));

    std::string str3 = std::string("hello\n");
    char * strout3 = strPar::stringToCharPointer(str3);
    assert(!strcmp("hello",strout3));

    std::string str4 = std::string("");
    char * strout4 = strPar::stringToCharPointer(str4);
    assert(!strcmp(strout4,""));

    delete[] strout;
    delete[] strout2;
    delete[] strout3;
    delete[] strout4;
}

void example_charPointerLen() {
    const char * str = "hello";
    const char * str2 = "hello\r";
    assert(strPar::charPointerLen(str) == 5);
    assert(strPar::charPointerLen(str2) == 5);
    assert(strPar::charPointerLen("") == 0);
    assert(strPar::charPointerLen("\r") == 0);
}

void example_isIn() {
    std::string str = std::string("hello");
    const char * str2 = "hello";
    assert(strPar::isIn(str, 'a') == false);
    assert(strPar::isIn(str, 'o') == true);
    assert(strPar::isIn(str2, 'a') == false);
    assert(strPar::isIn(str2, 'l') == true);
    assert(strPar::isIn(str, "la") == false);
    assert(strPar::isIn(str, "lo") == true);
    assert(strPar::isIn(str2, "al") == false);
    assert(strPar::isIn(str2, "ell") == true);
}

void example_copyCharPointer() {
    const char * str = "hello";
    char * str2 = strPar::copyCharPointer(str);
    assert(!strcmp(str, str2));
    delete[] str2;
}

void example_appendCharToPointer() { 
    char * str = new char[10];
    str = strcpy(str,"hello");
    str = strPar::appendCharToPointer(str, 'a');
    assert(!strcmp(str, "helloa"));
    str = strPar::appendCharToPointer(str, '1');
    assert(!strcmp(str, "helloa1"));
    delete[] str;

    char * str2 = new char[10];
    //str2[0] = 'h'; str2[1] = 'e'; str2[2] = 'l'; str2[3] = 'l'; str2[4] = 'o'; str2[5] = '\0';
    str2 = strcpy(str2,"hello");
    str2 = strPar::appendCharToPointerUnsafe(str2, 'a');
    assert(!strcmp(str2, "helloa"));
    str2 = strPar::appendCharToPointerUnsafe(str2, '1');
    assert(!strcmp(str2, "helloa1"));
    delete[] str2;
    
    char * str3 = new char[10];
    str3[0] = '\0';
    str3 = strPar::appendCharToPointer(str3, 'a');
    assert(!strcmp(str3, "a"));
    delete[] str3;

    char * str4 = new char[10];
    str4[0] = '\0';
    str4 = strPar::appendCharToPointerUnsafe(str4, 'a');
    assert(!strcmp(str4, "a"));
    delete[] str4;
}

void example_split() {
    const char * str = "hello1:hello2:hello3:";
    char ** list = strPar::split(str, ':');
    assert(!strcmp(list[0], "hello1") && !strcmp(list[1], "hello2") && !strcmp(list[2], "hello3") && !strcmp(list[3], "") && !strcmp(list[4], "\n\n"));
    strPar::deleteStringList(list); //run test in valgrind to make sure that this doesn't leak memory

    const char * str2 = "hello1::hello2::hello3::";
    char ** list2 = strPar::split(str2, "::");
    assert(!strcmp(list2[0], "hello1") && !strcmp(list2[1], "hello2") && !strcmp(list2[2], "hello3") && !strcmp(list2[3], "") && !strcmp(list2[4], "\n\n"));
    strPar::deleteStringList(list2); //run test in valgrind to make sure that this doesn't leak memory

    std::string str3 = std::string(str);
    std::vector<std::string> list3 = strPar::split(str3, ':');
    assert(list3[0] == std::string("hello1") && list3[1] == std::string("hello2") && list3[2] == std::string("hello3") && list3[3] == std::string(""));

    std::string str4 = std::string(str2);
    std::vector<std::string> list4 = strPar::split(str4, "::");
    assert(list4[0] == std::string("hello1") && list4[1] == std::string("hello2") && list4[2] == std::string("hello3") && list4[3] == std::string(""));
}

void example_vectorFromFile() {
    std::vector<std::string> list = strPar::vectorFromFile("input.txt");
    assert(list[0] == std::string("apple:1") && list[1] == std::string("banana:2") && list[2] == std::string("orange:3") && list[3] == std::string("lime:4"));

    std::vector<int> list2 = strPar::intVectorFromFile("input3.txt");
    int sum = 0;
    for (int i = 0; i < list2.size(); i++) {
        sum += list2[i];
    }
    assert(sum == 36);
}

void example_vectorFromFileDelimiter() {
    std::vector<std::vector<std::string>> list = strPar::vectorFromFileDelimiter("input.txt", ':');
    assert(list[0][0] == std::string("apple") && list[0][1] == std::string("1") && list[1][0] == std::string("banana") && list[1][1] == std::string("2")
        && list[2][0] == std::string("orange") && list[2][1] == std::string("3") && list[3][0] == std::string("lime") && list[3][1] == std::string("4"));

    std::vector<std::vector<std::string>> list2 = strPar::vectorFromFileDelimiter("input2.txt", "::");
    assert(list[0][0] == std::string("apple") && list[0][1] == std::string("1") && list[1][0] == std::string("banana") && list[1][1] == std::string("2")
        && list[2][0] == std::string("orange") && list[2][1] == std::string("3") && list[3][0] == std::string("lime") && list[3][1] == std::string("4"));

}

void example_lstrip() {

    //char ptr versions
    char * str = strPar::copyCharPointer("aahello");
    strPar::lstrip(str, 'a');
    assert(!strcmp(str, "hello"));
    char * str2 = strPar::copyCharPointer("hello");
    strPar::lstrip(str2, 'a');
    assert(!strcmp(str2, "hello"));
    char * str3 = strPar::copyCharPointer(" hello");
    strPar::lstrip(str3);
    assert(!strcmp(str3, "hello"));
    char * str4 = strPar::copyCharPointer("abahello");
    strPar::lstrip(str4,'a');
    assert(!strcmp(str4, "bahello"));
    strPar::lstrip(str4,'b');
    assert(!strcmp(str4, "ahello"));
    strPar::lstrip(str4,'a');
    assert(!strcmp(str4, "hello"));
    delete[] str;
    delete[] str2;
    delete[] str3;
    delete[] str4;

    str = strPar::copyCharPointer("aahello");
    strPar::lstrip(str, "aa");
    assert(!strcmp(str, "hello"));
    str2 = strPar::copyCharPointer("hello");
    strPar::lstrip(str2, "aaaaaa");
    assert(!strcmp(str2, "hello"));
    str3 = strPar::copyCharPointer(" hello");
    strPar::lstrip(str3, "  ");
    assert(!strcmp(str3, " hello"));
    str4 = strPar::copyCharPointer("abahello");
    strPar::lstrip(str4,"ab");
    assert(!strcmp(str4, "ahello"));
    delete[] str;
    delete[] str2;
    delete[] str3;
    delete[] str4;

    //string versions

    std::string str5 = std::string("aahello");
    strPar::lstrip(str5, 'a');
    assert(str5 == std::string("hello"));
    std::string str6 = std::string("hello");
    strPar::lstrip(str6, 'a');
    assert(str6 == std::string("hello"));
    std::string str7 = std::string(" hello");
    strPar::lstrip(str7);
    assert(str7 == std::string("hello"));
    std::string str8 = std::string("abahello");
    strPar::lstrip(str8, 'a');
    assert(str8 == std::string("bahello"));
    strPar::lstrip(str8, 'b');
    assert(str8 == std::string("ahello"));
    strPar::lstrip(str8, 'a');
    assert(str8 == std::string("hello"));

    str5 = std::string("aahello");
    strPar::lstrip(str5, "aa");
    assert(str5 == std::string("hello"));
    str6 = std::string("hello");
    strPar::lstrip(str6, "aaaaaa");
    assert(str6 == std::string("hello"));
    str7 = std::string(" hello");
    strPar::lstrip(str7, "  ");
    assert(str7 == std::string(" hello"));
    str8 = std::string("abahello");
    strPar::lstrip(str8,"ab");
    assert(str8 == std::string("ahello"));
}

void example_rstrip() {
    //char ptr versions
    char * str = strPar::copyCharPointer("helloaa");
    strPar::rstrip(str, 'a');
    assert(!strcmp(str, "hello"));
    char * str2 = strPar::copyCharPointer("hello");
    strPar::rstrip(str2, 'a');
    assert(!strcmp(str2, "hello"));
    char * str3 = strPar::copyCharPointer("hello ");
    strPar::rstrip(str3);
    assert(!strcmp(str3, "hello"));
    char * str4 = strPar::copyCharPointer("helloaba");
    strPar::rstrip(str4,'a');
    assert(!strcmp(str4, "helloab"));
    strPar::rstrip(str4,'b');
    assert(!strcmp(str4, "helloa"));
    strPar::rstrip(str4,'a');
    assert(!strcmp(str4, "hello"));
    delete[] str;
    delete[] str2;
    delete[] str3;
    delete[] str4;

    str = strPar::copyCharPointer("helloabab");
    strPar::rstrip(str, "ab");
    assert(!strcmp(str, "hello"));
    str2 = strPar::copyCharPointer("hello");
    strPar::rstrip(str2, "aaaaaa");
    assert(!strcmp(str2, "hello"));
    str3 = strPar::copyCharPointer("hello ");
    strPar::rstrip(str3, "  ");
    assert(!strcmp(str3, "hello "));
    str4 = strPar::copyCharPointer("helloaba");
    strPar::rstrip(str4,"ba");
    assert(!strcmp(str4, "helloa"));
    delete[] str;
    delete[] str2;
    delete[] str3;
    delete[] str4;

    //string versions

    std::string str5 = std::string("helloaa");
    strPar::rstrip(str5, 'a');
    assert(str5 == std::string("hello"));
    std::string str6 = std::string("hello");
    strPar::rstrip(str6, 'a');
    assert(str6 == std::string("hello"));
    std::string str7 = std::string("hello ");
    strPar::rstrip(str7);
    assert(str7 == std::string("hello"));
    std::string str8 = std::string("helloaba");
    strPar::rstrip(str8, 'a');
    assert(str8 == std::string("helloab"));
    strPar::rstrip(str8, 'b');
    assert(str8 == std::string("helloa"));
    strPar::rstrip(str8, 'a');
    assert(str8 == std::string("hello"));

    str5 = std::string("helloaa");
    strPar::rstrip(str5, "aa");
    assert(str5 == std::string("hello"));
    str6 = std::string("hello");
    strPar::rstrip(str6, "aaaaaa");
    assert(str6 == std::string("hello"));
    str7 = std::string(" hello");
    strPar::rstrip(str7, "  ");
    assert(str7 == std::string(" hello"));
    str8 = std::string("helloaba");
    strPar::rstrip(str8,"ba");
    assert(str8 == std::string("helloa"));
}

void example_strip() {
    //char ptr versions
    char * str = strPar::copyCharPointer("aaahelloaa");
    strPar::strip(str, 'a');
    assert(!strcmp(str, "hello"));
    char * str2 = strPar::copyCharPointer("hello");
    strPar::strip(str2, 'a');
    assert(!strcmp(str2, "hello"));
    char * str3 = strPar::copyCharPointer("   hello ");
    strPar::strip(str3);
    assert(!strcmp(str3, "hello"));
    char * str4 = strPar::copyCharPointer("abahelloaba");
    strPar::strip(str4,'a');
    assert(!strcmp(str4, "bahelloab"));
    strPar::strip(str4,'b');
    assert(!strcmp(str4, "ahelloa"));
    strPar::strip(str4,'a');
    assert(!strcmp(str4, "hello"));
    delete[] str;
    delete[] str2;
    delete[] str3;
    delete[] str4;

    str = strPar::copyCharPointer("ababhelloabab");
    strPar::strip(str, "ab");
    assert(!strcmp(str, "hello"));
    str2 = strPar::copyCharPointer("hello");
    strPar::strip(str2, "aaaaaa");
    assert(!strcmp(str2, "hello"));
    str3 = strPar::copyCharPointer("hello ");
    strPar::strip(str3, "  ");
    assert(!strcmp(str3, "hello "));
    str4 = strPar::copyCharPointer("baahelloaba");
    strPar::strip(str4,"ba");
    assert(!strcmp(str4, "ahelloa"));
    delete[] str;
    delete[] str2;
    delete[] str3;
    delete[] str4;

    //string versions

    std::string str5 = std::string("aaahelloaa");
    strPar::strip(str5, 'a');
    assert(str5 == std::string("hello"));
    std::string str6 = std::string("hello");
    strPar::strip(str6, 'a');
    assert(str6 == std::string("hello"));
    std::string str7 = std::string("   hello ");
    strPar::strip(str7);
    assert(str7 == std::string("hello"));
    std::string str8 = std::string("abahelloaba");
    strPar::strip(str8, 'a');
    assert(str8 == std::string("bahelloab"));
    strPar::strip(str8, 'b');
    assert(str8 == std::string("ahelloa"));
    strPar::strip(str8, 'a');
    assert(str8 == std::string("hello"));

    str5 = std::string("abhelloab");
    strPar::strip(str5, "ab");
    assert(str5 == std::string("hello"));
    str6 = std::string("hello");
    strPar::strip(str6, "aaaaaa");
    assert(str6 == std::string("hello"));
    str7 = std::string(" hello");
    strPar::strip(str7, "  ");
    assert(str7 == std::string(" hello"));
    str8 = std::string("baahelloaba");
    strPar::strip(str8,"ba");
    assert(str8 == std::string("ahelloa"));
}

//Runs all example code blocks with to verify the correctness of this module
void run_tests() {

    std::cout << "Running tests:" << std::endl;

    std::cout << "Testing 'stringToCharPointer()'... ";
    example_stringToCharPointer();
    std::cout << "done" << std::endl;

    std::cout << "Testing 'charPointerLen()'... ";
    example_charPointerLen();
    std::cout << "done" << std::endl;

    std::cout << "Testing 'isIn()'... ";
    example_isIn();
    std::cout << "done" << std::endl;

    std::cout << "Testing 'copyCharPointer()'... ";
    example_copyCharPointer();
    std::cout << "done" << std::endl;

    std::cout << "Testing 'appendCharToPointer()'... ";
    example_appendCharToPointer();
    std::cout << "done" << std::endl;

    std::cout << "Testing 'split()'... ";
    example_split();
    std::cout << "done" << std::endl;

    std::cout << "Testing 'vectorFromFile()'... ";
    example_vectorFromFile();
    std::cout << "done" << std::endl;

    std::cout << "Testing 'vectorFromFileDelimiter()'... ";
    example_vectorFromFileDelimiter();
    std::cout << "done" << std::endl;

    std::cout << "Testing 'lstrip()'... ";
    example_lstrip();
    std::cout << "done" << std::endl;
    
    std::cout << "Testing 'rstrip()'... ";
    example_rstrip();
    std::cout << "done" << std::endl;
    
    std::cout << "Testing 'strip()'... ";
    example_strip();
    std::cout << "done" << std::endl;

    std::cout << "All tests successfull!" << std::endl;

    return;
}

int main() {
    run_tests();
    return 0;
}