namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::rotation(float radians, float center_x, float center_y) {
        // 弧度从 0 变非 0(或反过来)会换掉管线的第一步
        rotate = radians;
        rox = center_x;
        roy = center_y;
        cmd_update = true;
        return *this;
    }
}
