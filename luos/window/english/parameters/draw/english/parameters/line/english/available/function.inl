void update();   // 检查脏标记:脏了就重新装配路由并重算顶点
const std::vector<Vertex>& vertex() const;
const std::vector<double>& segment_length() const;   // 逐段长度:渲染侧靠它算每段每面那些贴图块的尺寸
const std::vector<uint8_t>& face_mask() const;   // 逐段留下哪几个面:连接处那两个端面不在里面
Line& batch_load(const simdjson::dom::element& json, std::string_view type);   // 读命名的段当一条线:to 给一组是一段,给多组(重复键或数组)是多点折线
// 链式设置:返回自身,参数落定后由下一轮 Draw::draw 重算
Line& from(float x, float y, float z);
Line& to(float x, float y, float z);   // 追加一个终点:每多一个终点多一段
Line& size(float x_value, float y_value);
Line& rotation_point(float x, float y, float z);
Line& rotation(float x, float y, float z);
Line& rgba(uint8_t red, uint8_t green, uint8_t blue, float alpha = 1.0f);
Line& texture(bool value);   // 走不走贴图;false 时路径不参与
Line& texture(const std::string& path);   // 指定贴图文件夹(里面每段每面一块,名字 段号_面名)
Line& texture(const Information_image& image);   // 直接拿已经加载好的像素当贴图:所有块共用这一张
Line& seal(bool value);   // 封不封边:true 时把折线首尾接上,成一条闭合图形
