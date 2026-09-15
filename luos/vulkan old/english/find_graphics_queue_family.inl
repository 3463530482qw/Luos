namespace Gnik_luos {
    uint32_t Vulkan::find_graphics_queue_family(vk::SurfaceKHR surface) {
        auto queue_families = physical_device.getQueueFamilyProperties();
        for (uint32_t index = 0; index < static_cast<uint32_t>(queue_families.size()); index++) {
            bool support_graphics = (queue_families[index].queueFlags & vk::QueueFlagBits::eGraphics) != vk::QueueFlags{};
            if (support_graphics && physical_device.getSurfaceSupportKHR(index, surface)) {
                return index;
            }
        }
        throw std::runtime_error("Vulkan::find_graphics_queue_family => No queue family supports both graphics and present");
    }
}
