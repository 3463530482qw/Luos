namespace Gnik_luos {
    void Line::private_direction() {
        private_dx /= private_length;
        private_dy /= private_length;
        const float half = thickness * 0.5f;
        private_nx = -private_dy * half;
        private_ny = private_dx * half;
    }
}
