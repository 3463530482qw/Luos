uint32_t width{0};    // 视口(窗口内的内接矩形)尺寸
uint32_t height{0};
int32_t cut_offset_width{0};    // 视口在原窗口里的偏移 = 四周灰边的一半
int32_t cut_offset_height{0};
float logic_aspectratio{1.0f};  // 视口像素 / 画布像素:鼠标换算要用
