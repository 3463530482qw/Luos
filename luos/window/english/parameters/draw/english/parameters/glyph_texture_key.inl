namespace Gnik_luos {
    // 文字这一路交贴图的方式与图片命令统一:直接交像素,键就用"像素身份 + 尺寸"
    //   image:<自带像素身份号 或 像素地址>:<宽>x<高>
    // 自带像素的用身份号(地址会被分配器复用,不能当身份);外部像素(图片模块的)用地址
    std::string glyph_texture_key(const Information_image& image) {
        const std::string identity = image.identity != 0
            ? std::to_string(image.identity)
            : std::to_string(reinterpret_cast<uintptr_t>(image.data));
        return "image:" + identity + ":" + std::to_string(image.width) + "x" + std::to_string(image.height);
    }
}
