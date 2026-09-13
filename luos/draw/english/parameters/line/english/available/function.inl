void update();   // 由 Draw::draw 调用
const std::vector<Vertex>& vertex() const;
const std::vector<Vertex>& fill_vertex() const;   // 填充单独一层,由 Draw::draw 排在全部线条之前
// 链式设置:返回自身并置更新标志
Draw_line_cmd& from(float x, float y);
Draw_line_cmd& to(float x, float y);
Draw_line_cmd& line_width(float width);
Draw_line_cmd& color(uint8_t red, uint8_t green, uint8_t blue, float alpha = 1.0f);
Draw_line_cmd& gradient(
    uint8_t start_red, uint8_t start_green, uint8_t start_blue,
    uint8_t end_red, uint8_t end_green, uint8_t end_blue,
    float start_alpha = 1.0f, float end_alpha = 1.0f
);
Draw_line_cmd& dash(float length, float gap);
Draw_line_cmd& pixelate(float size);   // 打开像素化并给出方块边长;size <= 0 视为关闭
Draw_line_cmd& solid(bool on = true);
Draw_line_cmd& connect(bool on = true);
Draw_line_cmd& fill_inside(uint8_t red, uint8_t green, uint8_t blue, float alpha = 1.0f);
Draw_line_cmd& fill_outside(uint8_t red, uint8_t green, uint8_t blue, float alpha = 1.0f);
Draw_line_cmd& fill_above(bool on = true);   // 填充改到线条之上
Draw_line_cmd& end(bool on = true);
Draw_line_cmd& edge_rect(bool on = true);      // 端头平切(现在的做法)
Draw_line_cmd& edge_top(float size);           // 封边:上
Draw_line_cmd& edge_middle(float size);        // 封边:中
Draw_line_cmd& edge_bottom(float size);        // 封边:下
Draw_line_cmd& edge_both(float size);          // 封边:上下一块(三角形负形)
Draw_line_cmd& edge_round(float size);         // 封边:半圆正形(直径 = size)
Draw_line_cmd& edge_round_notch(float size);   // 封边:半圆负形
Draw_line_cmd& smooth(float value);            // 拐点圆滑度 0~1
Draw_line_cmd& rotation(float radians, float center_x, float center_y);
