Window& setting();
Window& setting(Window_settings_info window_settings_info);
Window& create();
Window& create(Window_create_info& Window_create_info);
Window& move_to(int x, int y);        // 绝对位置
Window& move_to(double x, double y);  // 按显示器尺寸的比例(0~1)
Window& anchor_to(Anchor_x anchor_x, Anchor_y anchor_y);   // 贴到屏幕某个角/中点
Window& resize();
Window& resize(int w, int h);
Window& resize(float w, float h);
Window& set_icon(Information_image image);
Window& run();
Window& close();
