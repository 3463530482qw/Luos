namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::solid(bool on) {
        // 打开就关掉虚线;两面都关则不绘制(见 router)
        label.solid = on;
        if (on) {
            label.dashed = false;
        }
        cmd_update = true;
        return *this;
    }
}
