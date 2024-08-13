cmake_minimum_required(VERSION 3.0)

project(AntSimulator VERSION 1.0.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML pakage
find_package(SFML REQUIRED COMPONENTS graphics window system)

# Add source code
add_executable(AntSimulator src/main.cpp)

# Relative path to the font
set(FONT_FILE ${CMAKE_SOURCE_DIR}/fonts/arial.ttf)

# Copy the font to the final directory
add_custom_command(TARGET AntSimulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${FONT_FILE} $<TARGET_FILE_DIR:AntSimulator>)

# Link SFML
target_link_libraries(AntSimulator sfml-graphics sfml-window sfml-system)

