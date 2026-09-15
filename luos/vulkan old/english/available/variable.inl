Vulkan_info vulkan_info;
vk::raii::Instance instance{nullptr};
vk::raii::PhysicalDevice physical_device{nullptr};
vk::raii::Device device{nullptr};
vk::Queue graphics_queue{nullptr};
