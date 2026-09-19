namespace Gnik_luos {
    void Vulkan_depth::destroy() {
        view = nullptr;
        image = nullptr;
        memory = nullptr;
    }
}
