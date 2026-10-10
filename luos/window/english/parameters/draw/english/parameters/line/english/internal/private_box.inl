namespace Gnik_luos {
    // 八个角:两端各四个,截面沿局部 x/y 各摊半个几何值;六个面各拆两个三角形
    void Line::private_box(size_t offset) {
        const double half_x = size_x * 0.5;
        const double half_y = size_y * 0.5;
        const double side_scale[4]{-half_x, half_x, half_x, -half_x};
        const double up_scale[4]{-half_y, -half_y, half_y, half_y};
        const Vector3 end[2]{private_start, private_end};
        Vector3 corner[2][4];
        for (int index = 0; index < 2; index++) {
            for (int quadrant = 0; quadrant < 4; quadrant++) {
                const double side = side_scale[quadrant];
                const double up = up_scale[quadrant];
                corner[index][quadrant] = Vector3{
                    end[index].x + private_side.x * side + private_up.x * up,
                    end[index].y + private_side.y * side + private_up.y * up,
                    end[index].z + private_side.z * side + private_up.z * up
                };
            }
        }

        // 面表:六行是六个面,每行四个角(先端号 0 起 1 终,再截面象限)
        // 绕序按右手定则朝外:叉积 = 该面的外法线 —— 管线开背面剔除以后,背对相机的面正好被剔掉
        const int face[6][4][2]{
            {{0, 0}, {0, 3}, {0, 2}, {0, 1}},
            {{1, 0}, {1, 1}, {1, 2}, {1, 3}},
            {{0, 2}, {1, 2}, {1, 1}, {0, 1}},
            {{0, 0}, {1, 0}, {1, 3}, {0, 3}},
            {{0, 3}, {1, 3}, {1, 2}, {0, 2}},
            {{0, 1}, {1, 1}, {1, 0}, {0, 0}}
        };
        // 展开图:六个面各占一行、按真实尺寸竖排(起端面 / +x / -x / +y / -y / 终端面),坐标一律世界单位
        // 行高:+x 与 -x 面跨局部 y(size_y),+y 与 -y 面跨局部 x(size_x),端面跨两个方向(按 size_y 取高)
        const int face_row[6]{0, 5, 1, 2, 3, 4};   // 面表 6 行 → 展开图的行号
        const double row_height[6]{size_y, size_y, size_y, size_x, size_x, size_y};
        const double row_v[6]{
            0.0,
            row_height[0],
            row_height[0] + row_height[1],
            row_height[0] + row_height[1] + row_height[2],
            row_height[0] + row_height[1] + row_height[2] + row_height[3],
            row_height[0] + row_height[1] + row_height[2] + row_height[3] + row_height[4]
        };
        const bool row_height_is_y[6]{true, true, true, false, false, true};   // 行内高向取局部 y 还是局部 x
        const bool row_u_is_arc[6]{false, true, true, true, true, false};      // u 取弧长(侧面)还是面内局部 x(端面)

        const int triangle[6]{0, 1, 2, 0, 2, 3};
        const float progress[2]{static_cast<float>(private_u0), static_cast<float>(private_u1)};
        size_t target = offset;   // 这一段在折线顶点表里的落点
        for (int index = 0; index < 6; index++) {
            const int row = face_row[index];
            for (int step = 0; step < 6; step++) {
                const int* point = face[index][triangle[step]];
                const Vector3& position = corner[point[0]][point[1]];
                const double side = side_scale[point[1]] + half_x;
                const double up = up_scale[point[1]] + half_y;
                Vertex& vertex = cache[target++];
                vertex.x = static_cast<float>(position.x);
                vertex.y = static_cast<float>(position.y);
                vertex.z = static_cast<float>(position.z);
                vertex.u = row_u_is_arc[row] ? progress[point[0]] : static_cast<float>(private_u0 + side);   // 端面也落在本段那一格里
                vertex.v = static_cast<float>(row_v[row] + (row_height_is_y[row] ? up : side));
            }
        }
    }
}
