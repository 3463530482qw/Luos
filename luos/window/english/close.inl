namespace Gnik_luos {
    Window& Window::close() {
        isrun = false;               
        run();                   
        if (id) {
            SDL_DestroyWindow(id); 
            id = nullptr;
        }
        return *this;
    }
}