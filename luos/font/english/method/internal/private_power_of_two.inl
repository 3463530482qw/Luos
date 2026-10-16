namespace Gnik_luos {
    // 行宽与图集高都取 2 的幂:补成正方形的位图在一块方形格子里排得整整齐齐,uv 也只按整数格算
    int Font::private_power_of_two(int value) {
        int side = 2;
        while (side < value) {
            side *= 2;
        }
        return side;
    }
}
