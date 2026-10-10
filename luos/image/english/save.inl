namespace Gnik_luos {
    Image& Image::save(const std::string& path, const unsigned char* pixels, uint32_t width, uint32_t height) {
        if (stbi_write_png(path.c_str(), static_cast<int>(width), static_cast<int>(height), 4, pixels, static_cast<int>(width) * 4) == 0) {
            throw std::runtime_error(std::string("Image::save => Image failed to save: ") + path);
        }
        return *this;
    }
}
