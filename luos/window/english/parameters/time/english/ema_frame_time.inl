namespace Gnik_luos {
    void Window_time::ema_frame_time() {
        double ceiling = frame_interval * 4.0;
        double sample = std::clamp(dt, 0.0, ceiling);
        private_smooth_dt += smooth_alpha * (sample - private_smooth_dt);
        dt = private_smooth_dt;
    }
}
