##########
find_package(GTest REQUIRED)
if (GTest_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES})
endif()
##########

