std::string name{};                        // 字体文件路径:图集身份与报错都用它
std::vector<unsigned char> file_data{};    // ttf 字节:stb_truetype 的解析结果一直指着它,不能被搬走
bool ready{false};                         // 解析成功才认这份字体
stbtt_fontinfo font_info{};
std::map<double, std::shared_ptr<Atlas_info>> atlas_map{};   // 逐字号一张图集
int ascent_metric{0}, descent_metric{0}, line_gap_metric{0};   // 字体自己的度量(未缩放:乘缩放系数得像素)
