namespace Gnik_luos {
    // 四种封边只差"延伸点"落在哪:
    // 上   = 端头回缩 大小/2,延伸点在线宽上沿、原端头外 大小/2 处
    // 中   = 同上,延伸点在中线
    // 下   = 同上,延伸点在线宽下沿
    // 上下一块 = 不回缩接尖,改成在端头挖掉一个三角形(负形):上下两块尖连成一体
    void Draw_line_cmd::private_edge_place() {
        private_edge_on = (edge_size > 0.0f)
            && (label.edge_top || label.edge_middle || label.edge_bottom || label.edge_both);
        private_cap_retract = 0.0f;
        private_cap_forward = 0.0f;
        private_cap_lateral = 0.0f;
        private_cap_notch = false;
        if (!private_edge_on) {
            return;
        }
        if (label.edge_both) {
            private_cap_retract = edge_size;
            private_cap_notch = true;
            return;
        }
        private_cap_retract = edge_size * 0.5f;
        private_cap_forward = edge_size;
        private_cap_lateral = label.edge_top ? -1.0f : (label.edge_bottom ? 1.0f : 0.0f);
    }
}
