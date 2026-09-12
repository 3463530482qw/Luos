#include <cstdio>
#include <cstdint>
#include <cstring>

static float as_float16(float v) {
    _Float16 h = static_cast<_Float16>(v);
    return static_cast<float>(h);
}

int main() {
    struct Case { const char* name; float value; };
    Case cases[] = {
        {"16:9 aspectratio", 2560.0f / 1440.0f},
        {"re_aspectratio (2560/1920)", 2560.0f / 1920.0f},
        {"16:10", 1920.0f / 1200.0f},
        {"4:3", 1024.0f / 768.0f},
        {"21:9", 2560.0f / 1080.0f},
    };
    printf("%-28s %-14s %-14s %s\n", "case", "float", "float16", "half 相对误差");
    for (auto& c : cases) {
        float f = c.value;
        float h = as_float16(c.value);
        double err = (double)(h - f) / (double)f;
        printf("%-28s %-14.8f %-14.8f %.4f%%\n", c.name, (double)f, (double)h, err * 100.0);
    }
    printf("\n用 half 的 aspectratio 反算宽度 (16:9, 高度 1080):\n");
    float exact = 2560.0f / 1440.0f;
    float halfv = as_float16(exact);
    printf("  float  : %.6f 像素\n", (double)(1080.0f * exact));
    printf("  float16: %.6f 像素\n", (double)(1080.0f * halfv));
    printf("  差     : %.6f 像素\n", (double)(1080.0f * exact - 1080.0f * halfv));
    printf("\n用 half 的 re_aspectratio 反算鼠标 (re=2560/1920):\n");
    float re_exact = 2560.0f / 1920.0f;
    float re_half = as_float16(re_exact);
    printf("  float  : %.10f\n", (double)re_exact);
    printf("  float16: %.10f\n", (double)re_half);
    printf("  相同?  : %s\n", re_exact == re_half ? "是" : "否");
    return 0;
}