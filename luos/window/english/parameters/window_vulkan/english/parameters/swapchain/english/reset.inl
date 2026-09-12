namespace Gnik_luos {
    void Vulkan_swapchain::reset() {
        // 重建前先释放旧交换链,确保其图像句柄全部失效
        swapchain.clear();
        images.clear();
        image_views.clear();
    }
}
