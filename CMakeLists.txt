cmake_minimum_required(VERSION 3.22)
project(EDA-Trabalho1 VERSION 0.5)

#config
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SOURCES main.cc)
add_executable(${PROJECT_NAME} ${SOURCES})