cmake_minimum_required(VERSION 3.10)
project(KartingCenter)

set(CMAKE_CXX_STANDARD 17)

# Найдите библиотеку PostgreSQL
find_package(PostgreSQL REQUIRED)

# Найдите библиотеку SFML
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(KartingCenter src/KartingCenterGUI.cpp src/DatabaseManager.cpp)

target_link_libraries(KartingCenter ${POSTGRESQL_LIBRARIES} sfml-graphics)
target_include_directories(KartingCenter PRIVATE ${POSTGRESQL_INCLUDE_DIRS} ${SFML_INCLUDE_DIR})