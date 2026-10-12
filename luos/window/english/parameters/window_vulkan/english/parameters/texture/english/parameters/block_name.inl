namespace Gnik_luos {
    // 贴图块名:段号_面名。面名与顶点发射顺序一致(起端面 / 终端面 / +x / -x / +y / -y)
    inline std::string texture_block_name(size_t segment, size_t face) {
        static const char* face_name[6]{"start", "end", "px", "nx", "py", "ny"};
        return std::to_string(segment) + "_" + face_name[face % 6];
    }
}
