# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.22)

# Set Project Name
project (cath)

# Cerate a SOURCES variable with a link to all cpp files to compile
set (SOURCES
    src/main.c
    src/Vector.c    
)

# Add executable with above sources
add_executable(${PROJECT_NAME} ${SOURCES})  

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include    
)