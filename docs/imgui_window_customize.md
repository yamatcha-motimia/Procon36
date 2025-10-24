# Dear ImGui ウィンドウカスタマイズ完全ガイド

このドキュメントでは、**Dear ImGui** のウィンドウ操作・カスタマイズに関する主要な関数と機能を整理・解説します。
ImGuiはC++でリアルタイムUIを簡単に構築できるライブラリであり、ゲームエディタやツール開発でよく使用されます。

---

## 1. ウィンドウの基本構造

ImGuiでは、`ImGui::Begin()` と `ImGui::End()` のペアでウィンドウを定義します。

```cpp
ImGui::Begin("My Window");
ImGui::Text("Hello, ImGui!");
ImGui::End();
```

### ポイント
- `Begin()` と `End()` のペアは常に対応している必要があります。
- `Begin()` の戻り値が `false` の場合は、そのウィンドウが折りたたまれており、ウィジェットの描画をスキップするのが推奨です。

---

## 2. ウィンドウフラグ (`ImGuiWindowFlags_`)

`ImGui::Begin()` に第2引数・第3引数として渡すことで、ウィンドウの挙動を制御できます。

```cpp
ImGui::Begin("Custom Window", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
```

### 代表的なウィンドウフラグ一覧

| フラグ名 | 効果 |
|-----------|-------|
| `ImGuiWindowFlags_NoTitleBar` | タイトルバーを非表示にする |
| `ImGuiWindowFlags_NoResize` | サイズ変更を無効にする |
| `ImGuiWindowFlags_NoMove` | ウィンドウの移動を禁止する |
| `ImGuiWindowFlags_NoScrollbar` | スクロールバーを非表示にする |
| `ImGuiWindowFlags_NoScrollWithMouse` | マウスホイールによるスクロールを無効にする |
| `ImGuiWindowFlags_NoCollapse` | 折りたたみ（三角アイコン）を無効にする |
| `ImGuiWindowFlags_AlwaysAutoResize` | コンテンツに合わせて自動的にサイズを調整する |
| `ImGuiWindowFlags_NoBackground` | 背景を描画しない |
| `ImGuiWindowFlags_NoBringToFrontOnFocus` | フォーカス時に前面へ移動しない |
| `ImGuiWindowFlags_MenuBar` | メニューバーを有効にする |

---

## 3. ウィンドウの位置・サイズ制御

ImGuiではウィンドウの位置やサイズを直接指定できます。これらは **`ImGui::Begin()` を呼び出す前** に設定します。

```cpp
ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_Always);
ImGui::Begin("Fixed Window", nullptr, ImGuiWindowFlags_NoResize);
ImGui::Text("位置とサイズが固定されています");
ImGui::End();
```

### 条件フラグ (`ImGuiCond_`)
| フラグ | 意味 |
|--------|------|
| `ImGuiCond_Always` | 毎フレーム強制的に設定を適用 |
| `ImGuiCond_Once` | 一度だけ適用 |
| `ImGuiCond_FirstUseEver` | 初回描画時にのみ適用 |

---

## 4. スタイルと見た目のカスタマイズ

ImGuiの外観は `ImGuiStyle` 構造体を通して制御可能です。

```cpp
ImGuiStyle& style = ImGui::GetStyle();
style.WindowRounding = 10.0f; // 角を丸く
style.FrameRounding = 5.0f;
style.WindowPadding = ImVec2(10, 10);
```

### テーマの変更例

```cpp
ImGui::StyleColorsDark();
ImGui::StyleColorsClassic();
ImGui::StyleColorsLight();
```

---

## 5. 子ウィンドウとグループ化

子ウィンドウを使うと、親ウィンドウ内にスクロール可能な領域や独立したレイアウト領域を作成できます。

```cpp
ImGui::Begin("Parent Window");
ImGui::BeginChild("Child1", ImVec2(200, 100), true);
ImGui::Text("子ウィンドウ1の内容");
ImGui::EndChild();

ImGui::SameLine();
ImGui::BeginChild("Child2", ImVec2(200, 100), true);
ImGui::Text("子ウィンドウ2の内容");
ImGui::EndChild();
ImGui::End();
```

---

## 6. ウィンドウ制御API（動的操作）

```cpp
ImGui::SetWindowFocus("My Window");
ImGui::SetWindowCollapsed("Debug", true);
ImGui::SetWindowPos("My Window", ImVec2(50, 50));
ImGui::SetWindowSize("My Window", ImVec2(300, 200));
```

- `ImGui::IsWindowFocused()`：現在のウィンドウがフォーカスを持っているか判定
- `ImGui::IsWindowHovered()`：ウィンドウがマウスの下にあるか判定
- `ImGui::GetWindowPos()` / `ImGui::GetWindowSize()`：位置・サイズを取得

---

## 7. その他便利な機能

### 7.1. ツールチップ（ヒント）

```cpp
ImGui::Button("設定");
if (ImGui::IsItemHovered()) {
    ImGui::SetTooltip("アプリケーションの設定を開きます。");
}
```

**関数一覧**

| 関数 | 説明 |
|------|------|
| `bool ImGui::IsItemHovered()` | 直前のウィジェットにマウスカーソルがホバーしている場合にtrue |
| `void ImGui::SetTooltip(const char* fmt, ...)` | ホバー時に表示されるツールチップを設定 |

---

### 7.2. 入力情報と時間

| 関数 | 説明 |
|------|------|
| `ImGui::GetIO().Framerate` | 現在のフレームレート（FPS） |
| `ImGui::GetIO().DeltaTime` | 前のフレームからの経過時間（秒） |
| `ImGui::IsKeyPressed(ImGuiKey key)` | 指定したキーが押されたフレームでtrue |

---

### 7.3. ロギングとキャプチャ

ImGuiの描画内容をテキストとしてキャプチャできます。デバッグ情報やUI状態をログ出力可能です。

```cpp
if (ImGui::Button("ログに出力")) {
    ImGui::LogToTTY(); // コンソールへのロギングを開始
    ImGui::Text("--- ログ開始 ---");
    ImGui::Text("現在の値: %.3f", my_float_value);
    ImGui::Text("--- ログ終了 ---");
    ImGui::LogFinish(); // ロギングを終了
}
```

| 関数 | 説明 |
|------|------|
| `void ImGui::LogText(const char* fmt, ...)` | ログにテキストを書き込む |
| `void ImGui::LogToTTY()` | コンソール出力を開始 |
| `void ImGui::LogToFile(int max_size = -1, const char* filename = NULL)` | ファイル出力を開始 |
| `void ImGui::LogToClipboard(int max_size = -1)` | クリップボード出力を開始 |
| `void ImGui::LogFinish()` | ロギングセッションを終了 |

---

## まとめ

このドキュメントでは、ImGuiウィンドウに関連する以下の操作をカバーしました：

- ウィンドウ生成 (`Begin` / `End`)
- フラグとスタイル設定
- 位置・サイズ制御
- 子ウィンドウとグループ化
- 動的なウィンドウ制御API
- ツールチップ、入力情報、ロギング機能

これらを組み合わせることで、デバッグ用パネルから本格的なエディタUIまで柔軟に構築できます。
