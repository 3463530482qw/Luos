// 世界空间约定(全库只此一份,别处引用这里):
//   - 右手 3D 空间,y 向下(与画布口径、着色器一致),单位就是世界单位,不是设备像素
//   - 地面是 y = 0 平面;画布是 z = 0 平面上的一块矩形,相机显示范围就是它
//   - 相机位置为默认 (0,0,0) 时,画布矩形的左下角贴世界原点
//   - 旋转按度;三个旋转都为 0 时相机看向 -z
//   - 世界量一律 double;只在出顶点与写 GPU 推常量时才收窄成 float
// 正交与透视只是同一套 3D 数据的两种取景,数据本身不随档位改变。
#include "english/parameters/world_point.inl"
#include "english/parameters/canvas_rect.inl"
#include "english/parameters/world_ray.inl"
#include "english/parameters/ground_hit.inl"
#include "english/method/intersect_ground.inl"
