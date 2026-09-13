namespace Gnik_luos {
    void Draw::draw(Draw_line_cmd& cmd) {
        cmd.camera = private_camera;
        if (cmd.cmd_update) {
            cmd.update();
            cmd.cmd_update = false;
        }
        if (private_vertex_sink == nullptr) {
            return;
        }
        // 填充单独一层:插到列表头部的填充区末尾,任何线条都追加在它后面
        // 于是填充压在全部线条之下,不会夹在前后两条线中间
        if (private_fill_head > private_vertex_sink->size()) {
            private_fill_head = 0;   // 上一帧的顶点已经上传清空,填充区重新从头部数
        }
        const std::vector<Vertex>& fill = cmd.fill_vertex();
        private_vertex_sink->insert(
            private_vertex_sink->begin() + static_cast<std::vector<Vertex>::difference_type>(private_fill_head),
            fill.begin(),
            fill.end()
        );
        private_fill_head += fill.size();
        const std::vector<Vertex>& line = cmd.vertex();
        private_vertex_sink->insert(private_vertex_sink->end(), line.begin(), line.end());
    }
}
