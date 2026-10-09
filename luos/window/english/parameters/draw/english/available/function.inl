Draw& bind_vertex_sink(std::vector<Vertex>& sink);   // 顶点去向:由线条渲染器在接线时接上
Line& line();   // 登记一条空命令(当帧内自己设参数),draw 铺完即清
Line& line(const Line& source);   // 按一条已经加载好的线登记命令,draw 铺完即清
void draw();    // 检查命令表里的脏标记,只重算脏的,按登记序追加顶点
