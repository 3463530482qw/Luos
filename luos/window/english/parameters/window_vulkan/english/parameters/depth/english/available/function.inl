void attach(Vulkan*& vulkan_engine);   // 接上火山(引用别名只在 attach 里绑一次)
Vulkan& vulkan();   // 内部取用口
void create(vk::Extent2D extent);
void destroy();
