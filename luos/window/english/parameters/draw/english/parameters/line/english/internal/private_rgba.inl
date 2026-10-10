namespace Gnik_luos {
    void Line::private_rgba() {
        const float red = r / 255.0f;
        const float green = g / 255.0f;
        const float blue = b / 255.0f;
        const float texture_flag = use_texture ? 1.0f : 0.0f;
        for (Vertex& v : cache) {
            v.r = red;
            v.g = green;
            v.b = blue;
            v.a = a;
            v.use_texture = texture_flag;
        }
    }
}
