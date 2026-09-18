namespace Gnik_luos {
    void Window_vulkan::request_rebuild() {
        // 尺寸与比例都是借用窗口成员的指针(自动跟随 resize),这里只置标记
        rebuild_flag = true;
    }
}
