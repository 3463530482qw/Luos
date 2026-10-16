namespace Gnik_luos {
    struct Sprite_sheet {              // 一张图集按格切开:切图类绘制(瓦片地图、帧动画)都按它算 uv
        int columns{1};                // 横向格数
        int rows{1};                   // 纵向格数
        int count{1};                  // 总格数 = columns * rows(行主序:格号 = 行 * columns + 列)
    };
}
