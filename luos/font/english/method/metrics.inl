namespace Gnik_luos {
    // 基线到文字块顶的高:文字块左上角按它落到第一行基线上
    double Font::ascent(double pixel_height) const {
        if (!ready || pixel_height <= 0.0) {
            return 0.0;
        }
        return static_cast<double>(ascent_metric) * private_scale(pixel_height);
    }

    // 字体自己的行高:上下伸部加行距;调用方给了行距就用调用方的
    double Font::line_height(double pixel_height) const {
        if (!ready || pixel_height <= 0.0) {
            return 0.0;
        }
        const double scale = private_scale(pixel_height);
        return static_cast<double>(ascent_metric - descent_metric + line_gap_metric) * scale;
    }
}
