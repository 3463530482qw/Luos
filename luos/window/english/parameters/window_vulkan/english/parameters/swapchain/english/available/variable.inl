vk::Format format{vk::Format::eUndefined};
uint32_t preferred_image_count{0};
vk::Extent2D extent{0, 0};
vk::raii::SwapchainKHR swapchain{nullptr};
std::vector<vk::raii::ImageView> image_views;
