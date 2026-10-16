namespace Gnik_luos {
    constexpr int atlas_pixel_limit = 2048 * 2048;   // 一张图集的像素上限:画布之外的浪费要有个头
    constexpr int atlas_row_budget = 4;              // 建图集时先备几行(行宽 × 这个数 = 初始高):免得每烤一个字都整张重烤
}
