namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::pixelate(float size) {
        pixel_size = size;
        label.pixelated = size > 0.0f;
        cmd_update = true;
        return *this;
    }
}
