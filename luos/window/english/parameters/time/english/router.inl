namespace Gnik_luos {
    void Window_time::router() {
        auto now = std::chrono::steady_clock::now();
        start = now;
        private_last = now;
        private_target = now;
        current = 0.0;
        before = 0.0;
        dt = 0.0;
        private_frame_accum = 0.0;
        frame_interval = (set_fps > 0.0) ? set_fps : 1.0 / 60.0;

        private_update.clear();
        private_update.push_back([this]() { time(); });
        if (youk_smooth) {
            youk_target_time = frame_interval * (frame_interval + 1.0) * (frame_interval + 2.0);
            private_update.push_back([this]() { youklx_frame_time(); });
        }
        private_update.push_back([this]() { sleep(); });
    }
}
