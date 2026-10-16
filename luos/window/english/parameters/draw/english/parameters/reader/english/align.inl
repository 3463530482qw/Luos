namespace Gnik_luos {
    // 对齐方式只认这三个写法:别的当没写,回原来的值
    int read_align(std::string_view value, int fallback) {
        if (value == "left") {
            return 0;
        }
        if (value == "center") {
            return 1;
        }
        if (value == "right") {
            return 2;
        }
        return fallback;
    }
}
