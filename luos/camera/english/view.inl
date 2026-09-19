namespace Gnik_luos {
    View_rect Camera::view() const {
        // 画布尺寸按缩放折算成世界单位,以相机位置为中心
        float half_width = canvas_width * 0.5f / ((zoom > 0.0f) ? zoom : 1.0f);
        float half_height = canvas_height * 0.5f / ((zoom > 0.0f) ? zoom : 1.0f);
        return View_rect{x - half_width, y - half_height, x + half_width, y + half_height};
    }
}
