namespace Gnik_luos {
    // 贴图文件夹里那份 blocks.txt:一行一块"块名 宽 高",只记生成过的块
    void Vulkan_texture::read_blocks(const std::string& folder) {
        if (!blocks_read.insert(folder).second) {
            return;
        }
        std::ifstream file(folder + "/blocks.txt");
        std::string line;
        while (std::getline(file, line)) {
            std::string field[3];
            size_t count = 0;
            size_t begin = 0;
            for (size_t index = 0; index <= line.size() && count < 3; index++) {
                if (index == line.size() || line[index] == ' ' || line[index] == '\t' || line[index] == '\r') {
                    if (index > begin) {
                        field[count] = line.substr(begin, index - begin);
                        count++;
                    }
                    begin = index + 1;
                }
            }
            if (count < 3) {
                continue;   // 行不完整:跳过,不猜
            }
            bool numeric = true;
            for (int index = 1; index < 3 && numeric; index++) {
                bool dot = false;
                for (size_t cursor = 0; cursor < field[index].size(); cursor++) {
                    const char symbol = field[index][cursor];
                    if (symbol == '-' && cursor == 0) {
                        continue;
                    }
                    if (symbol == '.' && !dot) {
                        dot = true;
                        continue;
                    }
                    if (symbol < '0' || symbol > '9') {
                        numeric = false;
                        break;
                    }
                }
                numeric = numeric && !field[index].empty();
            }
            if (!numeric) {
                continue;   // 尺寸不是数字:这一行不算
            }
            generated[folder + "/" + field[0]] = std::make_pair(std::stod(field[1]), std::stod(field[2]));
        }
    }
}
