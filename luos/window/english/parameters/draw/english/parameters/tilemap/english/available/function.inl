Tilemap& texture(const std::string& path);   // 瓦片图集:给路径
Tilemap& texture(const Information_image& image);   // 直接给已经加载好的像素
Tilemap& sheet(int columns, int rows);   // 图集按 columns × rows 切格(行主序)
Tilemap& grid(int columns, int rows);    // 地图多大(格数)
Tilemap& map(const std::vector<int>& tile);   // 逐格图号(行主序);空表 = 这一层没内容
Tilemap& origin(float x, float y);       // 地图世界原点(第一格左上角)
Tilemap& size(float tile_size);          // 一个瓦片在世界里的边长(默认 16)
Tilemap& view(int left, int top, int columns, int rows);   // 只出视野内那些格(按地图格算)
Tilemap& at(size_t index, int tile);     // 单改一格(改完自动标脏)
Tilemap& rgba(uint8_t red, uint8_t green, uint8_t blue, float alpha = 1.0f);
void update();   // 检查脏标记:脏了就按视野与地图重算顶点
const std::vector<Vertex>& vertex() const;
