Window& setting();
Window& setting(Window_settings_info window_settings_info);
Window& create();
Window& create(Window_create_info& Window_create_info);
Window& position_adjustment_numerical(float px, float py);
Window& position_adjustment_numerical(int px, int py);
Window& position_adjustment_positional(int px, int py);
Window& run();