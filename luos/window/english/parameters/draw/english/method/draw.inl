namespace Gnik_luos {
    void Draw::draw() {
        for (Line& cmd : lines) {
            cmd.update();
            if (private_vertex_sink == nullptr) {
                continue;
            }
            const std::vector<Vertex>& vertices = cmd.vertex();
            private_vertex_sink->insert(private_vertex_sink->end(), vertices.begin(), vertices.end());
        }
        lines.clear();
    }
}
