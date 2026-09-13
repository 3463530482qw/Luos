namespace Gnik_luos {
    // x 右边第一个格心所在的列号:格心落在 x 右边,这一格才算铺到
    int Draw_line_cmd::private_pixel_col(float x) const {
        return static_cast<int>(std::floor(x / pixel_size - 0.5f)) + 1;
    }
}
