namespace Gnik_luos {
    void Vulkan::init(Vulkan_info& vulkan_info) {
        init_info = vulkan_info;
        create_instance(vulkan_info);
        pick_physical_device();
    }
}
