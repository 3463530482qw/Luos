namespace Gnik_luos {
    Draw& Draw::bind_vertex_sink(std::vector<Vertex>& sink) {
        private_vertex_sink = &sink;
        return *this;
    }

    Draw& Draw::set_view(const Rect& view) {
        private_view = view;
        return *this;
    }
}
