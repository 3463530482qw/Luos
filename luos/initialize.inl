namespace luos {
    void initialize() {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            throw std::runtime_error(std::string("SDL Video子系统失败: ") + SDL_GetError());
        }
    }
}