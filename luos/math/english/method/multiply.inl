namespace Gnik_luos {
    // 列主序 4x4 相乘:返回 left * right(右乘那个先施加到顶点上)
    // 注意:存储是 column * 4 + row,与数学上的 A[row][col] 成转置关系,
    // 所以这里的取元素写法看着"反",实际算的就是 left × right(已用独立参照实现逐元素核对)
    Matrix4 multiply(const Matrix4& left, const Matrix4& right) {
        Matrix4 product;
        for (int column = 0; column < 4; column++) {
            for (int row = 0; row < 4; row++) {
                double sum = 0.0;
                for (int index = 0; index < 4; index++) {
                    sum += left.m[index * 4 + row] * right.m[column * 4 + index];
                }
                product.m[column * 4 + row] = sum;
            }
        }
        return product;
    }
}
