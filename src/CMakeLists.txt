add_subdirectory(date)

set(SOURCE  
        main.cpp)
        
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_directories(${PROJECT_NAME} PRIVATE date)
target_link_libraries(${PROJECT_NAME} date)
