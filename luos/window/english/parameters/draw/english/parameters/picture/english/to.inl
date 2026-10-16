namespace Gnik_luos {
    Picture& Picture::to(float x, float y, float z) {
        x2 = x;
        y2 = y;
        z2 = z;
        private_ready = true;   // 第二个角落定,这张图成立
        dirty = true;
        return *this;
    }
}
