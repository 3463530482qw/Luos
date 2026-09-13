namespace Gnik_luos {
    Draw& Draw::bind_camera(Camera& camera) {
        private_camera = &camera;
        return *this;
    }
}
