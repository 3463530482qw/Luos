namespace Gnik_luos {
    Tilemap& Tilemap::sheet(int sheet_columns, int sheet_rows) {   // 图集按 columns × rows 切格(行主序)
        sprite_sheet.columns = sheet_columns > 0 ? sheet_columns : 1;
        sprite_sheet.rows = sheet_rows > 0 ? sheet_rows : 1;
        sprite_sheet.count = sprite_sheet.columns * sprite_sheet.rows;
        dirty = true;
        return *this;
    }

    Tilemap& Tilemap::grid(int map_columns, int map_rows) {   // 地图多大(格数)
        columns = map_columns > 0 ? map_columns : 1;
        rows = map_rows > 0 ? map_rows : 1;
        tile.clear();
        dirty = true;
        return *this;
    }

    Tilemap& Tilemap::map(const std::vector<int>& source) {   // 逐格图号(行主序)
        tile = source;
        dirty = true;
        return *this;
    }

    Tilemap& Tilemap::origin(float x, float y) {   // 第一格左上角
        origin_x = x;
        origin_y = y;
        dirty = true;
        return *this;
    }

    Tilemap& Tilemap::size(float tile_size_value) {
        tile_size = tile_size_value;
        dirty = true;
        return *this;
    }

    Tilemap& Tilemap::view(int left, int top, int columns_value, int rows_value) {   // 只出视野内那些格
        view_x = left;
        view_y = top;
        view_columns = columns_value;
        view_rows = rows_value;
        dirty = true;
        return *this;
    }

    Tilemap& Tilemap::at(size_t index, int tile_value) {   // 单改一格
        if (index >= tile.size()) {
            tile.resize(index + 1, 0);
        }
        tile[index] = tile_value;
        dirty = true;
        return *this;
    }

    Tilemap& Tilemap::rgba(uint8_t red, uint8_t green, uint8_t blue, float alpha) {
        r = red;
        g = green;
        b = blue;
        a = alpha;
        dirty = true;
        return *this;
    }
}
