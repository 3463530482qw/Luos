namespace Gnik_luos {
    void Draw_line_cmd::private_geometry() {
        if (private_length <= 0.0f) {
            return;
        }
        private_quad(private_ax, private_ay, private_bx, private_by, private_u0, private_u1);
    }
}
