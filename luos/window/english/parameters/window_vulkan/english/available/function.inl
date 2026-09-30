void init(Vulkan& vulkan_engine);
void update_viewport();   // 按宿主窗口当前尺寸与画布比例重算视口
void request_rebuild();
void draw_frame();
void destroy();
double viewport_origin_x() const;   // 视口(窗口内接矩形)在原窗口里的左偏移(灰边宽度)
double viewport_origin_y() const;   // 视口在原窗口里的上偏移(灰边高度)
