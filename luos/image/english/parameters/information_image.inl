namespace Gnik_luos {
    // 图片命令的像素(浅拷贝视图 + 自己可能持有一份):
    // 自带一份像素(vector)时析构与拷贝都按深拷贝走 —— 绘制命令按值进绘制包是常态,数据必须跟着走
    class Information_image {
        public:
            std::vector<unsigned char> pixels{};   // 自己持有的像素:只用外部指针时这里是空的
            unsigned char* data{nullptr};          // 像素首地址:可能是外部的,也可能指着上面的 vector
            uint64_t identity{0};                  // 自带像素的唯一号(渲染侧认贴图身份用);外部像素为 0
            int width{0};
            int height{0};
            int channels{4};

            Information_image() = default;

            Information_image(const Information_image& other) {
                pixels = other.pixels;
                data = pixels.empty() ? other.data : pixels.data();
                identity = other.identity;
                width = other.width;
                height = other.height;
                channels = other.channels;
            }

            Information_image& operator=(const Information_image& other) {
                if (this == &other) {
                    return *this;
                }
                pixels = other.pixels;
                data = pixels.empty() ? other.data : pixels.data();
                identity = other.identity;
                width = other.width;
                height = other.height;
                channels = other.channels;
                return *this;
            }

            Information_image(Information_image&& other) noexcept
                : pixels(std::move(other.pixels)), data(other.data), identity(other.identity), width(other.width), height(other.height), channels(other.channels) {
                data = pixels.empty() ? other.data : pixels.data();
            }

            Information_image& operator=(Information_image&& other) noexcept {
                if (this == &other) {
                    return *this;
                }
                pixels = std::move(other.pixels);
                data = pixels.empty() ? other.data : pixels.data();
                identity = other.identity;
                width = other.width;
                height = other.height;
                channels = other.channels;
                return *this;
            }

            void clear() {
                if (pixels.empty() && data != nullptr) {
                    stbi_image_free(data);   // 外部交给图片模块的像素:由模块统一放掉
                }
                pixels.clear();
                data = nullptr;
                identity = 0;
                width = 0;
                height = 0;
            }
    };
}
