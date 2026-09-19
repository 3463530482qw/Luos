namespace Gnik_luos {
    uint32_t Vulkan_depth::find_memory_type(uint32_t type_filter, vk::MemoryPropertyFlags properties) {
        vk::PhysicalDeviceMemoryProperties memory_properties = (*vulkan)->physical_device.getMemoryProperties();
        for (uint32_t index = 0; index < memory_properties.memoryTypeCount; index++) {
            bool match_type = (type_filter & (1u << index)) != 0;
            bool match_property = (memory_properties.memoryTypes[index].propertyFlags & properties) == properties;
            if (match_type && match_property) {
                return index;
            }
        }
        throw std::runtime_error("Vulkan_depth::find_memory_type => No memory type matches the requirement");
    }
}
