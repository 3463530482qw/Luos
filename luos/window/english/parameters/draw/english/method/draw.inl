namespace Gnik_luos {
    void Draw::draw() {
        for (Line& cmd : lines) {
            cmd.update();
            if (private_vertex_sink == nullptr) {
                continue;
            }
            const std::vector<Vertex>& vertices = cmd.vertex();
            if (vertices.empty()) {
                continue;
            }
            if (private_span_sink != nullptr) {
                private_span_sink->push_back(Line_span{
                    cmd.texture_path,
                    private_vertex_sink->size(),
                    vertices.size(),
                    cmd.length(),
                    cmd.size_x,
                    cmd.size_y,
                    cmd.layout_column()
                });
            }
            private_vertex_sink->insert(private_vertex_sink->end(), vertices.begin(), vertices.end());
        }
        lines.clear();
    }
}
