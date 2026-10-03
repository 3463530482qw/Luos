std::deque<Line> keep_lines{};      // 常驻命令:包外注册一次(不动的线),每帧照旧铺顶点,draw 不清它
std::deque<Line> frame_lines{};     // 当帧命令:包内每帧登记(要调整的线),draw 铺完即清
