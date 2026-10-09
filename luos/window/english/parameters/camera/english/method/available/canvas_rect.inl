namespace Gnik_luos {
    // 画布在世界里的范围:固定在原点左下、三轴全正的那块矩形(z = 0 平面),
    // 尺寸是画布尺寸按 zoom 缩放后的结果 —— zoom 缩的是取景范围,不是画布本身的位置
    // 正交档它就是取景框;透视档是"屏幕 ↔ 画布"的换算基准(视口比例、拾取夹取都按它)
    Canvas_rect Camera::canvas_rect() const {
        const double scale = (zoom > zoom_min) ? zoom : 1.0;
        const double half_width = canvas_width * 0.5 / scale;
        const double half_height = canvas_height * 0.5 / scale;
        const double center_x = canvas_width * 0.5;
        const double center_y = canvas_height * 0.5;

        Canvas_rect rect;
        rect.min_x = center_x - half_width;
        rect.max_x = center_x + half_width;
        rect.min_y = center_y - half_height;
        rect.max_y = center_y + half_height;
        rect.z = 0.0;
        return rect;
    }
}
