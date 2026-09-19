Vulkan** vulkan{nullptr};                       // 火山由窗口火山借用,深度图只跟着设备建
vk::Format format{vk::Format::eD32Sfloat};      // 深度格式:pick_format 按物理设备能力定
vk::raii::Image image{nullptr};                 // 深度图:与交换链同尺寸,随交换链重建
vk::raii::DeviceMemory memory{nullptr};
vk::raii::ImageView view{nullptr};              // 帧缓冲的第二个附件
