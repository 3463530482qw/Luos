Thread& 更新包(std::function<void()> lambda_task) { return update_pack(lambda_task); };
Thread& 绘制包(std::function<void()> lambda_task) { return draw_pack(lambda_task); }
void 运行() { run(); };
void 清空() { clear(); }