namespace Gnik_luos {
    Picture& Picture::corner_rgba(size_t corner, uint8_t red, uint8_t green, uint8_t blue, float alpha) {   // 单改一个角:角号越界就当没写
        if (corner >= 4) {
            return *this;
        }
        r[corner] = red;
        g[corner] = green;
        b[corner] = blue;
        a[corner] = alpha;
        dirty = true;
        return *this;
    }
}
