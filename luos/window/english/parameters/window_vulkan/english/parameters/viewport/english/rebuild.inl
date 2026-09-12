namespace Gnik_luos {
    void Vulkan_viewport::rebuild(uint32_t window_width, uint32_t window_height, float window_aspectratio, uint32_t logic_width) {
        if (window_width == 0 || window_height == 0) {
            width = 0;
            height = 0;
            cut_offset_width = 0;
            cut_offset_height = 0;
            scale = 1.0f;   // 不取 0/0:除零会得到 nan,一旦写进视口就是整帧黑屏
            return;
        }

        // 比例口径:窗口比例只用来判断窗口是"更宽"还是"更高",内接矩形始终按传入的
        // 画布比例取 —— 传进来的值无效(0/nan)时才退回窗口比例,再退回 16:9
        float canvas_ratio = window_aspectratio;
        if (!(canvas_ratio > 0.0f) || !std::isfinite(canvas_ratio)) {
            canvas_ratio = static_cast<float>(window_width) / static_cast<float>(window_height);
        }
        if (!(canvas_ratio > 0.0f) || !std::isfinite(canvas_ratio)) {
            canvas_ratio = 1.7778f;
        }
        float window_ratio = static_cast<float>(window_width) / static_cast<float>(window_height);

        // 窗口内取最大内接矩形:更宽就按高度贴合(左右留灰边),更高就按宽度贴合(上下留灰边)
        if (window_ratio > canvas_ratio) {
            height = window_height;
            width = static_cast<uint32_t>(static_cast<float>(window_height) * canvas_ratio);
        } else {
            width = window_width;
            height = static_cast<uint32_t>(static_cast<float>(window_width) / canvas_ratio);
        }
        cut_offset_width = static_cast<int32_t>((window_width - width) / 2);
        cut_offset_height = static_cast<int32_t>((window_height - height) / 2);
        scale = (logic_width == 0) ? 1.0f : static_cast<float>(width) / static_cast<float>(logic_width);
    }
}
