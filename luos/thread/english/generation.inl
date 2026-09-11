namespace Gnik_luos {
    void Thread::wait_update(uint32_t gen) {
        std::unique_lock lock(mutex);
        condition_variable.wait(lock, [this, gen]() {
            return update_done_gen >= gen;
        });
    }

    void Thread::wait_draw(uint32_t gen) {
        std::unique_lock lock(mutex);
        condition_variable.wait(lock, [this, gen]() {
            return draw_done_gen >= gen;
        });
    }
}
