namespace Gnik_luos {
    Line& Line::to(float x, float y, float z) {
        to_point.push_back(Vector3{x, y, z});   // 追加终点:调一次一段,折线就是连着调
        dirty = true;
        return *this;
    }
}
