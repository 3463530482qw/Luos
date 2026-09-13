namespace Gnik_luos {
    void Draw_line_cmd::private_segment_colors(const Line_point& point, bool open) {
        // 封口的段用自己记下的颜色;未封口的最后一段用当前设置,两种写法(设色在前/在后)都成立
        private_er = open ? r : point.r;
        private_eg = open ? g : point.g;
        private_eb = open ? b : point.b;
        private_ea = open ? a : point.a;
    }
}
