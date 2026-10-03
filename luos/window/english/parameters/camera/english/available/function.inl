Camera& apply(const Window_settings_info& settings);   // 按窗口配置里的相机段设一次取景(没写就保持默认)
Camera& apply_default();   // 默认站位:画布中心正前方,距离让画布与逻辑窗口一一对应
void canvas_clip_matrix(float* out) const;   // 世界 → 裁剪:画布口径就是逻辑窗口,画布四角即视口四角
Canvas_rect canvas_rect() const;   // 我的取景范围:世界矩形(默认位置时左下角贴世界原点)
Rect rect() const;                  // 取景范围在当前朝向下覆盖到的世界 AABB,交给绘制器用
Matrix4 view_matrix() const;        // 世界 → 视图空间(3D:相机位置 + 三个基)
Matrix4 projection_view_space() const;   // 视图空间 → 裁剪空间(正交档的取景框就长在视图空间里)
Matrix4 view_projection() const;    // view_matrix × projection_view_space:世界 → 裁剪空间
World_ray ray_through_screen(double screen_x, double screen_y, double screen_width, double screen_height) const;   // 屏幕点 → 世界射线
Vector3 world_from_screen(double screen_x, double screen_y, double screen_width, double screen_height) const;      // 屏幕点 → 世界点(透视档取地面交点)
Vector3 canvas_from_screen(double screen_x, double screen_y, double screen_width, double screen_height) const;    // 屏幕点 → 画布上的世界点(夹在画布内)
Vector3 canvas_uv(const Vector3& world) const;   // 世界点 → 画布内的归一化坐标(0~1,越界给到界外)
