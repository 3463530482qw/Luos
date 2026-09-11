namespace Gnik_luos {
    Thread::Thread() {
        auto haco = std::thread::hardware_concurrency();
        haco = haco <= 4 ? 4 : haco;
        thread_quantity = static_cast<uint16_t>(haco - 2);
        for (uint16_t i = 0; i < thread_quantity; i++) {
            thread_pool.emplace_back([this](std::stop_token stto) {
                while (!stto.stop_requested()) {
                    size_t task_index = 0;
                    uint32_t gen = 0;
                    {
                        std::unique_lock lock(mutex);
                        condition_variable.wait(lock, [this, &stto]() {
                            if (stto.stop_requested()) return true;
                            if (update_outstanding.load(std::memory_order_acquire) > 0 &&
                                update_claimed.load(std::memory_order_acquire) < update_tasks.size()) {
                                return true;
                            }
                            if (draw_outstanding.load(std::memory_order_acquire) > 0 &&
                                draw_claimed.load(std::memory_order_acquire) < draw_tasks.size()) {
                                return true;
                            }
                            return false;
                        });
                        if (stto.stop_requested()) return;
                        gen = current_gen;
                    }

                    Phase p = phase.load(std::memory_order_acquire);
                    bool worked = false;
                    if (p == Phase::UPDATE) {
                        task_index = update_claimed.fetch_add(1, std::memory_order_acq_rel);
                        if (task_index < update_tasks.size()) {
                            update_tasks[task_index]();
                            worked = true;
                        }
                    } else if (p == Phase::DRAW) {
                        task_index = draw_claimed.fetch_add(1, std::memory_order_acq_rel);
                        if (task_index < draw_tasks.size()) {
                            draw_tasks[task_index]();
                            worked = true;
                        }
                    }
                    if (!worked) continue;

                    if (p == Phase::UPDATE) {
                        size_t done = update_completed.fetch_add(1, std::memory_order_acq_rel) + 1;
                        if (done == update_tasks.size()) {
                            {
                                std::lock_guard lock(mutex);
                                update_outstanding.store(0, std::memory_order_release);
                                update_done_gen = gen;
                            }
                            condition_variable.notify_all();
                        }
                    } else if (p == Phase::DRAW) {
                        size_t done = draw_completed.fetch_add(1, std::memory_order_acq_rel) + 1;
                        if (done == draw_tasks.size()) {
                            {
                                std::lock_guard lock(mutex);
                                draw_outstanding.store(0, std::memory_order_release);
                                draw_done_gen = gen;
                            }
                            condition_variable.notify_all();
                        }
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
