void update();   // 检查脏标记:脏了就重新装配路由并重算顶点
const std::vector<Vertex>& vertex() const;
// 链式设置:返回自身,参数落定后由下一轮 Draw::draw 重算
Line& from(float x, float y, float z);
Line& to(float x, float y, float z);
Line& size(float x_value, float y_value);
Line& rotation_point(float x, float y, float z);
Line& rotation(float x, float y, float z);
Line& rgba(uint8_t red, uint8_t green, uint8_t blue, float alpha = 1.0f);
