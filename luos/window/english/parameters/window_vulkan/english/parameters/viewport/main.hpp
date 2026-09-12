#pragma once
namespace Gnik_luos {
    class Vulkan_viewport {
        public:
            uint32_t width{0};
            uint32_t height{0};
            int32_t cut_offset_width{0};
            int32_t cut_offset_height{0};
            float scale{1.0f};
        public:
            void rebuild(uint32_t window_width, uint32_t window_height, float window_aspectratio, uint32_t logic_width);
    };
    using 火山视口 = Vulkan_viewport;
}
