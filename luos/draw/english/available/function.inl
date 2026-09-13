void draw(Draw_line_cmd& cmd);   // 里面先检查更新标志,然后更新顶点
Draw& bind_window(Window& window);   // 接上窗口后,画出的顶点直接进那个窗口的帧顶点表
