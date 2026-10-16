Font* face{nullptr};   // 绑定的字体(不持有:字体归应用或字体仓库养);空 = 没绑字体,改用默认字形贴图
std::string content{};   // 要画的文字(utf8):\n 断行,空串不出顶点
float x1{0.0f}, y1{0.0f}, z1{0.0f};   // 文字块左上角(世界坐标);z 由它给,文字块整个落在这个 z 上
float font_size{16.0f};   // 字号(像素高):按它烤字形/排方块,按它排版
float letter_spacing{0.0f};   // 字距:每个字形前进之后再加的像素
float line_height{0.0f};   // 行高:<= 0 就按字体自己的行高(没绑字体时按字号)
int align_mode{0};   // 对齐:0 左,1 中,2 右
float rotation_x{0.0f}, rotation_y{0.0f}, rotation_z{0.0f};                     // 旋转角(度,依次绕 x、y、z)
float rotation_point_x{0.0f}, rotation_point_y{0.0f}, rotation_point_z{0.0f};   // 旋转中心(世界坐标,默认原点)
uint8_t r{255}, g{255}, b{255};   // 字色(0~255)
float a{1.0f};                    // 字透明度(0~1)
bool dirty{true};                       // 参数改过就要重算顶点
std::vector<Vertex> cache{};            // 本命令的顶点(逐字形一组 6 个)
std::string texture_key{};   // 这次排版用的贴图槽位键(排完版就定死,绘制侧只搬运)
Information_image texture_pixels{};   // 这份键对应的像素(字体图集,或没绑字体时的默认字形贴图)
uint64_t texture_revision{0};   // 这次用的图集内容版本:字体那边改了就得重排
