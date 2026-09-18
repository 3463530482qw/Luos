namespace Gnik_luos {
    void Window::router() {
        private_run.clear();
        if (is_time) {
            private_run.push_back([&]() { time.update(); });
        }
        if (is_vulkan) {
            if (window_vulkan.initialized) {
                private_run.push_back([&]() { window_vulkan.draw_frame(); });
            } else {
                throw std::runtime_error(std::string("Window::router => Vulkan not initialized"));
            }
        }
        private_run.push_back([&]() { event_handling(); });
        if (is_key) {
            private_run.push_back([&]() { key.update(); });
        }
    }
}
