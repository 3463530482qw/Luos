namespace Gnik_luos {
    Line& Draw::line() {
        lines.emplace_back();
        return lines.back();
    }

    Line& Draw::line(const Line& source) {
        lines.push_back(source);
        return lines.back();
    }
}
