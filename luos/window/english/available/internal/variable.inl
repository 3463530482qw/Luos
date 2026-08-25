std::vector<SDL_DisplayID> displays;
const SDL_DisplayMode* mode{nullptr};
float aspectratio{0};
SDL_WindowID wid{0};
SDL_Event pre_event_ptr;                       // 窗口事件
std::vector<SDL_Event> pre_event;