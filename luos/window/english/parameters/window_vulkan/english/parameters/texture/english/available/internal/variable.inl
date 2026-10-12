std::unordered_map<std::string, Texture_slot> slot{};   // 块路径 → 槽位:空键那张纯色也在这里
图片 image_cache{};                                      // 像素缓存归图片模块管:同一块只解码一次
std::set<std::string> reported{};                        // 已经报过"缺块已生成"的文件夹:一次运行只报一行
std::unordered_map<std::string, std::pair<double, double>> generated{};   // 生成过的块 → 生成时的宽高(手画的块不在里面)
std::set<std::string> blocks_read{};                     // 已经读过 blocks.txt 的文件夹
vk::raii::DescriptorSetLayout descriptor_layout{nullptr};
