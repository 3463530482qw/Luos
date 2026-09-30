Draw& bind_vertex_sink(std::vector<Vertex>& sink);   // 顶点去处:绘制出的顶点追加到这里
Draw& set_view(const Rect& view);   // 每帧把相机的可见矩形交进来:外部填充按它留洞
void draw(Draw_line_cmd& cmd);   // 里面先检查更新标志,然后更新顶点
