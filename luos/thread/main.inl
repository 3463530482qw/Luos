namespace Gnik_luos {
    Thread::Thread() {
        auto haco = std::thread::hardware_concurrency();
        haco = haco <= 4 ? 4 : haco;
        thread_quantity = static_cast<uint16_t>(haco - 2);
        for (uint16_t i = 0; i < thread_quantity; i++) {
            thread_pool.emplace_back([this](std::stop_token stto) {
                while (!stto.stop_requested()) {
                    {
                        std::unique_lock lock(mutex);
                        condition_variable.wait(lock, [&]() {
                            if(stto.stop_requested()) return true;
                            Phase p = phase.load(std::memory_order_acquire);
                            switch (p) {
                                case Phase::UPDATE:
                                    return update_claimed.load(std::memory_order_acquire) < update_tasks.size();
                                case Phase::DRAW:
                                    return draw_claimed.load(std::memory_order_acquire) < draw_tasks.size();
                                default:
                                    return false;
                            }
                        });
                    }
                    if(stto.stop_requested()) return;
                    Phase p = phase.load(std::memory_order_acquire);

                    switch (p) {
                        case Phase::UPDATE:
                            {
                                size_t i = update_claimed.fetch_add(1, std::memory_order_acq_rel);
                                if (i < update_tasks.size()) {
                                    update_tasks[i]();
                                    size_t done = update_completed.fetch_add(1, std::memory_order_acq_rel) + 1;
                                    if (done == update_tasks.size()) {
                                        {
                                            std::lock_guard lk(mutex);
                                            update_done.store(true, std::memory_order_release);
                                        }
                                        condition_variable.notify_all();
                                    }
                                }
                                break;
                            }
                        case Phase::DRAW:
                            {
                                size_t i = draw_claimed.fetch_add(1, std::memory_order_acq_rel);
                                if (i < draw_tasks.size()) {
                                    draw_tasks[i]();
                                    size_t done = draw_completed.fetch_add(1, std::memory_order_acq_rel) + 1;
                                    if (done == draw_tasks.size()) {
                                        {
                                            std::lock_guard lk(mutex);
                                            draw_done.store(true, std::memory_order_release);
                                        }
                                        condition_variable.notify_all();
                                    }
                                }
                            }
                        default: break;
                    }
                }
            });
        }
    }
}