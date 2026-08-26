Scene* private_scene{nullptr};
Thread* private_thread{nullptr};
std::unordered_map<std::string, Window*> private_window;
bool* isrun;
std::function<void()> private_start;