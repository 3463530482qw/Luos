namespace Gnik_luos {
    // 贴图仓库由窗口火山持有,构造期接上:之后按路径取描述符都走它
    void Vulkan_line_render::attach_texture(Vulkan_texture& texture_layer) {
        texture_source = &texture_layer;
    }

    Vulkan_texture& Vulkan_line_render::texture() {
        if (texture_source == nullptr) {
            throw std::runtime_error("Vulkan_line_render::texture => Texture repository not attached yet");
        }
        return *texture_source;
    }
}
