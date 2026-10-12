namespace Gnik_luos {
    struct Texture_slot {              // 一个槽位键对应的 GPU 贴图:池与描述符跟着槽位走,槽位多少都不受池的容量限制
        vk::raii::Image image{nullptr};
        vk::raii::DeviceMemory memory{nullptr};
        vk::raii::ImageView view{nullptr};
        vk::raii::Sampler sampler{nullptr};
        vk::raii::DescriptorPool pool{nullptr};
        vk::raii::DescriptorSet descriptor{nullptr};
        bool pending{false};           // 还在 UNDEFINED 布局:第一次用之前要补一条屏障
        // 展开版面的尺寸(用世界单位量的,跟场景的世界坐标无关):顶点里烘的 uv 是世界单位,除以它才折成 0~1
        double sheet_width{0.0};       // 版面宽 = 同一个键下最长那条命令的列宽之和
        double sheet_height{0.0};      // 版面高 = 2×size_x + 4×size_y(六行按面的真实尺寸拼出来的总和)
    };
}
