namespace Gnik_luos {
    struct Texture_slot {              // 一条路径对应的 GPU 贴图:池与描述符跟着槽位走,槽位多少都不受池的容量限制
        vk::raii::Image image{nullptr};
        vk::raii::DeviceMemory memory{nullptr};
        vk::raii::ImageView view{nullptr};
        vk::raii::Sampler sampler{nullptr};
        vk::raii::DescriptorPool pool{nullptr};
        vk::raii::DescriptorSet descriptor{nullptr};
        bool pending{false};           // 还在 UNDEFINED 布局:第一次用之前要补一条屏障
        double world_width{0.0};       // 展开图的世界宽:同一路径里最长那条命令的总长
        double world_height{0.0};      // 展开图的世界高:六行按面的真实尺寸拼出来的总和
    };
}
