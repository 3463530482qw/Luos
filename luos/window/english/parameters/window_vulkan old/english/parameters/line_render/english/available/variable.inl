std::vector<Vertex> vertex;   // 本帧线条顶点:谁画线就往这里追加,prepare 上传后清空
// 管线与顶点缓冲(资源句柄对外可见,与窗口其它火山子模块同一风格)
vk::raii::PipelineLayout pipeline_layout{nullptr};
vk::raii::Pipeline pipeline{nullptr};
std::array<vk::raii::Buffer, 2> vertex_buffer{nullptr, nullptr};        // 双缓冲:GPU 读上一帧那块,CPU 写这块
std::array<vk::raii::DeviceMemory, 2> vertex_memory{nullptr, nullptr};
Line_push_constants push_constants{};
bool snap_pixel{false};   // 顶点吸附到设备像素:线更硬,但缩放下线宽可能不匀
