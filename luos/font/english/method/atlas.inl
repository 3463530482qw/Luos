namespace Gnik_luos {
    // 取这个字号的图集(没有就给空):绘制命令拿着它取像素,也靠它认"图集换没换"
    std::shared_ptr<const Atlas_info> Font::atlas(double pixel_height) const {
        const auto found = atlas_map.find(pixel_height);
        return found == atlas_map.end() ? nullptr : found->second;
    }
}
