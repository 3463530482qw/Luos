void create(
    const vk::raii::Device& device,
    const vk::raii::RenderPass& render_pass,
    const std::vector<vk::raii::ImageView>& image_views,
    const vk::raii::ImageView& depth_view,
    vk::Extent2D extent
);