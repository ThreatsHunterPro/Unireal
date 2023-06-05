CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT(Unireal)

#Settings
SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin)

#Librairies
link_directories(Engine/Libraries)

#Includes
include_directories(Engine/Includes)

#Subdirectories
add_subdirectory(${CMAKE_SOURCE_DIR}/Source)