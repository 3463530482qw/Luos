namespace Gnik_luos {
    Tilemap& Draw::map() {
        commands.emplace_back(Tilemap{});
        return std::get<Tilemap>(commands.back());
    }

    Tilemap& Draw::map(const Tilemap& source) {
        commands.emplace_back(source);
        return std::get<Tilemap>(commands.back());
    }
}
