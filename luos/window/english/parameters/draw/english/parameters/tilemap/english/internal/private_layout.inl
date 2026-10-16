namespace Gnik_luos {
    // 按视野逐格摊四边形:视野为空就整层都出(小地图用得上)
    void Tilemap::private_layout() {
        if (tile.empty()) {
            return;   // 这一层没内容
        }
        const int from_column = view_columns > 0 ? std::max(0, view_x) : 0;
        const int from_row = view_rows > 0 ? std::max(0, view_y) : 0;
        const int to_column = view_columns > 0 ? std::min(columns, view_x + view_columns) : columns;
        const int to_row = view_rows > 0 ? std::min(rows, view_y + view_rows) : rows;
        for (int row = from_row; row < to_row; row++) {
            for (int column = from_column; column < to_column; column++) {
                const size_t index = static_cast<size_t>(row) * static_cast<size_t>(columns) + static_cast<size_t>(column);
                if (index >= tile.size()) {
                    continue;
                }
                private_emit(column, row, tile[index]);
            }
        }
    }
}
