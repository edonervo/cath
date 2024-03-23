# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.22)

# Set Project Name
project (cath)

# Cerate a SOURCES variable with a link to all cpp files to compile
set (SOURCES
    src/Vector.c    
    src/Matrix.c
    src/LinSys.c
    src/unity.c
    src/utils.c
    src/FiniteDiffGrid.c
    tests/testVector.c
    tests/testMatrix.c
    tests/testLynSys.c
    tests/testGrid.c
    tests/main.c
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
