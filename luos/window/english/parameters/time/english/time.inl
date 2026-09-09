namespace Gnik_luos {
    void Window_time::time() {
        auto now = std::chrono::steady_clock::now();
        before = current;
        current = std::chrono::duration<double>(now - start).count();

        dt = std::chrono::duration<double>(now - private_last).count();
        private_last = now;
        private_frame_accum += dt;
    }
}
