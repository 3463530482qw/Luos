namespace Gnik_luos {
    // camera 子段:get_double 对整数/浮点都能取;键不存在就不覆盖,整段照旧用默认值
    bool Window_settings_info::private_load_camera() {
        if (target_type.at_key("camera").get_object().get(camera_object)) {
            return false;   // window_info 里没写 camera 段
        }
        has_camera = true;

        if (!camera_object.at_key("perspective").get_bool().get(temporary_camera_is_perspective)) {
            camera_is_perspective = temporary_camera_is_perspective;
        }
        if (!camera_object.at_key("x").get_double().get(temporary_camera_value)) {
            camera_x = temporary_camera_value;
        }
        if (!camera_object.at_key("y").get_double().get(temporary_camera_value)) {
            camera_y = temporary_camera_value;
        }
        if (!camera_object.at_key("z").get_double().get(temporary_camera_value)) {
            camera_z = temporary_camera_value;
        }
        if (!camera_object.at_key("rotation_x").get_double().get(temporary_camera_value)) {
            camera_rotation_x = temporary_camera_value;
        }
        if (!camera_object.at_key("rotation_y").get_double().get(temporary_camera_value)) {
            camera_rotation_y = temporary_camera_value;
        }
        if (!camera_object.at_key("rotation_z").get_double().get(temporary_camera_value)) {
            camera_rotation_z = temporary_camera_value;
        }
        if (!camera_object.at_key("fov").get_double().get(temporary_camera_value)) {
            camera_fov = temporary_camera_value;
        }
        if (!camera_object.at_key("near").get_double().get(temporary_camera_value)) {
            camera_near_plane = temporary_camera_value;
        }
        if (!camera_object.at_key("far").get_double().get(temporary_camera_value)) {
            camera_far_plane = temporary_camera_value;
        }
        if (!camera_object.at_key("zoom").get_double().get(temporary_camera_value)) {
            camera_zoom = temporary_camera_value;
        }
        return true;
    }
}
