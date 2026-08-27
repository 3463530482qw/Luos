namespace Gnik_luos {
    void Window_time::time() {
        before = current;
        current = std::chrono::duration<double>(
            std::chrono::steady_clock::now() - start
        ).count();

        dt = current - before;
    }
}