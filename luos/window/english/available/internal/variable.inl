std::vector<SDL_DisplayID> displays;
const SDL_DisplayMode* mode{nullptr};
float aspectratio{0};
SDL_WindowID window_id{0};
SDL_Event pre_event_ptr;                       // 窗口事件
std::vector<SDL_Event> pre_event;
float logic_aspectratio{0};
uint16_t cut_offset_width{0};
uint16_t cut_offset_height{0};