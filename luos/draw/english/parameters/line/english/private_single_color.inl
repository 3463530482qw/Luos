namespace Gnik_luos {
    void Draw_line_cmd::private_single_color() {
        float red = private_er[0] / 255.0f;
        float green = private_eg[0] / 255.0f;
        float blue = private_eb[0] / 255.0f;
        for (size_t index = private_emit_begin; index < private_vertex.size(); index++) {
            Vertex& v = private_vertex[index];
            v.r = red;
            v.g = green;
            v.b = blue;
            v.a = private_ea[0];
        }
    }
}
