uint64_t dispatch_locked(Phase next_phase, size_t task_quantity);
void wait_update(uint64_t gen);
void wait_draw(uint64_t gen);
Thread& wait();
