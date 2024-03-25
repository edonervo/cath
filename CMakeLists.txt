# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.22)

# Set Project Name
project (cath)

# Use file(GLOB ...) to get a list of all .c files in src/ and tests/
file(GLOB SOURCES
    src/*.c
    tests/*.c
)

# Add executable with above sources
add_executable(${PROJECT_NAME} ${SOURCES})  

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include    
)

target_link_libraries(${PROJECT_NAME} m)

# Add compiler flags to enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wconversion)
