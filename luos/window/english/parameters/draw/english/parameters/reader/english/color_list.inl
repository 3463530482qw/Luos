namespace Gnik_luos {
    // 读一组颜色(逐组的 {red,green,blue,alpha}):按出现顺序填进四角,组数不足就只填前面几组;缺键保默认
    void read_color_list(const simdjson::dom::element& source, uint8_t* red, uint8_t* green, uint8_t* blue, float* alpha, size_t count) {
        if (!source.is_array()) {
            return;
        }
        size_t corner = 0;
        for (auto entry : source.get_array()) {
            if (corner >= count) {
                break;
            }
            read_color(entry, red[corner], green[corner], blue[corner], alpha[corner]);
            corner++;
        }
    }
}
