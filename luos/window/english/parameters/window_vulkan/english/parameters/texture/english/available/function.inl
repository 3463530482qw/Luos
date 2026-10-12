void attach(Vulkan*& vulkan_engine);   // 接上火山(引用别名只在 attach 里绑一次)
Vulkan& vulkan();   // 内部取用口
vk::raii::DescriptorSetLayout& layout();   // 管线布局要用:第一次取的时候建
// 按块路径取槽位(没有就建):键是块文件路径、"image:<像素地址>"(直接交的像素)或空(库内那张纯色);
// 块文件不在就按 (block_width, block_height) 生成一张描边块 —— 那是这块在世界里的尺寸
const vk::raii::DescriptorSet& descriptor(const std::string& key, double block_width, double block_height, const Information_image* passed);
void record_barrier(const vk::raii::CommandBuffer& command_buffer, const std::string& key);   // 这块第一次用之前补一条布局屏障
void destroy();
