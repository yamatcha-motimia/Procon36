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
    # vcpkgが提供するGLFWのパス（多くの場合、ヘッダーは"GLFW"というサブフォルダにあります）
    glfw3
    # ImGui本体のヘッダーパス
    imgui::imgui
    # ImGuiのバインディング（実装）ファイルのヘッダーパス
    # vcpkgのImGuiポートは、多くの場合、このヘッダーパスもimgui::imguiターゲットに含めるが、
    # 含まれていない場合は明示的に追加が必要。
    # ここでは、imgui::glfw-bindingのターゲット名に対応するINCLUDE_DIRSを要求します
    $<TARGET_PROPERTY:imgui::glfw-binding,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:imgui::opengl3-binding,INTERFACE_INCLUDE_DIRECTORIES>
)

# 実行可能ファイルに必要なライブラリをリンク
target_link_libraries(run PRIVATE
    imgui                 # ImGui本体
    imgui-glfw            # GLFWバインディング
    imgui-opengl3         # OpenGL3バインディング (GLAD込み)
    glfw3                 # GLFW本体
)
