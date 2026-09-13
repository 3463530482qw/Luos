namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::dash(float length, float gap) {
        // 段长与间隔一起写,风格直接切到虚线
        dash_length = length;
        dash_gap = gap;
        label.dashed = true;
        label.solid = false;
        cmd_update = true;
        return *this;
    }
}
