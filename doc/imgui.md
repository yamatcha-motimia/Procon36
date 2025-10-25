# ImGui環境構築 総まとめドキュメント（WSL + VS Code）
## 1. 専門用語の注釈

| 用語 | 読み方 | 意味と役割 |
|------|-------|-----------|
| GUI          | ジーユーアイ | Graphical User Interface。視覚的な操作画面（ボタンやウィンドウなど） |
| ImGui        | イムグイ     | Immediate Mode GUI。C++で高速なデバッグ用UIを簡単に作れるライブラリ  |
| GLFW         | ジーエルエフダブリュー | グラフィックスAPIのためのウィンドウと入力管理ライブラリ      |
| OpenGL       | オープンジーエル | Graphics Library。2D/3Dグラフィックス描画用のAPI                |
| レンダリング  | レンダリング | データを画面上のピクセルに変換して描画する処理                        |
| Vsync        | ブイシンク   | 垂直同期。FPSをモニターのリフレッシュレートに合わせる機能             |
| コンテキスト  | コンテキスト | 実行に必要な状態やデータをまとめたメモリ領域。ImGuiの基礎となる        |
| バックエンド  | バックエンド | UIデータをグラフィックスAPIやウィンドウライブラリに橋渡しする役割      |
| リンカー      | リンカー    | コンパイル済みコードとライブラリを結合して実行ファイルを生成するプログラム |

## 2. 全体のコード (main.cpp)
```cpp
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
// <GLFW/glfw3.h>の前に、必ず他のImGuiのヘッダーを記述する。

// ... glfw_error_callback関数（省略）

int main(int, char**)
{
    // === 初期化フェーズ ===
    glfwSetErrorCallback(/* ... */);
    if (!glfwInit()) return 1;

    // OpenGLバージョン3.3（Core Profile）の指定
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ウィンドウの作成
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ウィンドウタイトル", NULL, NULL);
    if (window == NULL) return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // VSyncを無効化 (WSLgでのラグ対策)

    // ImGuiコンテキストの作成
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark(); // UIのテーマ設定（ダークモード）

    // ImGuiバックエンドの初期化 (GLFWとOpenGLとの連携設定)
    ImGui_ImplGlfw_InitForOpenGL(window, true); // ウィンドウ(GLFW)との連携
    ImGui_ImplOpenGL3_Init(glsl_version);       // 描画API(OpenGL)との連携

    // デモウィンドウ表示フラグ、背景色などの設定
    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // === メインループフェーズ ===
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); // マウスやキーボードの入力を受け取る

        // 1. ImGuiのフレーム開始
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame(); // これ以降、UIロジックを記述する

        // 2. 【★★カスタマイズ部分★★】UIロジックの定義
        // ... ここにImGuiの関数（ImGui::Begin, ImGui::Buttonなど）を記述 ...
        if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

        // 3. ImGuiのレンダリング
        ImGui::Render(); // UI定義（ロジック）を画面描画データに変換

        // 4. 背景の描画と画面クリア
        glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT); // 画面を背景色で塗りつぶす

        // 5. 変換されたImGuiデータを描画
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window); // 描画結果を画面に反映
    }

    // === 終了処理フェーズ ===
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
```

## 3. コードの全体的な流れの説明

全体のコードは、**「初期化」** → **「メインループ（毎フレーム実行）」** → **「終了処理」**の3部構成です。

### 1. 初期化フェーズ (プログラム起動時)

GLFWを使ってウィンドウとOpenGLの描画コンテキストを準備します。
ImGui::CreateContext()で、ImGuiの土台を作ります。
ImGui_Impl...Init()の2行で、ImGuiとGLFW/OpenGLという別々のライブラリが連携できるように設定します。

### 2. メインループフェーズ (毎秒60回など、繰り返し実行)

このループが、ウェブサイトのコードで**レンダリング（描画）**と呼ばれている部分です。

    - ImGui::NewFrame(): 「今から新しいフレームを描画するよ」という開始宣言。この後に書かれたUIコードが「即時モード」で実行されます。

    - UIロジックの定義: ImGui::Begin(), ImGui::Button() などを呼び出し、画面に表示したいUIを定義します。

    - ImGui::Render(): 定義されたUIロジックを、OpenGLが理解できる描画命令のリスト（Draw Data）に変換します。

    - 画面のクリア: glClear()で前フレームの残像を消します。

    - 描画実行: ImGui_ImplOpenGL3_RenderDrawData()で、ImGuiの描画命令リストをOpenGLに実行させ、UIを画面にレンダリングします。

    - 画面反映: glfwSwapBuffers()で、描画結果をモニターに表示します。

### 3. 終了処理フェーズ (ウィンドウを閉じた時)

ImGui::DestroyContext()やglfwTerminate()などで、確保したリソースをすべて解放し、プログラムをクリーンに終了します。

## 4. コピペで使い回しても良い定型文
### 1. インクルードヘッダー：
```CPP
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
// ... その他必要なヘッダー
```

### 2. ImGuiコンテキストの初期化～バックエンド連携：
```cpp
// ほぼこのままコピペでOK
ImGui::CreateContext();
ImGui::StyleColorsDark();
ImGui_ImplGlfw_InitForOpenGL(window, true);
ImGui_ImplOpenGL3_Init(glsl_version);
```

### 3. メインループのフレーム開始と終了処理：
```cpp
// ループのどこかで必ずNewFrame/Renderのセットが必要
ImGui_ImplOpenGL3_NewFrame(); ImGui_ImplGlfw_NewFrame(); ImGui::NewFrame();

// ... UIロジック ...

ImGui::Render();
// ... OpenGLのクリア処理 ...
ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
```

## 5. カスタマイズする部分の関数一覧と使い方
カスタマイズの中心となるのは、メインループ内の UIロジックの定義部分です。

| 関数/構文 | 使い方と意味 | 専門用語 |
|-----------|--------------|----------|
| ImGui::Begin("タイトル", &bool) | 新しいウィンドウの定義を開始。「タイトル」がウィンドウ名。&boolはウィンドウの「×」ボタンの状態を保存する変数（NULLにすると「×」ボタンが無効になる）。 | ウィンドウ |
| ImGui::End() | ウィンドウの定義を終了。ImGui::Begin()と必ずペアで使用する。 | ウィンドウ |
| ImGui::Text("文字列") | 単なる静的なテキストを表示。 | |
| ImGui::Button("ボタン名") | ボタンを表示。**戻り値がtrue**のとき、ボタンがクリックされている。 | ウィジェット |
| ImGui::SliderFloat("名前", &float, min, max) | 浮動小数点数（float）の値をスライドで変更するUIを表示。変更された値は&floatに即座に書き込まれる。 | ウィジェット |
| ImGui::Checkbox("名前", &bool) | チェックボックスを表示。チェックの状態は&boolに反映される。 | ウィジェット |
| ImGui::ShowDemoWindow(&bool) | 全ImGuiウィジェットのデモを表示する大きなウィンドウ。ImGuiの機能を試すのに最適。 | |
