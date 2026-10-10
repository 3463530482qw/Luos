std::vector<Vertex>* private_vertex_sink{nullptr};   // 顶点去向,由线条渲染器接上
std::vector<Line_span>* private_span_sink{nullptr};  // 分段表去向:每条命令占的区间与它要的贴图,同样由线条渲染器接上
