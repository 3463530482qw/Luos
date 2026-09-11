void dispatch(Phase next_phase, size_t task_quantity, uint32_t gen);
void wait_update(uint32_t gen);
void wait_draw(uint32_t gen);
Thread& wait();
