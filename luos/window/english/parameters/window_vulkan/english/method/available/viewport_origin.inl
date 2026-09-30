namespace Gnik_luos {
    // 视口就是窗口内的内接矩形,四周留的灰边宽度由视口模块算好:
    // 这里只做转发,让窗口层不必穿透到火山子模块里取数
    double Window_vulkan::viewport_origin_x() const {
        return static_cast<double>(viewport.cut_offset_width);
    }

    double Window_vulkan::viewport_origin_y() const {
        return static_cast<double>(viewport.cut_offset_height);
    }
}
