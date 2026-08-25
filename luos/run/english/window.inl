namespace Gnik_luos {
    void Run::specify_window(Window& window) {
        if(private_window.empty()) {
            isrun = &window.isrun;
        }
        
        private_window[window.name] = &window;
    }

    void Run::specify_remove_window(Window& window) {
        private_window.erase(window.name);
    }
}
