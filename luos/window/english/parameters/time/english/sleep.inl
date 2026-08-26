namespace Gnik_luos {
    void Window_time::sleep() {
        if (dt > sleep_fps) {
            return;
        }
        remaining = sleep_fps - dt;
        auto target_time = std::chrono::steady_clock::now()
            + std::chrono::duration<float>(remaining);
        std::this_thread::sleep_until(target_time);
    }
}