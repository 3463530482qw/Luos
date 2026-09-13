void update();   // 由 Draw::draw 调用
const std::vector<Vertex>& vertex() const;
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
Draw_line_cmd& solid(bool on = true);
Draw_line_cmd& connect(bool on = true);
Draw_line_cmd& end(bool on = true);
Draw_line_cmd& rotation(float radians, float center_x, float center_y);
