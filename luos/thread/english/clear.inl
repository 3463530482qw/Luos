namespace Gnik_luos {
    void Thread::clear() {
        wait();
        std::lock_guard lock(mutex);
        update_tasks.clear();
        draw_tasks.clear();
        phase.store(Phase::IDLE, std::memory_order_release);
    }
}
