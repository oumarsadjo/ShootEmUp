cmake_minimum_required(VERSION 3.25.1)
project(ShootEm)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

# Add your source files
add_executable(ShootEm 
    Main.cpp
    Game.hpp
    Game.cpp
    Player.hpp
    Player.cpp
    Global.hpp
    Enemy.cpp 
    Enemy.hpp
)

# Link SFML libraries to your executable
target_link_libraries(ShootEm PRIVATE 
    sfml-system 
    sfml-window 
    sfml-graphics 
    sfml-audio
)

# If you need the static version, uncomment the following line
# set_target_properties(ShootEm PROPERTIES
#     COMPILE_DEFINITIONS "SFML_STATIC"
# )

