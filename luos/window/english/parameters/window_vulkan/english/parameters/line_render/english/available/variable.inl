Vulkan** vulkan_source{nullptr};   // 指向窗口火山的火山借用指针:接上后一直有效   // 火山由窗口火山在构造后接上;项目内部一律走 vulkan()
Camera& camera;   // 相机子模块(窗口火山持有):构造期绑死,不再判空
Vulkan_texture* texture_source{nullptr};   // 贴图仓库(窗口火山持有):构造期接上,按路径取描述符
// 着色器文件名:由 Window_vulkan 在每次建交换链时从渲染配置抄进来(create_pipeline 用)
// 名字带 file 后缀,免得和 create_pipeline 里那两个 ShaderModule 局部变量撞名
std::string vertex_shader_file{"line.vert.spv"};
std::string fragment_shader_file{"line.frag.spv"};

std::vector<Vertex> vertex;   // 本帧线条顶点:谁画线就往这里追加,prepare 上传后清空
std::vector<Line_span> span;   // 本帧分段表:每条命令占的区间与贴图路径,Draw 登记时追加,prepare 消费后清空
std::vector<std::string> group_texture{};             // 本帧分组:每组用哪张图(空串 = 不指定)
std::vector<vk::DescriptorSet> group_descriptor{};    // 每组绑的描述符集
std::vector<std::array<float, 2>> group_scale{};       // 每组贴图的 uv 缩放(1/展开世界宽, 1/展开世界高)
std::vector<std::array<uint32_t, 2>> group_range{};   // 每组在顶点表里的 (起点, 条数)
// 管线与顶点缓冲(资源句柄与窗口其它火山子模块同一风格,对外可见)
vk::raii::PipelineLayout pipeline_layout{nullptr};
vk::raii::Pipeline pipeline{nullptr};
std::array<vk::raii::Buffer, 2> vertex_buffer{nullptr, nullptr};        // 双缓冲:GPU 读上一帧那块,CPU 写这块
std::array<vk::raii::DeviceMemory, 2> vertex_memory{nullptr, nullptr};
Line_push_constants push_constants{};
bool snap_pixel{false};   // 顶点吸附到设备像素:线更硬,但缩放下线宽可能不匀
