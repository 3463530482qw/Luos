namespace Gnik_luos {
    void Draw::draw() {
        for (Line& cmd : keep_lines) {
            cmd.update();
            if (private_vertex_sink == nullptr) {
                continue;
            }
            const std::vector<Vertex>& vertices = cmd.vertex();
            private_vertex_sink->insert(private_vertex_sink->end(), vertices.begin(), vertices.end());
        }
        for (Line& cmd : frame_lines) {
            cmd.update();
            if (private_vertex_sink == nullptr) {
                continue;
            }
            const std::vector<Vertex>& vertices = cmd.vertex();
            private_vertex_sink->insert(private_vertex_sink->end(), vertices.begin(), vertices.end());
        }
        // 当帧命令已交出去,表清空:下一帧的登记从空表重新开始(常驻表不动)
        frame_lines.clear();
    }
}
