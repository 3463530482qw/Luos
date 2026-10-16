namespace Gnik_luos {
    Line& Draw::line() {
        commands.emplace_back(Line{});
        return std::get<Line>(commands.back());
    }

    Line& Draw::line(const Line& source) {
        commands.emplace_back(source);
        return std::get<Line>(commands.back());
    }
}
