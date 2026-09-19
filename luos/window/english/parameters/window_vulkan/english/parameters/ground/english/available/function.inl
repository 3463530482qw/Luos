void create(const vk::raii::RenderPass& render_pass);
void prepare(float aspect);
void draw(const vk::raii::CommandBuffer& command_buffer);
void destroy();
