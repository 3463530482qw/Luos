namespace Gnik_luos {
    // 这一行相对文字块左上角要挪多少:左对齐 0,居中负半个行宽,右对齐负一整行宽
    float Text::private_align_offset(float width) const {
        if (align_mode == 1) {
            return -width * 0.5f;
        }
        if (align_mode == 2) {
            return -width;
        }
        return 0.0f;
    }
}
