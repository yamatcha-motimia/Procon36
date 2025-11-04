#pragma once
#include "common/namespace_macro.hpp"

BEGIN_SOLVER_NAMESPACE

class DebugGUI {
public:
    DebugGUI() = default;
    DebugGUI(const DebugGUI&) = delete;
    DebugGUI& operator=(const DebugGUI&) = delete;

    ~DebugGUI() = default;

    void run();
private:
    void initGLFW();
    void initImgui();
    void renderFrame();
    void drawUI();
};

END_SOLVER_NAMESPACE
