void update();   // 检查脏标记:脏了就按文字重排一遍(字形没烤过会现烤,贴图键与像素也在这一步定死)
const std::vector<Vertex>& vertex() const;
Text& font(Font& face_value);   // 绑定字体
Text& texture(const std::string& path);   // 没绑字体时改用的贴图路径(空 = 库内那张默认字形贴图)
Text& batch_load(const simdjson::dom::element& json, std::string_view type);   // 读命名的段当一条文字命令
// 链式设置:返回自身,参数落定后由下一轮 Draw::draw 重算
Text& from(float x, float y, float z);   // 文字块左上角
Text& text(const std::string& value);    // 要画的文字(utf8,\n 断行)
Text& size(float pixel_height, float line_spacing = 0.0f);   // 字号(像素高)与行高(<= 0 按字体自己的行高)
Text& spacing(float letter_gap);         // 字距(像素)
Text& align(const std::string& value);   // 对齐:left / center / right,别的写法当没写
Text& rotation_point(float x, float y, float z);
Text& rotation(float x, float y, float z);
Text& rgba(uint8_t red, uint8_t green, uint8_t blue, float alpha = 1.0f);
