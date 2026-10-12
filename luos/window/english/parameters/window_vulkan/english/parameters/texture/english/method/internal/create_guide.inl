namespace Gnik_luos {
    // 缺图时给美术的提示图:黑底,按"列 × 面"分格 —— 列是每一段(零长段不占列),行是六个面
    // 版式由同一键下最长的那条命令定;尺寸 = 展开版面尺寸 × 2(留精度余量,画完缩小到逻辑尺寸也清楚)
    void Vulkan_texture::create_guide(const std::string& path, const std::vector<Line_span>& usage) {
        const Line_span* layout = &usage.front();
        for (const Line_span& item : usage) {
            if (item.length > layout->length) {
                layout = &item;
            }
        }
        if (layout->length <= 0.0 || layout->column.empty()) {
            throw std::runtime_error("Vulkan_texture::create_guide => Nothing to unwrap for: " + path);
        }

        const double sheet_width = layout->length;
        const double row_height[6]{layout->size_y, layout->size_y, layout->size_y, layout->size_x, layout->size_x, layout->size_y};
        double sheet_height = 0.0;
        for (double height : row_height) {
            sheet_height += height;
        }

        const uint32_t width = static_cast<uint32_t>(sheet_width * 2.0);
        const uint32_t height = static_cast<uint32_t>(sheet_height * 2.0);
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

        std::cerr << "贴图缺失,已生成 uv 提示图: " << path << " (" << width << "x" << height
                  << ", " << layout->column.size() << " 列 × 6 面)" << std::endl;

        double row_v = 0.0;
        for (int row = 0; row < 6; row++) {
            const bool end_face = row == 0 || row == 5;
            double column = 0.0;
            for (double width_of_column : layout->column) {
                // 端面行:每列在它的开头占一小格(宽 = size_x);侧面行:整列都是这一段长的带
                const double cell_left = column;
                const double cell_right = column + (end_face ? layout->size_x : width_of_column);
                const double cell_top = row_v;
                const double cell_bottom = row_v + row_height[row];
                fill(cell_left, cell_top, cell_right, cell_bottom, 64);                    // 覆盖带
                fill(cell_left, cell_top, cell_right, cell_top + 0.5, 255);                // 上边界
                fill(cell_left, cell_bottom - 0.5, cell_right, cell_bottom, 255);          // 下边界
                fill(cell_left, cell_top, cell_left + 0.5, cell_bottom, 255);              // 左边界(分列线)
                fill(cell_right - 0.5, cell_top, cell_right, cell_bottom, 255);            // 右边界(分列线)
                column += width_of_column;
            }
            row_v += row_height[row];
        }

        image_cache.save(path, pixels.data(), width, height);
    }
}
