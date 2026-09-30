void attach(Vulkan*& vulkan_engine);   // 接上火山(引用别名只在 attach 里绑一次)
Vulkan& vulkan();   // 内部取用口
void create(const vk::raii::RenderPass& render_pass);
void prepare();   // 推常量(投影与视口比例都由相机给)
void draw(const vk::raii::CommandBuffer& command_buffer);
void destroy();
