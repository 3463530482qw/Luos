namespace Gnik_luos {
    Text& Text::align(const std::string& value) {
        align_mode = read_align(value, align_mode);   // 别的写法当没写:对齐方式不由库替它猜
        dirty = true;
        return *this;
    }
}
