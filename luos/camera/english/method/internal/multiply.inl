namespace Gnik_luos {
    // 列主序 4x4 相乘:left * right(右乘那个先施加到顶点上)
    Matrix4 Camera::private_multiply(const Matrix4& left, const Matrix4& right) const {
        Matrix4 product;
        for (int column = 0; column < 4; column++) {
            for (int row = 0; row < 4; row++) {
                float sum = 0.0f;
                for (int index = 0; index < 4; index++) {
                    sum += left.m[index * 4 + row] * right.m[column * 4 + index];
                }
                product.m[column * 4 + row] = sum;
            }
        }
        return product;
    }
}
