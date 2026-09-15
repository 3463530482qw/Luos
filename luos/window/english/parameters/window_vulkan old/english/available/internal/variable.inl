bool initialized{false};
bool rebuild_flag{false};
uint32_t pending_width{0};
uint32_t pending_height{0};
float pending_aspectratio{0};
uint32_t pending_logic_width{0};
uint32_t logic_width{0};    // 宿主窗口的逻辑画布尺寸(线条投影用,此处取不到 Window 完整定义,故在 initialize 时抄一份)
uint32_t logic_height{0};
uint32_t graphics_queue_family{0};
Vulkan* vulkan{nullptr};   // 火山由应用持有,窗口火山只借用
