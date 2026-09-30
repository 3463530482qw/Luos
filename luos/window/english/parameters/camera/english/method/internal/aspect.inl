namespace Gnik_luos {
    // 视口比例由取景的画布尺寸决定(宽高有 0 就退回 16:9,别把 0 传进投影)
    double Camera::private_aspect() const {
        if (canvas_width <= 0.0 || canvas_height <= 0.0) {
            return aspect_fallback;
        }
        return canvas_width / canvas_height;
    }
}
