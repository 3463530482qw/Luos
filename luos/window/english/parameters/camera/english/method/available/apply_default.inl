namespace Gnik_luos {
    // 默认取景:站位落在画布中心正前方,距离由 private_fit_distance 反解
    // 坐标系(右手系):x 正向右、y 正向上、z 正靠观察者;相机看向 -z,所以站位落在画布前方的 z 正侧
    //   站位 z = +距离,于是画布那一块(z = 0 平面)正好铺满视口:世界原点在画布左下角,x 向右、y 向上
    // 两档都摆站位:透视档的距离决定"画布铺满视口",正交档 xy 与距离无关、距离只决定深度的起点
    // 站位与 zoom 无关:zoom 缩的是取景范围,画布中心一直在画布尺寸的正中
    // 前提(由窗口在设置相机前保证):画布已按 logic 尺寸同步
    //   站位三个分量全为 0 = "没写站位"(camera 段整个不写,或 x/y/z 都写 0)→ 走这里的默认贴合
    //   给了任意一个非 0 分量就一字不差照用 —— 站位、旋转、fov 都是调用方的口径,这里不再重摆
    Camera& Camera::apply_default() {
        if (canvas_width <= 0.0 || canvas_height <= 0.0) {
            return *this;
        }
        const Vector3& point = position.position;
        if (point.x != 0.0 || point.y != 0.0 || point.z != 0.0) {
            return *this;
        }
        position.position.x = canvas_width * 0.5;
        position.position.y = canvas_height * 0.5;
        position.position.z = private_fit_distance();
        return *this;
    }
}
