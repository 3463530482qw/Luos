namespace Gnik_luos {
    Text& Draw::text() {
        commands.emplace_back(Text{});
        return std::get<Text>(commands.back());
    }

    Text& Draw::text(const Text& source) {
        commands.emplace_back(source);
        return std::get<Text>(commands.back());
    }
}
