cmake_minimum_required(VERSION 3.0)  # Versión mínima requerida de CMake

project(SFML_test)  # Nombre de tu proyecto

# Agrega el directorio donde se encuentra el archivo SFMLConfig.cmake
set(SFML_DIR "/lib/x86_64-linux-gnu/cmake/SFML")

# Encuentra el paquete SFML
find_package(SFML REQUIRED COMPONENTS graphics window system)

# Agrega los archivos de código fuente de tu proyecto
add_executable(mi_ejecutable main.cpp)

# Enlaza tu proyecto con la biblioteca SFML
target_link_libraries(mi_ejecutable sfml-graphics sfml-window sfml-system)

