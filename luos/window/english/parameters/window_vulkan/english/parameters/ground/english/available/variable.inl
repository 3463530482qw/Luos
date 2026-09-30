Vulkan** vulkan_source{nullptr};   // 指向窗口火山的火山借用指针:接上后一直有效   // 火山由窗口火山在构造后接上;项目内部一律走 vulkan()
Camera& camera;             // 相机子模块(窗口火山持有):构造期绑死,不再判空

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
