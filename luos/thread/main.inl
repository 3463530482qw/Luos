namespace Gnik_luos {
    Thread::Thread() {
        auto haco = std::thread::hardware_concurrency();
        haco = haco <= 4 ? 4 : haco;
        thread_quantity = static_cast<uint16_t>(haco - 2);
        for (uint16_t i = 0; i < thread_quantity; i++) {
            thread_pool.emplace_back([this](std::stop_token stto) {
                std::function<void()> task;
                while (!stto.stop_requested()) {
                    {
                        std::unique_lock lock(mutex);
                        condition_variable.wait(lock, [this, &stto]() {
                            if (stto.stop_requested()) return true;
                            Phase p = phase.load(std::memory_order_acquire);
                            if (p == Phase::UPDATE) {
                                return update_claimed.load(std::memory_order_acquire) < update_quantity.load(std::memory_order_acquire);
                            }
                            if (p == Phase::DRAW) {
                                return draw_claimed.load(std::memory_order_acquire) < draw_quantity.load(std::memory_order_acquire);
                            }
                            return false;
                        });
                        if (stto.stop_requested()) return;

                        Phase p = phase.load(std::memory_order_acquire);
                        task = nullptr;
                        if (p == Phase::UPDATE) {
                            size_t task_index = update_claimed.fetch_add(1, std::memory_order_acq_rel);
                            if (task_index < private_update_snapshot.size()) {
                                task = std::move(private_update_snapshot[task_index]);
                            }
                        } else if (p == Phase::DRAW) {
                            size_t task_index = draw_claimed.fetch_add(1, std::memory_order_acq_rel);
                            if (task_index < private_draw_snapshot.size()) {
                                task = std::move(private_draw_snapshot[task_index]);
                            }
                        }
                        if (!task) continue;
                        active_workers.fetch_add(1, std::memory_order_acq_rel);
                    }

                    task();

                    {
                        std::lock_guard lock(mutex);
                        task = nullptr;
                        Phase p = phase.load(std::memory_order_acquire);
                        if (p == Phase::UPDATE) {
                            size_t done = update_completed.fetch_add(1, std::memory_order_acq_rel) + 1;
                            if (done == update_quantity.load(std::memory_order_acquire)) {
                                update_done_gen = current_gen;
                                phase.store(Phase::IDLE, std::memory_order_release);
                            }
                        } else if (p == Phase::DRAW) {
                            size_t done = draw_completed.fetch_add(1, std::memory_order_acq_rel) + 1;
                            if (done == draw_quantity.load(std::memory_order_acquire)) {
                                draw_done_gen = current_gen;
                                phase.store(Phase::IDLE, std::memory_order_release);
                            }
                        }
                        active_workers.fetch_sub(1, std::memory_order_acq_rel);
                        condition_variable.notify_all();
                    }
                }
            });
        }
    }

    Thread::~Thread() {
        wait();
        for (uint16_t i = 0; i < thread_quantity; i++) {
            thread_pool[i].request_stop();
        }
        condition_variable.notify_all();
        for (uint16_t i = 0; i < thread_quantity; i++) {
            if (thread_pool[i].joinable()) {
                thread_pool[i].join();
            }
        }
    }
}
