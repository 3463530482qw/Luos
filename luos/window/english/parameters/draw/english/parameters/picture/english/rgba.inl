namespace Gnik_luos {
    Picture& Picture::rgba(uint8_t red, uint8_t green, uint8_t blue, float alpha) {   // 四角同色
        for (size_t corner = 0; corner < 4; corner++) {
            r[corner] = red;
            g[corner] = green;
            b[corner] = blue;
            a[corner] = alpha;
        }
        dirty = true;
        return *this;
    }
}
