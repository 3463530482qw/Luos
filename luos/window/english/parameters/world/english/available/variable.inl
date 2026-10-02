// 世界量的落点(库里不搬动它们,由使用侧按需读写):
World_point point{};        // 当前关注的世界点(相机站位、拾取结果都能放这里)
World_ray ray{};            // 屏幕反投影出来的射线
Canvas_rect canvas_rect{};  // 相机取景的世界矩形(画布口径,默认在 z = 0 平面)
Ground_hit hit{};           // 最近一次射线求交的结果(valid = false 时无意义)
