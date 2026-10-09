namespace Gnik_luos {
    // 默认站位:把画布精确塞进取景框需要多远的距离(相机看向 +z,站位落在 z 的负侧)
    //   透视档:可见矩形恒为画布比例的相似形,纵向半高 = tan(纵向半角)·距离,所以
    //     距离 = 半高 / tan(纵向半角),横向同理(半宽按画布比例换算,两支合起来就是画布满视口)
    //   正交档:xy 的取景框长在视图空间里,与距离无关;但深度要有起点(近平面得落在画布之前),
    //           所以同样给这个距离 —— 两档的站位口径因此一致
    double Camera::private_fit_distance() const {
        const double scale = (zoom > zoom_min) ? zoom : 1.0;
        const double half_height = canvas_height * 0.5 / scale;
        if (half_height <= 0.0) {
            return 0.0;
        }
        const double focal = std::tan(fov * 0.5 * pi / 180.0);
        if (focal <= 0.0) {
            return half_height;   // 角度退化:也要把站位放在画布之前,深度才有起点
        }
        return half_height / focal;
    }
}
