vk::Extent2D frame_extent{0, 0};   // 交换链帧尺寸(着色器像素吸附用)
uint32_t vertex_frame{0};          // 当前写入哪块顶点缓冲
uint32_t vertex_count{0};          // 本帧待绘制的顶点数(0 = 本帧无线条)
size_t vertex_capacity{0};         // 顶点缓冲字节容量
static constexpr size_t vertex_buffer_bytes{1024 * 1024};   // 顶点缓冲预分配 1MB,顶点多了按需扩容
