namespace Gnik_luos {
    // 火山在 Window_vulkan 构造完之后接上:引用别名只在这里绑一次,别处不再碰指针
    void Vulkan_ground::attach(Vulkan*& vulkan_engine) {
        vulkan_source = &vulkan_engine;   // 记录借用指针的地址,火山一接上就能看见
    }

    Vulkan& Vulkan_ground::vulkan() {
        if (vulkan_source == nullptr || *vulkan_source == nullptr) {
            throw std::runtime_error("Vulkan_ground::vulkan => Vulkan engine not attached yet");
        }
        return **vulkan_source;
    }

    Vulkan_ground::Vulkan_ground(Camera& camera_layer) : camera(camera_layer) {
    }
}
