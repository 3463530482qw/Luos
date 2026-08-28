namespace Gnik_luos {
    Window& Window::run() {
        time.update();
        while (SDL_PollEvent(&pre_event_ptr)) {
            if (pre_event_ptr.window.windowID != 0 && pre_event_ptr.window.windowID != window_id) {
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
                case SDL_EVENT_MOUSE_MOTION:
                    mouse_update(pre_event_ptr.motion.x, pre_event_ptr.motion.y); 
                    break;
                case 0x8000:
                    SDL_SetWindowIcon(id, static_cast<SDL_Surface*>(pre_event_ptr.user.data1));
                    SDL_DestroySurface(static_cast<SDL_Surface*>(pre_event_ptr.user.data1));
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