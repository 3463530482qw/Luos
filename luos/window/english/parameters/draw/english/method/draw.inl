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
                    cmd.texture_key,
                    private_vertex_sink->size(),
                    vertices.size(),
                    cmd.size_x,
                    cmd.size_y,
                    cmd.segment_length(),
                    cmd.face_mask(),
                    cmd.texture_image
                });
            }
            private_vertex_sink->insert(private_vertex_sink->end(), vertices.begin(), vertices.end());
        }
        lines.clear();
    }
}
