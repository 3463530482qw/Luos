namespace Gnik_luos {
    Picture& Draw::picture() {
        commands.emplace_back(Picture{});
        return std::get<Picture>(commands.back());
    }

    Picture& Draw::picture(const Picture& source) {
        commands.emplace_back(source);
        return std::get<Picture>(commands.back());
    }
}
