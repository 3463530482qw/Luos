namespace Gnik_luos {
    // 火山在 Window_vulkan 构造完之后接上:引用别名只在这里绑一次,别处不再碰指针
    void Vulkan_line_render::attach(Vulkan*& vulkan_engine) {
        vulkan_source = &vulkan_engine;   // 记录借用指针的地址,火山一接上就能看见
    }

    Vulkan& Vulkan_line_render::vulkan() {
        if (vulkan_source == nullptr || *vulkan_source == nullptr) {
            throw std::runtime_error("Vulkan_line_render::vulkan => Vulkan engine not attached yet");
        }
        return **vulkan_source;
    }

    Vulkan_line_render::Vulkan_line_render(Camera& camera_layer) : camera(camera_layer) {
    }

    // 绘制器与本渲染器互为引用:接线在 Window_vulkan 构造完之后做(那时两边都已就位)
    void Vulkan_line_render::attach_draw(Draw& draw_layer) {
        draw_layer.bind_vertex_sink(vertex);
    }
}
