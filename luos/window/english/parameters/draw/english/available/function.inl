Draw& bind_vertex_sink(std::vector<Vertex>& sink);   // 顶点去向:由线条渲染器在接线时接上
Line& line();   // 当帧登记:包内每帧调用(要调整的线),draw 铺完即清
Line& keep();   // 常驻登记:包外调用一次(不动的线),之后每帧照旧铺顶点
void draw();    // 检查两条命令表里的脏标记,只重算脏的,按常驻在前、当帧在后追加顶点
