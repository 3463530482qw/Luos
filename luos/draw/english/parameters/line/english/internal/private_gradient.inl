namespace Gnik_luos {
    void Draw_line_cmd::private_gradient() {
        // 只染本段,用本段自己的两端颜色
        for (size_t index = private_emit_begin; index < private_vertex.size(); index++) {
            Vertex& v = private_vertex[index];
            float t = std::clamp(v.u, 0.0f, 1.0f);
            v.r = (private_er[0] + (private_er[1] - private_er[0]) * t) / 255.0f;
            v.g = (private_eg[0] + (private_eg[1] - private_eg[0]) * t) / 255.0f;
            v.b = (private_eb[0] + (private_eb[1] - private_eb[0]) * t) / 255.0f;
            v.a = private_ea[0] + (private_ea[1] - private_ea[0]) * t;
        }
    }
}
