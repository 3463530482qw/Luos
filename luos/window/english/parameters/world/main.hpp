#include "english/parameters/world_point.inl"
#include "english/parameters/world_ray.inl"
#include "english/parameters/canvas_rect.inl"
#include "english/parameters/ground_hit.inl"
namespace Gnik_luos {
    class World {
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
    };
}
#include "english/method/intersect_ground.inl"
