# ===== 初期設定 =====
# CMake 最低バージョンを指定
cmake_minimum_required(VERSION 3.20)

# プロジェクト名と使用言語を指定
project(Procon36App CXX)

# C++ バージョン指定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# C++ 最適化フラグ
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native")

# ===== 外部ライブラリ設定 =====
# vcpkg でインストールしたパッケージの検索
find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# --- Google Benchmark 設定 ---
# 修正点: ベンチマーク自身のテストを無効化
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable internal benchmark tests")
add_subdirectory(vendor/benchmark)  # Google Benchmark をプロジェクトに組み込む
# -----------------------------

add_subdirectory(vendor/spdlog)

# ===== 実行ファイルの詳細設定 =====
# 実行ファイルの作成
add_executable(run src/main.cpp)

# インクルードディレクトリ追加
# imgui, nlohmann/json, spdlog
target_include_directories(run PRIVATE
    "/home/yamatcha_game_dev/dev/vcpkg/installed/x64-linux/include"
    #"${CMAKE_SOURCE_DIR}/vendor/json/single_include/"
)

# 実行可能ファイルに必要なライブラリをリンク
# vcpkg が生成したライブラリファイルへの絶対パスを直接指定
set(VCPKG_LIB_DIR "/home/yamatcha_game_dev/dev/vcpkg/installed/x64-linux/lib")

target_link_libraries(run PRIVATE
    "${VCPKG_LIB_DIR}/libimgui.a"  # ImGui 本体
    "${VCPKG_LIB_DIR}/libglfw3.a"  # GLFW 本体
    pthread GL dl X11              # Linux で必要なシステムライブラリ
    # spdlog
)

# ===== テストとベンチマーク設定 =====
# 実行可能なベンチマークターゲットを作成
add_executable(run_benchmark test/benchmark.cpp)

# ベンチマークターゲットに Benchmark ライブラリをリンク
target_link_libraries(run_benchmark PRIVATE benchmark spdlog)
