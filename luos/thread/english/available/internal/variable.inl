uint16_t thread_quantity;
std::vector<std::jthread> thread_pool;
std::mutex mutex;
std::condition_variable condition_variable;
std::atomic<Phase> phase{Phase::IDLE};

std::vector<std::function<void()>> update_tasks;
std::vector<std::function<void()>> draw_tasks;

std::atomic<size_t> update_claimed{0};
std::atomic<size_t> draw_claimed{0};
std::atomic<size_t> update_completed{0};
std::atomic<size_t> draw_completed{0};

std::atomic<size_t> update_outstanding{0};
std::atomic<size_t> draw_outstanding{0};

uint64_t current_gen{0};
uint64_t update_done_gen{0};
uint64_t draw_done_gen{0};
