std::unordered_map<std::string, Texture_slot> slot{};   // 路径 → 槽位:空路径那张纯色也在这里
图片 image_cache{};                                      // 像素缓存归图片模块管:同一张图只解码一次
vk::raii::DescriptorSetLayout descriptor_layout{nullptr};
