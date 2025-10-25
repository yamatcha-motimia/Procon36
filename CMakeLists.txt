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

# ライブラリ名に対応するターゲット名を指定
target_include_directories(run PRIVATE
    "/home/yamatcha_game_dev/dev/vcpkg/installed/x64-linux/include"
)

# 実行可能ファイルに必要なライブラリをリンク
# vcpkgが生成したライブラリファイルへの絶対パスを直接指定
set(VCPKG_LIB_DIR "/home/yamatcha_game_dev/dev/vcpkg/installed/x64-linux/lib")

target_link_libraries(run PRIVATE
    "${VCPKG_LIB_DIR}/libimgui.a"  # ImGui本体
    "${VCPKG_LIB_DIR}/libglfw3.a"  # GLFW本体
    pthread GL dl X11              # Linuxで必要なシステムライブラリ
)
