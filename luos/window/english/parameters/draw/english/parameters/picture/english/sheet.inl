namespace Gnik_luos {
    // 从图集里切一格:图片只画这一格(与地图图层同一套切图口径,行主序)
    Picture& Picture::sheet(int columns, int rows, int index) {
        sprite_sheet.columns = columns > 0 ? columns : 1;
        sprite_sheet.rows = rows > 0 ? rows : 1;
        sprite_sheet.count = sprite_sheet.columns * sprite_sheet.rows;
        sheet_index = index < 0 ? 0 : (index >= sprite_sheet.count ? sprite_sheet.count - 1 : index);
        dirty = true;
        return *this;
    }
}
