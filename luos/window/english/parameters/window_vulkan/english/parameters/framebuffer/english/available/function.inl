void create(
    const vk::raii::Device& device,
    const vk::raii::RenderPass& render_pass,
    const std::vector<vk::raii::ImageView>& image_views,
    vk::Extent2D extent
);