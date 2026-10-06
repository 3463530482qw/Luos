namespace Gnik_luos {
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
