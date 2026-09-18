Vulkan** vulkan{nullptr};
// 着色器文件名:由 Window_vulkan 在每次建交换链时从渲染配置抄进来(create_pipeline 用)
// 名字带 file 后缀,免得和 create_pipeline 里那两个 ShaderModule 局部变量撞名
std::string vertex_shader_file{"line.vert.spv"};
std::string fragment_shader_file{"line.frag.spv"};

std::vector<Vertex> vertex;   // 本帧线条顶点:谁画线就往这里追加,prepare 上传后清空
// 管线与顶点缓冲(资源句柄与窗口其它火山子模块同一风格,对外可见)
vk::raii::PipelineLayout pipeline_layout{nullptr};
vk::raii::Pipeline pipeline{nullptr};
std::array<vk::raii::Buffer, 2> vertex_buffer{nullptr, nullptr};        // 双缓冲:GPU 读上一帧那块,CPU 写这块
std::array<vk::raii::DeviceMemory, 2> vertex_memory{nullptr, nullptr};
Line_push_constants push_constants{};
bool snap_pixel{false};   // 顶点吸附到设备像素:线更硬,但缩放下线宽可能不匀
