namespace Gnik_luos {
    Thread& Thread::wait() {
        std::unique_lock lock(mutex);
        condition_variable.wait(lock, [this]() {
            if (active_workers.load(std::memory_order_acquire) != 0) return false;
            if (phase.load(std::memory_order_acquire) == Phase::IDLE) return true;
            return update_claimed.load(std::memory_order_acquire) == update_quantity.load(std::memory_order_acquire) &&
                   update_completed.load(std::memory_order_acquire) == update_quantity.load(std::memory_order_acquire) &&
                   draw_claimed.load(std::memory_order_acquire) == draw_quantity.load(std::memory_order_acquire) &&
                   draw_completed.load(std::memory_order_acquire) == draw_quantity.load(std::memory_order_acquire);
        });
        return *this;
    }
}
