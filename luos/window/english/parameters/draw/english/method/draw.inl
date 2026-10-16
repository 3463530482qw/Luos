namespace Gnik_luos {
    // 按登记序逐条铺:线是立体盒子(逐段逐面),图是一张四边形(一组 6 个顶点),文字是逐字形一组四边形,地图是一整层瓦片一张图集
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
                        line->texture_image,                });
                }
                private_vertex_sink->insert(private_vertex_sink->end(), vertices.begin(), vertices.end());
                continue;
            }
            if (Picture* picture = std::get_if<Picture>(&command)) {
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
                        picture->texture_image,                });
                }
                private_vertex_sink->insert(private_vertex_sink->end(), vertices.begin(), vertices.end());
                continue;
            }
            if (Text* text = std::get_if<Text>(&command)) {
                text->update();
                if (private_vertex_sink == nullptr) {
                    continue;
                }
                const std::vector<Vertex>& glyphs = text->vertex();
                if (glyphs.empty()) {
                    continue;
                }
                if (private_span_sink != nullptr) {
                    // 贴图键与像素在排版那一刻就定死了(Text::update 里算好),这里只搬运:
                    // 绘制命令这一帧末就被清掉,渲染侧再回头找命令要指针会取到悬空的像素
                    private_span_sink->push_back(Line_span{
                        text->texture_key,
                        private_vertex_sink->size(),
                        glyphs.size(),
                        0.0,
                        0.0,
                        {},
                        {},
                        true,              // 一张图铺满这一段:键就是那张贴图,顶点数按 count 走
                        text->texture_pixels,                });
                }
                private_vertex_sink->insert(private_vertex_sink->end(), glyphs.begin(), glyphs.end());
                continue;
            }
            if (Tilemap* tilemap = std::get_if<Tilemap>(&command)) {
                tilemap->update();
                if (private_vertex_sink == nullptr) {
                    continue;
                }
                const std::vector<Vertex>& tiles = tilemap->vertex();
                if (tiles.empty()) {
                    continue;
                }
                if (private_span_sink != nullptr) {
                    private_span_sink->push_back(Line_span{
                        tilemap->texture_key,
                        private_vertex_sink->size(),
                        tiles.size(),
                        0.0,
                        0.0,
                        {},
                        {},
                        true,              // 一整层共用一张图集:一组铺完,顶点数按 count 走
                        tilemap->texture_image,                });
                }
                private_vertex_sink->insert(private_vertex_sink->end(), tiles.begin(), tiles.end());
            }
        }
        commands.clear();
    }
}
