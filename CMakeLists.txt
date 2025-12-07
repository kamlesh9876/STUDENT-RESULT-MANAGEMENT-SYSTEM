cmake_minimum_required(VERSION 3.10)
project(StudentMarksManagementSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SQLite3 package
find_package(SQLite3 REQUIRED)

# Add executable
add_executable(srms
    main.cpp
    StudentDatabase.cpp
)

# Link SQLite3 library
target_link_libraries(srms PRIVATE SQLite::SQLite3)

# Add include directories
target_include_directories(srms PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Compiler-specific options
if(MSVC)
    target_compile_options(srms PRIVATE /W4)
else()
    target_compile_options(srms PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Copy database.sql to build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/database.sql 
               ${CMAKE_CURRENT_BINARY_DIR}/database.sql COPYONLY)

# Set output directory
set_target_properties(srms PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Create bin directory if it doesn't exist
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Custom target to run the application
add_custom_target(run
    COMMAND srms
    DEPENDS srms
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    COMMENT "Running Student Marks Management System"
)
