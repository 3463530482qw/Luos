namespace Gnik_luos {
    // 四种封边只差"延伸点"落在哪:
    // 上/中/下 = 端头回缩 大小/2,延伸点在线宽上沿/中线/下沿,纵向都在原端头外 大小/2 处
    // 上下一块 = 三角形负形(端面挖掉一个三角形)
    // 半圆正/负形 = 上面两种的圆角版:尖换成圆弧,范围与原形一样(圆弧仍然过延伸点)
    void Draw_line_cmd::private_edge_place() {
        private_edge_on = (edge_size > 0.0f)
            && (label.edge_top || label.edge_middle || label.edge_bottom
                || label.edge_both || label.edge_round || label.edge_round_notch);
        private_cap_retract = 0.0f;
        private_cap_forward = 0.0f;
        private_cap_lateral = 0.0f;
        private_cap_notch = false;
        if (!private_edge_on) {
            return;
        }
        if (label.edge_round_notch || label.edge_both) {
            private_cap_retract = edge_size;
            private_cap_notch = true;
            return;
        }
        private_cap_retract = edge_size * 0.5f;
        private_cap_forward = edge_size;
        private_cap_lateral = label.edge_top ? -1.0f : (label.edge_bottom ? 1.0f : 0.0f);
    }
}
