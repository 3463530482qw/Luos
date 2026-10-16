void update();   // 检查脏标记:脏了就按两个对角重算这张四边形的六个顶点
const std::vector<Vertex>& vertex() const;
Picture& batch_load(const simdjson::dom::element& json, std::string_view type);   // 读命名的段当一张图:data 两个点是这张图的对角
// 链式设置:返回自身,参数落定后由下一轮 Draw::draw 重算
Picture& from(float x, float y, float z);   // 左上角
Picture& to(float x, float y, float z);     // 对角
Picture& rotation_point(float x, float y, float z);
Picture& rotation(float x, float y, float z);
Picture& rgba(uint8_t red, uint8_t green, uint8_t blue, float alpha = 1.0f);   // 四角同色
Picture& corner_rgba(size_t corner, uint8_t red, uint8_t green, uint8_t blue, float alpha = 1.0f);   // 单改一个角
Picture& texture(bool value);   // 走不走贴图;false 时只走四角 rgba
Picture& texture(const std::string& path);   // 一张图片文件(缺图按这张图的尺寸生成提示图)
Picture& texture(const Information_image& image);   // 直接拿已经加载好的像素当贴图
