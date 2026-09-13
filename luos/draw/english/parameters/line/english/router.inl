namespace Gnik_luos {
    void Draw_line_cmd::router() {
        // 标志运行时可变:与上次快照一致就沿用现有管线
        bool rotate_on = (rotate != 0.0f);
        bool edge_on = (label.edge_top || label.edge_middle || label.edge_bottom || label.edge_both);
        if (private_routed &&
            private_label.solid == label.solid &&
            private_label.dashed == label.dashed &&
            private_label.gradient == label.gradient &&
            private_label.connected == label.connected &&
            private_label.edge_top == label.edge_top &&
            private_label.edge_middle == label.edge_middle &&
            private_label.edge_bottom == label.edge_bottom &&
            private_label.edge_both == label.edge_both &&
            private_rotate_on == rotate_on) {
            return;
        }
        private_routed = true;
        private_label = label;
        private_rotate_on = rotate_on;

        private_step.clear();
        if (!label.solid && !label.dashed) {
            return;
        }
        private_step.push_back(rotate_on ? &Draw_line_cmd::private_rotation : &Draw_line_cmd::private_endpoint);
        private_step.push_back(&Draw_line_cmd::private_normal);
        if (label.connected && !label.dashed) {
            private_step.push_back(&Draw_line_cmd::private_connect);
        }
        private_step.push_back(label.dashed ? &Draw_line_cmd::private_dashed : &Draw_line_cmd::private_geometry);
        if (edge_on) {
            private_step.push_back(&Draw_line_cmd::private_edge_cap);
        }
        private_step.push_back(label.gradient ? &Draw_line_cmd::private_gradient : &Draw_line_cmd::private_single_color);
    }
}
