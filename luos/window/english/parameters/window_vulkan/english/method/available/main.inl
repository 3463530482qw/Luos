namespace Gnik_luos {
    // 相机子模块与渲染模块在构造期一次绑死:引用一路有效到析构,后面不再需要判空
    // 绘制器归窗口所有,窗口在构造期把实体交进来(那时两边都已构造完毕);视口量用的时候从宿主窗口现取
    Window_vulkan::Window_vulkan(Draw& draw_layer) : drawer(draw_layer), line_render(camera), ground(camera) {
        line_render.attach_draw(drawer);
        depth.attach(vulkan_borrowed);
        line_render.attach(vulkan_borrowed);
        ground.attach(vulkan_borrowed);
    }

    Window_vulkan::~Window_vulkan() {
        // 显式销毁由 destroy 负责(Window 析构会调用),这里只保证句柄与借用引用不残留
        initialized = false;
        rebuild_flag = false;
    }
}
