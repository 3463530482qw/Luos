void attach(Vulkan*& vulkan_engine);   // 接上火山(引用别名只在 attach 里绑一次)
Vulkan& vulkan();   // 内部取用口:窗口火山保证在 create / prepare / draw 之前已接上
void attach_draw(Draw& draw_layer);   // 绘制器的顶点出口接到本渲染器的顶点表
// 随交换链重建调用:渲染通道一换,管线就得跟着重建;顶点缓冲只与设备有关,保留
void create(const vk::raii::RenderPass& render_pass, vk::Extent2D& swapchain_extent);
void prepare();   // 帧前算好推常量(投影与视口比例都由相机给,必须在录制之外)
void draw(const vk::raii::CommandBuffer& command_buffer);   // 纯录制:绑管线/推常量/绑顶点缓冲/画
void destroy();
