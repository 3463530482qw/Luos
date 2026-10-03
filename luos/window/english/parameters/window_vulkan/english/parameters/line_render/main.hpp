#include "english/parameters/push_constants.inl"
// 顶点格式 Vertex 由 draw 子模块定义(window\parameters\draw 先于本模块引入),线条管线只用不改
namespace Gnik_luos {
    class Vulkan;
    class Vulkan_line_render {
        public:
            #include "english/available/variable.inl"
        public:
            Vulkan_line_render(Camera& camera_layer);   // 相机在构造期绑死,之后一路有效
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
        private:
            #include "english/available/internal/function.inl"
    };
}
#include "english/method/available/main.inl"
#include "english/method/available/create.inl"
#include "english/method/available/prepare.inl"
#include "english/method/available/draw.inl"
#include "english/method/available/destroy.inl"
#include "english/method/internal/load_shader.inl"
#include "english/method/internal/create_pipeline.inl"
#include "english/method/internal/create_vertex_buffer.inl"
#include "english/method/internal/find_memory_type.inl"
