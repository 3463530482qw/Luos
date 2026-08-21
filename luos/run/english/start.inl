namespace Gnik_luos {
    void Run::start() {
        while(1) {
            if (private_scene->goal_scene != private_scene->current_scene) {
                private_scene->current_scene = private_scene->goal_scene;
                break;
            }
            private_thread->run();
        }
    }
}
