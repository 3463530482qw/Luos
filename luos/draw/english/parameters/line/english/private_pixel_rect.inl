namespace Gnik_luos {
    // 像素化的填充:按整格铺一块,列号是闭区间 [first_col, last_col],行号 row
    void Draw_line_cmd::private_pixel_rect(int first_col, int last_col, int row, const std::array<uint8_t, 3>& color, float alpha) {
        if (last_col < first_col || pixel_size <= 0.0f) {
            return;
        }
        float left = static_cast<float>(first_col) * pixel_size;
        float right = static_cast<float>(last_col + 1) * pixel_size;
        float top = static_cast<float>(row) * pixel_size;
        float bottom = top + pixel_size;
        float red = color[0] / 255.0f;
        float green = color[1] / 255.0f;
        float blue = color[2] / 255.0f;
        const Vertex corner[6] = {
            {left, top,    0.0f, 0.0f, red, green, blue, alpha},
            {right, top,   0.0f, 0.0f, red, green, blue, alpha},
            {right, bottom, 0.0f, 0.0f, red, green, blue, alpha},
            {left, top,    0.0f, 0.0f, red, green, blue, alpha},
            {right, bottom, 0.0f, 0.0f, red, green, blue, alpha},
            {left, bottom, 0.0f, 0.0f, red, green, blue, alpha}
        };
        for (const Vertex& point : corner) {
            private_fill_vertex.push_back(point);
        }
    }
}
