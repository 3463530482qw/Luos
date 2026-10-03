namespace Gnik_luos {
    // 默认站位:把画布精确塞进取景框需要多远的距离(相机看向 +z,站位落在 z 的负侧)
    //   透视档:可见矩形恒为画布比例的相似形,纵向半高 = tan(纵向半角)·距离;要装下整块画布就得让
    //   纵向与横向各留出画布的一半,两式都不够就装不下,所以取两个方向里更远的那个:
    //     距离 = 半高 / tan(纵向半角),横向同理(半宽按画布比例换算)
    //   正交档没有透视收敛,取景框就长在视图空间里,不需要距离,给 0
    double Camera::private_fit_distance() const {
        const double scale = (zoom > zoom_min) ? zoom : 1.0;
        const double half_height = canvas_height * 0.5 / scale;
        if (half_height <= 0.0) {
            return 0.0;
        }
        if (!is_perspective) {
            return 0.0;
        }
        const double focal = std::tan(fov * 0.5 * pi / 180.0);
        if (focal <= 0.0) {
            return 0.0;
        }
        return half_height / focal;
    }
}
