cmake_minimum_required(VERSION 3.0)  # Versión mínima requerida de CMake

project(AntSimulator VERSION 1.0.0 LANGUAGES CXX) # Nombre de tu proyecto

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Encuentra el paquete SFML
find_package(SFML REQUIRED COMPONENTS graphics window system)

# Agrega los archivos de código fuente de tu proyecto
add_executable(AntSimulator src/main.cpp)

# Enlaza tu proyecto con la biblioteca SFML
target_link_libraries(AntSimulator sfml-graphics sfml-window sfml-system)

