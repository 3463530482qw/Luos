namespace Gnik_luos {
    // 默认取景:站位落在画布中心正前方(相机看向 +z,站位所以落在 z 的负侧),距离由 private_fit_distance 反解
    // 于是画布那一块(z = 0 平面)正好铺满视口:世界原点在窗口左下角,x 向右、y 向上,三轴都取正
    // 前提(由窗口在设置相机前保证):画布已按 logic 尺寸同步;没把站位显式写到画布之后的配置才走这里
    //   站位 z >= 0 视为"要贴合默认取景"(z = 0 与 x = y = 0 都是"没改"的写法)
    //   应用自己写的取景(站位在 z 的负侧、画布之前)不动它
    Camera& Camera::apply_default() {
        if (!is_perspective || canvas_width <= 0.0 || canvas_height <= 0.0) {
            return *this;
        }
        if (position.position.z < 0.0) {
            return *this;
        }
        const double scale = (zoom > zoom_min) ? zoom : 1.0;
        position.position.x = canvas_width * 0.5 / scale;
        position.position.y = canvas_height * 0.5 / scale;
        position.position.z = -private_fit_distance();
        return *this;
    }
}
