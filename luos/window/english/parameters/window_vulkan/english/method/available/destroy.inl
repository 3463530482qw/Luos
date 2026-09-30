namespace Gnik_luos {
    void Window_vulkan::destroy() {
        if (!initialized) {
            return;
        }
        initialized = false;

        vulkan_engine().device.waitIdle();
        destroy_resources();
        // 火山仍由应用持有与销毁,这里只把自己标成未初始化
    }
}
