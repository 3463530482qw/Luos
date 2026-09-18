Vulkan** vulkan{nullptr};
// 着色器文件名:由 Window_vulkan 在每次建交换链时从渲染配置抄进来(create_pipeline 用)
// 名字带 file 后缀,免得和 create_pipeline 里那两个 ShaderModule 局部变量撞名
std::string vertex_shader_file{"line.vert.spv"};
std::string fragment_shader_file{"line.frag.spv"};
