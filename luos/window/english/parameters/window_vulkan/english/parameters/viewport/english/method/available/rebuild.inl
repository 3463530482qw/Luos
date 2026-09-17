namespace Gnik_luos {
    void Vulkan_viewport::rebuild() {
        height = static_cast<float>(*window_height) * (*aspectratio);
        if (static_cast<float>(*window_width) >= width) {
            width = height;
            height = static_cast<float>(height) / static_cast<float>(*aspectratio);
            cut_offset_width = (static_cast<float>(*window_width) - width) / 2.0f;
            cut_offset_height = 0;
        } else {
            width = static_cast<float>(*window_width);
            height = static_cast<float>(width) / (*aspectratio);
            cut_offset_height = (static_cast<float>(*window_height) -  height) / 2.0f;
            cut_offset_width = 0;
        }
        *logic_aspectratio = static_cast<float>(width) / static_cast<float>(*window_logic_width);
    }
}