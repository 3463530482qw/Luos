namespace Gnik_luos {
    void Run::start() {
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
    }
}
