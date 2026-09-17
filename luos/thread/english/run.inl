namespace Gnik_luos {
    void Thread::run() {
        uint64_t update_gen = 0;
        uint64_t draw_gen = 0;
        {
            std::lock_guard lock(mutex);
            private_update_snapshot = update_tasks;
            if (!private_update_snapshot.empty()) {
                update_gen = dispatch_locked(Phase::UPDATE, private_update_snapshot.size());
            }
        }
        if (update_gen != 0) {
            wait_update(update_gen);
        }

        {
            std::lock_guard lock(mutex);
            private_draw_snapshot = draw_tasks;
            if (!private_draw_snapshot.empty()) {
                draw_gen = dispatch_locked(Phase::DRAW, private_draw_snapshot.size());
            }
        }
        if (draw_gen != 0) {
            wait_draw(draw_gen);
        }
    }
}
