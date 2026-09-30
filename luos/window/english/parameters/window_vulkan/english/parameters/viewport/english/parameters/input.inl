namespace Gnik_luos {
    struct Viewport_input {   // 视口算内接矩形要的窗口量:值语义,由 Window_vulkan 推过来
        uint32_t window_width{0};
        uint32_t window_height{0};
        uint32_t logic_width{1600};
        uint32_t logic_height{900};
        float aspectratio{0.0f};
    };
}
