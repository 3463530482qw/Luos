void allocate(const vk::raii::Device& device, const vk::raii::CommandPool& command_pool, uint32_t count);
void begin(uint32_t index);
void begin_render_pass(
    uint32_t index,
    const vk::raii::RenderPass& render_pass,
    const vk::raii::Framebuffer& framebuffer,
    vk::Rect2D& render_area,
    vk::ClearValue& clear_value
);