#include <stdio.h>
#include <stdexcept>
#include <GLFW/glfw3.h>

#include "imgui.h"              // ImGui のコア機能
#include "imgui_impl_glfw.h"    // ImGuiとGLFW（ウィンドウ）の連携コード
#include "imgui_impl_opengl3.h" // ImGuiとOpenGL（描画API）の連携コード

// エラーコールバック関数 (省略可能)
static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**)
{
    // 1. GLFWの初期化
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) { return 1; }

    // 2. OpenGLとGLFWのバージョン指定
    // OpenGL 3.3 Core Profileを使用
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 3. ウィンドウの作成
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 Example", NULL, NULL);
    if (window == NULL) { return 1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // VSyncを無効（ラグ軽減）

    // 4. ImGuiコンテキストの初期化
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // 5. ImGuiスタイルとフォントの設定
    ImGui::StyleColorsDark();

    // 6. ImGuiのバックエンド設定（GLFWとOpenGL3の連携）
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // デモウィンドウの表示フラグ
    bool show_demo_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // 7. メインループ
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); // OSからのキー入力やマウスイベントを処理

        // ImGuiフレームの開始
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame(); // ImGuiの描画開始宣言

        // === 8. ImGui GUIのロジックをここに記述 ===

        // (A) デモウィンドウの表示
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // (B) 独自のウィンドウの作成
        {
            // ウィンドウの初期設定
            ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_Always);
            static float f = 0.0f;
            ImGui::Begin("Hello, ImGui!", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize); // ウィンドウの開始
            ImGui::Text("This is my first ImGui window!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // スライダー
            if (ImGui::Button("Button")) // ボタン
            {
                // ボタンが押されたときの処理
            }
            ImGui::End(); // ウィンドウの終了
        }

        // 9. レンダリング
        ImGui::Render(); // 描画ロジックを内部データに変換
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        // 背景のクリア
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // ImGuiの描画データでレンダリング
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window); // 実際に画面に描画
    }

    // 10. クリーンアップ
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
