std::string texture_key{};      // 瓦片图集路径(整层共用这一张)
Sprite_sheet sprite_sheet{};    // 图集怎么切
int columns{32};                // 地图列数
int rows{32};                   // 地图行数
std::vector<int> tile{};        // 逐格图号(行主序:索引 = 行 * columns + 列);空 = 这一层没内容
float origin_x{0.0f}, origin_y{0.0f};   // 地图世界原点:第一格左上角(世界 y 是向上的,行随 y 递减)
float tile_size{16.0f};         // 一个瓦片在世界里的边长
int view_x{0}, view_y{0};       // 视野左上角(格)
int view_columns{0}, view_rows{0};   // 视野格数:0 = 不管视野,整层都出顶点
uint8_t r{255}, g{255}, b{255};   // 顶点色(整层同一个色,染色用)
float a{1.0f};
bool dirty{true};               // 参数改过就要重算顶点
std::vector<Vertex> cache{};    // 本命令的顶点(可见格一格格摊成四边形)
