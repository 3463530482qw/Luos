namespace Gnik_luos {
    // 像素化通路:逐格行取补集,行与列都夹在可见矩形内
    void Draw_line_cmd::private_fill_outside_pixel(float view_left, float view_top, float view_right, float view_bottom) {
        const int first_row = private_pixel_col(view_top);
        const int last_row = private_pixel_col(view_bottom) - 1;
        const int view_first_col = private_pixel_col(view_left);
        const int view_last_col = private_pixel_col(view_right) - 1;
        std::vector<float> crossing{};
        for (int row = first_row; row <= last_row; row++) {
            private_crossings((static_cast<float>(row) + 0.5f) * pixel_size, crossing);
            int cursor = view_first_col;
            for (size_t index = 0; index + 1 < crossing.size(); index += 2) {
                const int first_col = private_pixel_col(crossing[index]);
                const int last_col = private_pixel_col(crossing[index + 1]) - 1;
                if (first_col > cursor) {
                    private_pixel_rect(cursor, first_col - 1, row, outside_color, outside_alpha);
                }
                cursor = std::max(cursor, last_col + 1);
            }
            if (cursor <= view_last_col) {
                private_pixel_rect(cursor, view_last_col, row, outside_color, outside_alpha);
            }
        }
    }
}
