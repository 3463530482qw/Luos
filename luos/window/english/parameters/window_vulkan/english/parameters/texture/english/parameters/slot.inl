namespace Gnik_luos {
    struct Texture_slot {              // 一个槽位键对应的 GPU 贴图:只管素材(像素 → 图/视图/采样器/描述符)
        vk::raii::Image image{nullptr};
        vk::raii::DeviceMemory memory{nullptr};
        vk::raii::ImageView view{nullptr};
        vk::raii::Sampler sampler{nullptr};
        vk::raii::DescriptorPool pool{nullptr};
        vk::raii::DescriptorSet descriptor{nullptr};
        bool pending{false};           // 还在 UNDEFINED 布局:第一次用之前要补一条屏障
    };
}
