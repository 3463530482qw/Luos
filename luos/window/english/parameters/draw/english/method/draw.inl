namespace Gnik_luos {
    // 按登记序逐条铺:线是立体盒子(逐段逐面),图是一张四边形(一组 6 个顶点)
    void Draw::draw() {
        for (auto& command : commands) {
            if (Line* line = std::get_if<Line>(&command)) {
                line->update();
                if (private_vertex_sink == nullptr) {
                    continue;
                }
                const std::vector<Vertex>& vertices = line->vertex();
                if (vertices.empty()) {
                    continue;
                }
                if (private_span_sink != nullptr) {
                    private_span_sink->push_back(Line_span{
                        line->texture_key,
                        private_vertex_sink->size(),
                        vertices.size(),
                        line->size_x,
                        line->size_y,
                        line->segment_length(),
                        line->face_mask(),
                        false,
                        line->texture_image
                    });
                }
                private_vertex_sink->insert(private_vertex_sink->end(), vertices.begin(), vertices.end());
                continue;
            }
            Picture* picture = std::get_if<Picture>(&command);
            if (picture == nullptr) {
                continue;
            }
            picture->update();
            if (private_vertex_sink == nullptr) {
                continue;
            }
            const std::vector<Vertex>& vertices = picture->vertex();
            if (vertices.empty()) {
                continue;
            }
            if (private_span_sink != nullptr) {
                private_span_sink->push_back(Line_span{
                    picture->texture_key,
                    private_vertex_sink->size(),
                    vertices.size(),
                    static_cast<double>(std::abs(picture->x2 - picture->x1)),
                    static_cast<double>(std::abs(picture->y2 - picture->y1)),
                    {},
                    {},
                    true,
                    picture->texture_image
                });
            }
            private_vertex_sink->insert(private_vertex_sink->end(), vertices.begin(), vertices.end());
        }
        commands.clear();
    }
}
