void update();   // 检查脏标记:脏了就重新装配路由并重算顶点
const std::vector<Vertex>& vertex() const;
double length() const;   // 展开图的宽 = 去重后各列宽之和(同一路径里取最长的那条命令来展开)
const std::vector<double>& layout_column() const;   // 展开图的列 = 去重后的段长:同长的段共用一列
Line& batch_load(const simdjson::dom::element& json, std::string_view type);   // 读命名的段当一条线:to 给一组是一段,给多组(重复键或数组)是多点折线
// 链式设置:返回自身,参数落定后由下一轮 Draw::draw 重算
Line& from(float x, float y, float z);
Line& to(float x, float y, float z);   // 追加一个终点:每多一个终点多一段
Line& size(float x_value, float y_value);
Line& rotation_point(float x, float y, float z);
Line& rotation(float x, float y, float z);
Line& rgba(uint8_t red, uint8_t green, uint8_t blue, float alpha = 1.0f);
Line& texture(bool value);   // 走不走贴图;false 时路径不参与
Line& texture(const std::string& path);   // 指定图片路径并顺带打开贴图(空串 = 库内那张纯色)
