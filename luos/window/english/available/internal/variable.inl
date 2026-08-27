std::vector<SDL_DisplayID> displays;
const SDL_DisplayMode* mode{nullptr};
float aspectratio{0};
SDL_WindowID window_id{0};
SDL_Event pre_event_ptr;                       // 窗口事件
std::vector<SDL_Event> pre_event;
float re_aspectratio{1.0f};
int cut_offset_width{0};
int cut_offset_height{0};