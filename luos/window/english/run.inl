namespace Gnik_luos {
    Window& Window::run() {
        time.update();
        while (SDL_PollEvent(&pre_event_ptr)) {
            if (pre_event_ptr.window.windowID != 0 && pre_event_ptr.window.windowID != wid) {
                pre_event.push_back(pre_event_ptr);
                continue;
            }
            switch (pre_event_ptr.type) {
                case SDL_EVENT_QUIT:
                    isrun = false;
                    break;
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                    isrun = false;
                    break;
                default:
                    break;
            }
            
        }
        for (auto& e : pre_event) {  
            SDL_PushEvent(&e);
        }
        pre_event.clear();
        return *this;
    }
}