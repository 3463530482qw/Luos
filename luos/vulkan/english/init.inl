namespace Gnik_luos {
    void Vulkan::init(Vulkan_info& vulkan_info) {
        create_instance(vulkan_info);
        pick_physical_device();
    }

    void Vulkan::初始化(Vulkan_info& vulkan_info) { init(vulkan_info); }
    void Vulkan::创建设备(uint32_t graphics_queue_family) { create_logical_device(graphics_queue_family); }
}
