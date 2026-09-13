namespace Gnik_luos {
    // 拐点圆滑度:0 保持原来的尖角,1 圆到底;超出范围就夹住
    Draw_line_cmd& Draw_line_cmd::smooth(float value) {
        corner_smooth = std::clamp(value, 0.0f, 1.0f);
        cmd_update = true;
        return *this;
    }
}
