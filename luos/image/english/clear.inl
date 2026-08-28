namespace Gnik_luos {
    Image& Image::clear() {
        for (auto& group : pack) {
            for (auto& img : group) {
                if (img.data) {
                    stbi_image_free(img.data);
                    img.data = nullptr;
                }
            }
        }
        pack.clear();
        return *this;
    }
}
