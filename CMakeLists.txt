cmake_minimum_required(VERSION 3.18)

# Point CMake at the MinGW compiler from CodeBlocks.
# Must be set BEFORE the project() call.
set(CMAKE_CXX_COMPILER "C:/Program Files/CodeBlocks/MinGW/bin/g++.exe")
set(CMAKE_C_COMPILER   "C:/Program Files/CodeBlocks/MinGW/bin/gcc.exe")

project(DND_PROJECT CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# All game logic sources — excludes main so tests can link to the same library
set(LIB_SOURCES
    src/P_Character.cpp
    src/P_CharacterManager.cpp
    src/P_Inventory.cpp
    src/P_Item.cpp
    src/P_Weapon.cpp
    src/P_Armor.cpp
    src/P_Gear.cpp
    src/P_spells.cpp
    src/P_SpellBook.cpp
    src/P_SpellSlots.cpp
    src/P_Wallet.cpp
    src/P_Colours.cpp
)

# Static library that both the game exe and the test exe link against
add_library(dnd_lib STATIC ${LIB_SOURCES})
target_include_directories(dnd_lib PUBLIC include)

# Main game executable
add_executable(DND_PROJECT src/P_main.cpp)
target_link_libraries(DND_PROJECT PRIVATE dnd_lib)

# Required for CTest to discover and register tests
enable_testing()

# Test suite
add_subdirectory(tests)
