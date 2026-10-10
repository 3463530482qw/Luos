namespace Gnik_luos {
    // 火山在 Window_vulkan 构造完之后接上:引用别名只在这里绑一次,别处不再碰指针
    void Vulkan_texture::attach(Vulkan*& vulkan_engine) {
        vulkan_source = &vulkan_engine;
    }

    Vulkan& Vulkan_texture::vulkan() {
        if (vulkan_source == nullptr || *vulkan_source == nullptr) {
            throw std::runtime_error("Vulkan_texture::vulkan => Vulkan engine not attached yet");
        }
        return **vulkan_source;
    }
}
