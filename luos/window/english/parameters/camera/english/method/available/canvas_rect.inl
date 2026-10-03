namespace Gnik_luos {
    // 我的取景范围:世界矩形,尺寸是画布尺寸按 zoom 缩放后的结果,xy 跟着站位走
    // 正交档它就是取景框本身;透视档只作"画布口径"的换算基准(屏幕↔画布、视口比例都按它)
    Canvas_rect Camera::canvas_rect() const {
        const double scale = (zoom > zoom_min) ? zoom : 1.0;
        const double width = canvas_width / scale;
        const double height = canvas_height / scale;

        Canvas_rect rect;
        rect.z = 0.0;
        if (position.position.x == 0.0 && position.position.y == 0.0 && position.position.z == 0.0) {
            rect.min_x = 0.0;
            rect.max_x = width;
            rect.min_y = -height;   // y 向下:左上角在原点,矩形朝下铺
            rect.max_y = 0.0;
            return rect;
        }
        rect.min_x = position.position.x;
        rect.max_x = position.position.x + width;
        rect.min_y = position.position.y - height;
        rect.max_y = position.position.y;
        return rect;
    }
}
