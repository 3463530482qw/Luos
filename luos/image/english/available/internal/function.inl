namespace Gnik_luos {
    // 贴图槽位的身份号:外部像素(图片模块给的)给 0,自带像素(程序生成的贴图)每造一份给一个新号
    // 拿像素地址当身份是不行的 —— 地址会被回收复用,两张不同的贴图会被认成同一张
    inline uint64_t next_texture_identity() {
        static std::atomic<uint64_t> counter{0};
        return ++counter;
    }
}
