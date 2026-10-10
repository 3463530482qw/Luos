void attach(Vulkan*& vulkan_engine);   // 接上火山(引用别名只在 attach 里绑一次)
Vulkan& vulkan();   // 内部取用口
vk::raii::DescriptorSetLayout& layout();   // 管线布局要用:第一次取的时候建
// 按路径取槽位(没有就建):usage = 本帧用这条路径的所有段,展开尺寸与缺图提示图都由它算
const vk::raii::DescriptorSet& descriptor(const std::string& path, const std::vector<Line_span>& usage);
const Texture_slot& slot_of(const std::string& path);   // 查已建好的槽位(拿展开尺寸用)
void record_barrier(const vk::raii::CommandBuffer& command_buffer, const std::string& path);   // 这张图第一次用之前补一条布局屏障
void destroy();
