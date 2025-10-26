add_library(solver_lib
    STATIC
    ${PROJECT_SOURCE_DIR}/src/util/timer.cpp
)

target_include_directories(solver_lib
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
