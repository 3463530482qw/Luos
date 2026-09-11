namespace Gnik_luos {
    void Thread::dispatch(Phase next_phase, size_t task_quantity, uint32_t gen) {
        std::unique_lock lock(mutex);
        phase.store(next_phase, std::memory_order_release);
        current_gen = gen;
        switch (next_phase) {
            case Phase::UPDATE:
                update_claimed.store(0, std::memory_order_relaxed);
                update_completed.store(0, std::memory_order_relaxed);
                update_outstanding.store(task_quantity, std::memory_order_relaxed);
                break;
            case Phase::DRAW:
                draw_claimed.store(0, std::memory_order_relaxed);
                draw_completed.store(0, std::memory_order_relaxed);
                draw_outstanding.store(task_quantity, std::memory_order_relaxed);
                break;
            default:
                break;
        }
        if (task_quantity >= thread_quantity) {
            condition_variable.notify_all();
        } else {
            for (size_t i = 0; i < task_quantity; i++) {
                condition_variable.notify_one();
            }
        }
    }
}
