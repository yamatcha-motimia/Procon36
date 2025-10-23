# CMakeの最低バージョンを指定
cmake_minimum_required(VERSION 3.20)

# プロジェクト名と使用言語を指定
project(Procon36App CXX)

# C++のバージョン指定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# C++用の最適化フラグ
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native")

# vcpkgでインストールしたパッケージの検索
find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(run src/main.cpp)

# 実行可能ファイルに必要なライブラリをリンク
target_link_libraries(run PRIVATE
    imgui::imgui
    imgui::glfw-binding
    imgui::opengl3-binding
    glfw3
)
