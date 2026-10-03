namespace Gnik_luos {
    // 默认取景的"世界 → 裁剪"闭式矩阵(列主序 16 个 float,直接可推给着色器):
    //   相机看世界的默认口径就是逻辑窗口(canvas_width x canvas_height),不掺任何别的量:
    //     x_ndc = wx · 2/canvas_w - 1        y_ndc = 1 - wy · 2/canvas_h
    //     w ≡ 1(仿射),z 取常数 0.5(正交档式深度,落在 Vulkan 的 [0,1] 里)
    //   画布四角因此正落在视口四角(视口本身已按画布比例取窗口内接矩形),不多不少
    void Camera::canvas_clip_matrix(float* out) const {
        const double scale = (zoom > zoom_min) ? zoom : 1.0;
        const double canvas_w = canvas_width / scale;
        const double canvas_h = canvas_height / scale;
        for (int index = 0; index < 16; index++) {
            out[index] = 0.0f;
        }
        if (canvas_w <= 0.0 || canvas_h <= 0.0) {
            return;
        }
        out[0] = static_cast<float>(2.0 / canvas_w);
        out[5] = static_cast<float>(-2.0 / canvas_h);
        out[12] = -1.0f;
        out[13] = 1.0f;
        out[14] = 0.5f;
        out[15] = 1.0f;
    }
}
