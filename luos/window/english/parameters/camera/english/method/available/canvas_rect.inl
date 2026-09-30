namespace Gnik_luos {
    // 我当前显示的世界矩形 = 画布:矩形左下角贴世界原点(默认位置时就是世界原点)
    // 判定"是否默认位置"用三个分量,避免把 (0,0,0) 当成哨兵值 —— 相机站在原点是合法位置
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
