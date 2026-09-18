namespace Gnik_luos {
    void Window_vulkan::destroy() {
        if (!initialized) {
            return;
        }
        initialized = false;

        vulkan->device.waitIdle();
        destroy_resources();
        vulkan = nullptr;   // 解绑借用,火山仍由应用持有
    }
}
