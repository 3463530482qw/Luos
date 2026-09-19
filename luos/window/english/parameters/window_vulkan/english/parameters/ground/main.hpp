#include "english/parameters/push_constants.inl"
namespace Gnik_luos {
    class Vulkan_ground {
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
            #include "english/available/internal/function.inl"
    };
}
#include "english/method/available/create.inl"
#include "english/method/available/prepare.inl"
#include "english/method/available/draw.inl"
#include "english/method/available/destroy.inl"
#include "english/method/internal/load_shader.inl"
#include "english/method/internal/create_pipeline.inl"
