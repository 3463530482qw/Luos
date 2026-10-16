int private_line_count() const;                    // \n 断出来的行数(至少一行)
float private_measure(const std::u32string& line) const;   // 一行的排版宽度(含字距)
float private_advance(char32_t codepoint) const;   // 一个码位的前进量:绑了字体取字形,没绑按字号推
float private_align_offset(float width) const;     // 这一行按对齐方式相对左上角要挪多少
void private_rotate();                             // 按三个角建旋转基
Vector3 private_rotate_vector(const Vector3& value, const Vector3& pivot) const;   // 绕旋转中心转一个点
void private_emit(const Glyph& glyph, float pen_x, float baseline, bool placeholder, float box_width, float box_height);   // 一个字形(或占位方块)摊成两个三角形
void private_layout();                             // 逐行逐字排:算位置、取字形、发顶点
