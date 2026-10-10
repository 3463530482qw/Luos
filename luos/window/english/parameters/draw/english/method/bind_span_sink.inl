namespace Gnik_luos {
    Draw& Draw::bind_span_sink(std::vector<Line_span>& sink) {
        private_span_sink = &sink;
        return *this;
    }
}
