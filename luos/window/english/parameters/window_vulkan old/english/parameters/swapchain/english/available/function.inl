void reset();
void create(
    const vk::raii::PhysicalDevice& physical_device,
    const vk::raii::Device& device,
    vk::SurfaceKHR surface,
    uint32_t window_width,
    uint32_t window_height
);
void create_image_views(const vk::raii::Device& device);
