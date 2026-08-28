#include "english/parameters/information_image.inl"
namespace Gnik_luos {
    class Image {
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
    };
    using 图片 = Image;
}
#include "english/load.inl"