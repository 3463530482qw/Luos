namespace Gnik_luos {
    void Vulkan_swapchain::reset() {
        // 先放视图再放交换链:图像视图引用的是交换链的图像,反过来销毁等于让视图悬空
        image_views.clear();
        images.clear();
        swapchain.clear();
    }
}
