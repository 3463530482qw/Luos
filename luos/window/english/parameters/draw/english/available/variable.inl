std::deque<std::variant<Line, Picture, Text, Tilemap>> commands{};   // 本帧的绘制命令:登记序即绘制序,draw 铺完即清
