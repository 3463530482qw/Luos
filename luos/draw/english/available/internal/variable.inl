Rect private_view{};                                 // 本帧的可见矩形,由相机每帧交过来
std::vector<Vertex>* private_vertex_sink{nullptr};   // 顶点去处,由 bind_window 接上
size_t private_fill_head{0};                         // 本帧已经铺在列表头部的填充顶点数
