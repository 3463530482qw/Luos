namespace Gnik_luos {
    // 把一张位图放进图集:格子是 2 的幂正方形,行式打包(行内放不下换行)
    // 回 false = 这次没放下(调用方换更大的图集重来),回 true 时 uv 与位图尺寸都填好了
    bool Font::private_place(Atlas_info& target, const unsigned char* bitmap, int width, int height, Glyph& metric) {
        const std::array<int, 4> pad = private_pad(width, height);
        const int side = width + pad[0] + pad[2];
        if (target.width == 0) {
            const int bound = private_glyph_bound(private_scale(target.pixel_height)) + atlas_glyph_margin * 2;
            target.width = private_power_of_two(std::max(side, bound));   // 行宽按字形上界定:别为每个宽字形重建一次
            target.height = target.width * atlas_row_budget;              // 一次给足几行:免得每烤一个字都要把整张图集重烤一遍
            target.pixels.assign(static_cast<size_t>(target.width) * static_cast<size_t>(target.height) * 4, 0);
        }
        if (side > target.width) {
            target.need_wider = true;   // 这一块比行宽还宽(字体没报准自己的上界):图集要同时长宽,只长高会原地打转
            return false;
        }
        if (target.cursor_x + side > target.width) {
            target.cursor_x = 0;
            target.cursor_y += target.row_height;
            target.row_height = 0;
        }
        if (target.cursor_y + side > target.height) {
            return false;   // 这一行之后放不下了:换更高的图集重来
        }

        for (int row = 0; row < height; row++) {
            unsigned char* destination = target.pixels.data()
                + (static_cast<size_t>(target.cursor_y + pad[1] + row) * static_cast<size_t>(target.width) + static_cast<size_t>(target.cursor_x + pad[0])) * 4;
            for (int column = 0; column < width; column++) {
                destination[column * 4 + 0] = 255;   // 字形像素是纯白,颜色由顶点色乘上去
                destination[column * 4 + 1] = 255;
                destination[column * 4 + 2] = 255;
                destination[column * 4 + 3] = bitmap[static_cast<size_t>(row) * static_cast<size_t>(width) + static_cast<size_t>(column)];
            }
        }

        metric.width = static_cast<float>(width);
        metric.height = static_cast<float>(height);
        const float inset_u = 0.5f / static_cast<float>(target.width);    // 内缩半纹素:线性过滤不啃到隔壁字形
        const float inset_v = 0.5f / static_cast<float>(target.height);
        metric.u0 = (static_cast<float>(target.cursor_x + pad[0]) / static_cast<float>(target.width)) + inset_u;
        metric.v0 = (static_cast<float>(target.cursor_y + pad[1]) / static_cast<float>(target.height)) + inset_v;
        metric.u1 = (static_cast<float>(target.cursor_x + pad[0] + width) / static_cast<float>(target.width)) - inset_u;
        metric.v1 = (static_cast<float>(target.cursor_y + pad[1] + height) / static_cast<float>(target.height)) - inset_v;
        target.cursor_x += side;
        target.row_height = std::max(target.row_height, side);
        target.revision++;   // 像素内容变了:版本 +1,渲染侧据此换贴图槽位
        return true;
    }
}
