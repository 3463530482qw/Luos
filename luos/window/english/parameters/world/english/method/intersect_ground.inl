namespace Gnik_luos {
    // 射线 × 地面(y = 0 平面)求交:方向朝上、与地面平行、交点在射线身后这三种情况
    // 都给不出有效交点,统一返回 (0, 0, 0) 并置 valid = false,不静默给一个看着像答案的点
    Ground_hit World::intersect_ground(const World_ray& ray) {
        Ground_hit hit;
        if (ray.direction.y == 0.0) {
            return hit;   // 与地面平行
        }
        const double distance = -ray.origin.y / ray.direction.y;
        if (distance < 0.0) {
            return hit;   // 交点在射线身后
        }
        hit.point.position.x = ray.origin.x + ray.direction.x * distance;
        hit.point.position.y = 0.0;
        hit.point.position.z = ray.origin.z + ray.direction.z * distance;
        hit.valid = true;
        return hit;
    }
}
