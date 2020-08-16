cmake_minimum_required(VERSION 3.0.0)
project(TEST_PROJECT VERSION 0.0.1)

#год плюсов
set(CMAKE_CXX_STANDART 20)
set(CMAKE_STANDART_REQUIRED ON)


#Ищем файлы
file(GLOB SOURCES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(Threads REQUIRED)

add_subdirectory(Interrupter)
add_subdirectory(Reader)
add_subdirectory(Reverser)
add_subdirectory(Runner)
add_subdirectory(TokenProcessor)
add_subdirectory(Writer)
add_subdirectory(Models)
add_subdirectory(Utilities)

target_link_libraries(${PROJECT_NAME} 
    Threads::Threads 
    Runner 
    TokenProcessor 
    Interrupter 
    Reader 
    Reverser 
    Writer 
    Models 
    Utilities)


