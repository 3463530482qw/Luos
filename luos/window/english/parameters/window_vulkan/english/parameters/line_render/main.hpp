#include "english/parameters/push_constants.inl"
// 顶点格式 Vertex 由 draw 模块定义(luos/main.hpp 里 draw 先于 window 引入),线条管线只用不改
namespace Gnik_luos {
    class Vulkan_line_render {
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
        private:
            #include "english/available/internal/function.inl"
    };
}
#include "english/method/available/create.inl"
#include "english/method/available/prepare.inl"
#include "english/method/available/draw.inl"
#include "english/method/available/destroy.inl"
#include "english/method/internal/load_shader.inl"
#include "english/method/internal/create_pipeline.inl"
#include "english/method/internal/create_vertex_buffer.inl"
#include "english/method/internal/find_memory_type.inl"
