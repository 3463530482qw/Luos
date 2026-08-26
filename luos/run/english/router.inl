namespace Gnik_luos {
    void Run::router() {
        private_start = [this]() {
            if (private_scene == nullptr) {
                std::runtime_error(std::string("Run::start => Need specify scene"));
            }
            if (private_thread == nullptr) {
                std::runtime_error(std::string("Run::start => Need specify thread"));
            }
            if (private_window.empty()) {
                std::runtime_error(std::string("Run::start => Need specify window"));
            }
            private_start = [this]() {
                while(isrun) {
                    if (private_scene->goal_scene != private_scene->current_scene) {
                        private_scene->current_scene = private_scene->goal_scene;
                        break;
                    }
                    private_thread->run();
                    for (auto it = private_window.begin(); it != private_window.end(); ++it) {
                        it->second->run();
                    }
                }
            };
        };
    }
}