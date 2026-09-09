namespace Gnik_luos {
    void Window_time::sleep() {
        if (frame_interval <= 0.0) {
            return;
        }
        private_target += std::chrono::duration_cast<std::chrono::steady_clock::duration>(
            std::chrono::duration<double>(frame_interval)
        );
        auto now = std::chrono::steady_clock::now();
        if (private_target <= now) {
            private_target = now;
            return;
        }
        if (private_target - now > std::chrono::duration_cast<std::chrono::steady_clock::duration>(
                std::chrono::duration<double>(frame_interval * 4.0))) {
            private_target = now;
            return;
        }
        std::this_thread::sleep_until(private_target);
    }
}
