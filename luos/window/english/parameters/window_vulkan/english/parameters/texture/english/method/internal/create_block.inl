namespace Gnik_luos {
    // 缺块时给美术的提示块:黑底,覆盖带(暗) + 四边描边(亮,0.5 世界单位宽)
    // 尺寸 = 该块自己的世界尺寸 ×2(留精度余量,画完缩小到逻辑尺寸也清楚)
    void Vulkan_texture::create_block(const std::string& path, double world_width, double world_height) {
        if (world_width <= 0.0 || world_height <= 0.0) {
            throw std::runtime_error("Vulkan_texture::create_block => Bad block size for: " + path);
        }
        std::filesystem::create_directories(std::filesystem::path(path).parent_path());   // 贴图文件夹不存在就先建出来

        const uint32_t width = static_cast<uint32_t>(world_width * 2.0);
        const uint32_t height = static_cast<uint32_t>(world_height * 2.0);
        std::vector<unsigned char> pixels(static_cast<size_t>(width) * height * 4, 0);
        for (size_t index = 3; index < pixels.size(); index += 4) {
            pixels[index] = 255;   // 黑底不透明
        }

        const auto fill = [&pixels, width, height](double x0, double y0, double x1, double y1, unsigned char value) {
            const int left = std::max(0, static_cast<int>(x0 * 2.0));
            const int top = std::max(0, static_cast<int>(y0 * 2.0));
            const int right = std::min(static_cast<int>(width), static_cast<int>(x1 * 2.0));
            const int bottom = std::min(static_cast<int>(height), static_cast<int>(y1 * 2.0));
            for (int y = top; y < bottom; y++) {
                for (int x = left; x < right; x++) {
                    unsigned char* texel = &pixels[(static_cast<size_t>(y) * width + static_cast<size_t>(x)) * 4];
                    texel[0] = value;
                    texel[1] = value;
                    texel[2] = value;
                }
            }
        };

        fill(0.0, 0.0, world_width, world_height, 64);                                    // 覆盖带
        fill(0.0, 0.0, world_width, 0.5, 255);                                            // 上边界
        fill(0.0, world_height - 0.5, world_width, world_height, 255);                    // 下边界
        fill(0.0, 0.0, 0.5, world_height, 255);                                           // 左边界
        fill(world_width - 0.5, 0.0, world_width, world_height, 255);                     // 右边界

        image_cache.save(path, pixels.data(), width, height);
    }
}
