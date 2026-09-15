namespace Gnik_luos {
    void Window_vulkan::find_graphics_queue_family() {
        auto queue_families = vulkan->physical_device.getQueueFamilyProperties();
        for (uint32_t index = 0; index < static_cast<uint32_t>(queue_families.size()); index++) {
            bool support_graphics = (queue_families[index].queueFlags & vk::QueueFlagBits::eGraphics) != vk::QueueFlags{};
            if (support_graphics && vulkan->physical_device.getSurfaceSupportKHR(index, surface.surface)) {
                graphics_queue_family = index;
                return;
            }
        }
        throw std::runtime_error("Window_vulkan::find_graphics_queue_family => No queue family supports both graphics and present");
    }
}
