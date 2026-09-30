Vulkan** vulkan_source{nullptr};   // 指向窗口火山的火山借用指针:接上后一直有效   // 火山由窗口火山在构造后接上;项目内部一律走 vulkan()
vk::Format format{vk::Format::eD32Sfloat};      // 深度格式:pick_format 按物理设备能力定
vk::raii::Image image{nullptr};                 // 深度图:与交换链同尺寸,随交换链重建
vk::raii::DeviceMemory memory{nullptr};
vk::raii::ImageView view{nullptr};              // 帧缓冲的第二个附件
