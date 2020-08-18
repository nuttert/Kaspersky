cmake_minimum_required(VERSION 3.0.0)
project(TEST_PROJECT VERSION 0.0.1)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_FOLDER build)

if(${TEST_MODE})
    file(GLOB SOURCES "Tests/main.cpp")
else()
    file(GLOB SOURCES "main.cpp")
endif()

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20) 

find_package(Threads REQUIRED)

add_subdirectory(Interrupter)
add_subdirectory(Reader)
add_subdirectory(Reverser)
add_subdirectory(Runner)
add_subdirectory(TokenProcessor)
add_subdirectory(Writer)
add_subdirectory(Models)
add_subdirectory(Utilities)


if(${TEST_MODE})
    find_package(GTest REQUIRED)
    if (GTest_FOUND)
        target_include_directories(${PROJECT_NAME} PUBLIC ${GTEST_INCLUDE_DIRS})
        target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} gmock)
    endif()
endif()

cmake_policy(SET CMP0063 NEW)


target_link_libraries(${PROJECT_NAME} 
    stdc++fs
    Threads::Threads 
    Runner 
    TokenProcessor 
    Interrupter 
    Reader 
    Reverser 
    Writer 
    Models 
    Utilities
    )
