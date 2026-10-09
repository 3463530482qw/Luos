namespace Gnik_luos {
    // 默认取景:站位落在画布中心正前方(相机看向 +z,站位所以落在 z 的负侧),距离由 private_fit_distance 反解
    // 于是画布那一块(z = 0 平面)正好铺满视口:世界原点在窗口左下角,x 向右、y 向上,三轴都取正
    // 两档都摆站位:透视档的距离决定"画布铺满视口",正交档 xy 与距离无关、距离只决定深度的起点
    // 站位与 zoom 无关:zoom 缩的是取景范围,画布中心一直在画布尺寸的正中
    // 前提(由窗口在设置相机前保证):画布已按 logic 尺寸同步;没把站位显式写到画布之后的配置才走这里
    //   站位 z >= 0 视为"要贴合默认取景"(z = 0 与 x = y = 0 都是"没改"的写法)
    //   应用自己写的取景(站位在 z 的负侧、画布之前)不动它
    Camera& Camera::apply_default() {
        if (canvas_width <= 0.0 || canvas_height <= 0.0) {
            return *this;
        }
        if (position.position.z < 0.0) {
            return *this;
        }
        position.position.x = canvas_width * 0.5;
        position.position.y = canvas_height * 0.5;
        position.position.z = -private_fit_distance();
        return *this;
    }
}
