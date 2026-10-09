namespace Gnik_luos {
    Line& Line::from(float x, float y, float z) {
        x1 = x;
        y1 = y;
        z1 = z;
        to_point.clear();   // 起点重设即重开一条折线:旧终点挂在旧起点后面,留着就是另一条路径
        dirty = true;
        return *this;
    }
}
