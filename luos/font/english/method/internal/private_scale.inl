namespace Gnik_luos {
    // 字号按"字高"折算:stb_truetype 的像素高 = 上下伸部之和
    double Font::private_scale(double pixel_height) const {
        if (pixel_height <= 0.0) {
            return stbtt_ScaleForPixelHeight(&font_info, 1.0f);
        }
        return stbtt_ScaleForPixelHeight(&font_info, static_cast<float>(pixel_height));
    }
}
