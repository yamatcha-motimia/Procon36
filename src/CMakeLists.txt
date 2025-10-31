# === Solver ===
add_library(SolverLib STATIC
    ${PROJECT_SOURCE_DIR}/src/util/timer.cpp
)

target_include_directories(SolverLib PUBLIC
    ${PROJECT_SOURCE_DIR}/include/
)

# === GUI ===
#add_library(GUILib STATIC
    #${PROJECT_SOURCE_DIR}/src/gui/gui.cpp
#)

#target_include_directories(GUILib PUBLIC
    #"/home/yamatcha_game_dev/dev/vcpkg/installed/x64-linux/include"
    #${CMAKE_CURRENT_SOURCE_DIR}/include/
#)
