std::chrono::steady_clock::time_point start{};
double current{0};        
double before{0};            
double dt{0};  
double set_fps{0};
double frame_interval{1.0 / 60.0};
double smooth_alpha{0.15};
bool youk_smooth{false};
bool ema_smooth{false};
