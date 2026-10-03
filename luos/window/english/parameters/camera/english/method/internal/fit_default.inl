namespace Gnik_luos {
    // 默认取景:站位落在画布中心正前方,距离由 private_fit_distance 反解 ——
    // 于是站位推到 z = 0 时,世界原点的 1600x900(默认逻辑窗口)与世界单位的 1600x900 一一对应
    // 前提(由窗口在设置相机前保证):画布已按 logic 尺寸同步;没把站位显式写到画布之前的配置才走这里
    //   站位 z <= 0 视为"要贴合默认取景"(z = 0 与 x = y = 0 都是"没改"的写法)
    //   源 json 写的站位在画布之前(z < 0),那是应用自己的取景,不动它
    void Camera::private_fit_default() {
        if (!is_perspective || canvas_width <= 0.0 || canvas_height <= 0.0) {
            return;
        }
        if (position.position.z < 0.0) {
            return;
        }
        const double scale = (zoom > zoom_min) ? zoom : 1.0;
        position.position.x = canvas_width * 0.5 / scale;
        position.position.y = -canvas_height * 0.5 / scale;
        position.position.z = -private_fit_distance();
    }
}
