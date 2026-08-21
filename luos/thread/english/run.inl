namespace Gnik_luos {
    void Thread::run() {
        {
            std::unique_lock lock(mutex);
            condition_variable.wait(lock, [this]() {
                return draw_done.load(std::memory_order_acquire);
            });
        }
        if (!update_tasks.empty()) {
            phase.store(Phase::UPDATE, std::memory_order_release);
            update_done.store(false, std::memory_order_release);
            {
                std::lock_guard lock(mutex);
                update_claimed.store(0, std::memory_order_relaxed);
                update_completed.store(0, std::memory_order_relaxed);
            }
            condition_variable.notify_all();
            {
                std::unique_lock lock(mutex);
                condition_variable.wait(lock, [this]() {
                    return update_done.load(std::memory_order_acquire);
                });
            }
        }
        if (!draw_tasks.empty()) {
            phase.store(Phase::DRAW, std::memory_order_release);
            draw_done.store(false, std::memory_order_release);
            {
                std::lock_guard lock(mutex);
                draw_claimed.store(0, std::memory_order_relaxed);
                draw_completed.store(0, std::memory_order_relaxed);
            }
            condition_variable.notify_all();
        }
    }
}