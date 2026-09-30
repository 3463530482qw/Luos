// 交换链与表面、视口都是同一条链上的邻居:用引用拿尺寸,不再借宿主窗口成员的指针
void create(const Vulkan_surface& surface, const Vulkan_viewport& viewport, const vk::raii::PhysicalDevice& physical_device, const vk::raii::Device& device);
void create_image_views(const vk::raii::Device& device);
void reset();
