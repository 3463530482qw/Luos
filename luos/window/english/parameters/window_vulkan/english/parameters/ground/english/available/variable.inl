Vulkan** vulkan{nullptr};   // 火山由窗口火山借用,地面管线跟着设备建
Camera* camera{nullptr};    // 相机:由 Window 构造时接上,地面按它定位与投影

bool enabled{true};         // 总开关(默认开),值由窗口火山从火山初始化配置抄进来
std::string vertex_shader_file{"ground.vert.spv"};
std::string fragment_shader_file{"ground.frag.spv"};
float grid_size{100.0f};        // 小格边长(世界单位)
float major_every{10.0f};       // 每几格一条主线
float fade_distance{8000.0f};   // 离相机地面投影多远淡出到看不见
float minor_color[4]{0.42f, 0.44f, 0.5f, 0.5f};    // 小格线颜色(rgba)
float major_color[4]{0.72f, 0.74f, 0.8f, 0.85f};   // 主格线颜色(rgba)
vk::raii::PipelineLayout pipeline_layout{nullptr};
vk::raii::Pipeline pipeline{nullptr};
