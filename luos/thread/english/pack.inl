namespace Gnik_luos {
    Thread& Thread::update_pack(std::function<void()> lambda_task) {
        update_tasks.push_back(std::move(lambda_task));
        return *this;
    }
    Thread& Thread::draw_pack(std::function<void()> lambda_task) {
        draw_tasks.push_back(std::move(lambda_task));
        return *this;
    }
}