namespace Gnik_luos {
    uint64_t Thread::dispatch_locked(Phase next_phase, size_t task_quantity) {
        uint64_t gen = ++current_gen;
        phase.store(next_phase, std::memory_order_release);

        switch (next_phase) {
            case Phase::UPDATE:
                update_claimed.store(0, std::memory_order_relaxed);
                update_completed.store(0, std::memory_order_relaxed);
                update_quantity.store(task_quantity, std::memory_order_relaxed);
                update_done_gen = gen - 1;
                break;
            case Phase::DRAW:
                draw_claimed.store(0, std::memory_order_relaxed);
                draw_completed.store(0, std::memory_order_relaxed);
                draw_quantity.store(task_quantity, std::memory_order_relaxed);
                draw_done_gen = gen - 1;
                break;
            default:
                break;
        }

        condition_variable.notify_all();
        return gen;
    }
}
