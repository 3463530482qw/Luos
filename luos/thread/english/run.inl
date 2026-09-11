namespace Gnik_luos {
    void Thread::run() {
        uint32_t gen = current_gen + 1;

        if (!update_tasks.empty()) {
            dispatch(Phase::UPDATE, update_tasks.size(), gen);
            wait_update(gen);
        } else {
            std::lock_guard lock(mutex);
            update_done_gen = gen;
        }

        if (!draw_tasks.empty()) {
            dispatch(Phase::DRAW, draw_tasks.size(), gen);
            wait_draw(gen);
        } else {
            std::lock_guard lock(mutex);
            draw_done_gen = gen;
        }
    }
}
