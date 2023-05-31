cmake_minimum_required(VERSION 3.12)
project(examples)          #Feel free to steal this CMakeLists.txt, change this line to the name of your main file,
set(CMAKE_CXX_STANDARD 11) #if you want to reuse it

add_library(parsingLibrary parsingLibrary.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} parsingLibrary)

#These features use the "examples" output file as a test, 
#remove these lines if you are reusing this CMakeLists.txt for another project
enable_testing()
add_test(NAME ${CMAKE_PROJECT_NAME} COMMAND ./${CMAKE_PROJECT_NAME})
