namespace Gnik_luos {
    Thread& Thread::wait() {
        std::unique_lock lock(mutex);
        condition_variable.wait(lock, [this]() {
            return update_outstanding.load(std::memory_order_acquire) == 0 &&
                   draw_outstanding.load(std::memory_order_acquire) == 0;
        });
        return *this;
    }
}
