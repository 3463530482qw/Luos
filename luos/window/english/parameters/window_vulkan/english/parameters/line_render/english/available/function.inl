// 随交换链重建调用:渲染通道一换,管线就得跟着重建;顶点缓冲只与设备有关,保留
void create(const vk::raii::RenderPass& render_pass, vk::Extent2D& swapchain_extent);
void prepare(float logic_width, float logic_height);   // 帧前上传本帧顶点并算好推常量(必须在录制之外)
void draw(const vk::raii::CommandBuffer& command_buffer);   // 纯录制:绑管线/推常量/绑顶点缓冲/画
void destroy();
