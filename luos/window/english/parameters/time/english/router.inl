namespace Gnik_luos {
    void Window_time::router() {
        start = std::chrono::steady_clock::now();
        private_update.clear();
        if (set_fps > 0.000015) {
            sleep_fps = set_fps - 0.000015;
        } else {
            sleep_fps = 0;
        }
        private_update.push_back([this]() { time(); });
        if (youk_smooth) {
            youk_target_time = sleep_fps * (sleep_fps + 1.0f) * (sleep_fps + 2.0f);
            private_update.push_back([this]() { youklx_frame_time(); });
        }
        private_update.push_back([this]() { sleep(); });
    }
    private_update();
}