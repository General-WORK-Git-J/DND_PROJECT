include(FetchContent)

# Download GoogleTest at configure time — no manual installation needed
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
# Prevent GoogleTest from overriding our compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test executable — add new test files here as you create them
add_executable(dnd_tests
    test_wallet.cpp
    test_character.cpp
    test_spellslots.cpp
    test_inventory.cpp
)

target_link_libraries(dnd_tests
    PRIVATE
    dnd_lib
    GTest::gtest_main
)

# Statically link MinGW runtime so the exe runs without DLLs on the PATH
target_link_options(dnd_tests PRIVATE -static)

# PRE_TEST defers discovery until test-run time — more reliable on MinGW/Windows
# (avoids running the binary during cmake configure, which can fail due to missing DLLs)
include(GoogleTest)
gtest_discover_tests(dnd_tests DISCOVERY_MODE PRE_TEST)
