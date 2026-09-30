namespace Gnik_luos {
    // 视图空间 → 裁剪空间:两台取景器在这里分叉,别处不再判断档位
    //   正交档:取景框长在视图空间里(xy 就是面前的画面,z 原样通到 NDC 深度)
    //   透视档:视锥压进 NDC,裁剪空间 z ∈ [0, 1](Vulkan 口径:近平面 0、远平面 1)
    Matrix4 Camera::projection_view_space() const {
        if (!is_perspective) {
            return private_orthographic_matrix();
        }
        return private_perspective_matrix(private_aspect());
    }
}
