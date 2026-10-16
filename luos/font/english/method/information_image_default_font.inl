namespace Gnik_luos {
    // 内置的默认字形贴图:没绑字体的文字命令拿它当"占位字形"用
    // 只用粗水平条 + 粗边框:斜线、细线在缩放(世界尺寸 ≠ 贴图像素)下会断成虚线,这里避开
    // side 按"一个方块会有多少像素"给:贴图像素与方块像素越接近,放大后的毛刺越少
    Information_image Information_image_default_font(int side) {
        side = std::clamp(side, font_default_texture_size, font_default_texture_limit);
        const int thickness = std::max(2, side / 16);
        std::vector<unsigned char> pixels(static_cast<size_t>(side) * side * 4, 0);
        const auto fill = [&pixels, side](int x0, int y0, int x1, int y1, unsigned char red, unsigned char green, unsigned char blue) {
            for (int y = std::max(0, y0); y < std::min(side, y1); y++) {
                for (int x = std::max(0, x0); x < std::min(side, x1); x++) {
                    unsigned char* texel = &pixels[(static_cast<size_t>(y) * side + static_cast<size_t>(x)) * 4];
                    texel[0] = red;
                    texel[1] = green;
                    texel[2] = blue;
                    texel[3] = 255;
                }
            }
        };

        for (size_t index = 3; index < pixels.size(); index += 4) {
            pixels[index] = 255;   // 底:不透明
        }
        fill(0, 0, side, side, 110, 118, 132);                             // 底色(冷灰)
        fill(0, 0, side, thickness, 226, 232, 240);                        // 上沿
        fill(0, side - thickness, side, side, 226, 232, 240);              // 下沿
        fill(0, 0, thickness, side, 226, 232, 240);                        // 左沿
        fill(side - thickness, 0, side, side, 226, 232, 240);              // 右沿
        fill(side / 5, side / 4, side - side / 5, side / 4 + thickness, 240, 244, 250);                      // 第一行
        fill(side / 5, side / 2 - thickness / 2, side - side / 4, side / 2 + thickness / 2, 240, 244, 250);  // 第二行(长一点)
        fill(side / 4, side * 3 / 4 - thickness, side - side / 5, side * 3 / 4, 240, 244, 250);              // 第三行

        Information_image image{};
        image.pixels = std::move(pixels);
        image.data = image.pixels.data();
        image.identity = next_texture_identity();   // 自带像素的身份号:渲染侧靠它认贴图槽位,不看地址
        image.width = side;
        image.height = side;
        image.channels = 4;
        return image;
    }
}
