namespace Gnik_luos {
    Window& Window::run() {
        for(auto& fun : private_run) {
            fun();
        }      
        return *this;
    }
}
