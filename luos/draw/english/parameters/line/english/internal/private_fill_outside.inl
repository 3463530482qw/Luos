namespace Gnik_luos {
    // 外部填充:把"当前可见矩形"挖掉形状本身
    // 两条通路各自成文件:像素化走 private_fill_outside_pixel,其余走 private_fill_outside_band
    void Draw_line_cmd::private_fill_outside() {
        if (!label.fill_outside || private_path.size() < 3) {
            return;
        }
        // 可见矩形是世界量(double),这里只是几何边界,取用时收窄成 float
        const float view_left = static_cast<float>(private_view.left);
        const float view_top = static_cast<float>(private_view.top);
        const float view_right = static_cast<float>(private_view.right);
        const float view_bottom = static_cast<float>(private_view.bottom);

        if (label.pixelated && pixel_size > 0.0f) {
            private_fill_outside_pixel(view_left, view_top, view_right, view_bottom);
            return;
        }
        private_fill_outside_band(view_left, view_top, view_right, view_bottom);
    }
}
