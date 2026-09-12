#include <cstdio>
#include <cstdint>

// Q16.16 定点
static int32_t to_q16(float v) { return (int32_t)(v * 65536.0f + (v >= 0 ? 0.5f : -0.5f)); }
static float from_q16(int32_t v) { return (float)v / 65536.0f; }
// Q1.30 定点(专为 1.0~2.0 区间)
static int32_t to_q30(float v) { return (int32_t)(v * 1073741824.0f + 0.5f); }
static float from_q30(int32_t v) { return (float)v / 1073741824.0f; }
static float as_f16(float v) { return (float)(_Float16)v; }

int main() {
    float vals[] = {2560.0f/1440.0f, 2560.0f/1920.0f, 1920.0f/1200.0f, 2560.0f/1080.0f};
    const char* names[] = {"16:9", "2560/1920", "16:10", "21:9"};
    printf("%-12s %-13s %-13s %-13s %-13s\n", "case", "float", "float16", "Q16.16", "Q1.30");
    for (int i = 0; i < 4; ++i) {
        float v = vals[i];
        printf("%-12s %-13.8f %-13.8f %-13.8f %-13.8f\n", names[i],
               (double)v, (double)as_f16(v), (double)from_q16(to_q16(v)), (double)from_q30(to_q30(v)));
    }
    printf("\n反算逻辑坐标(logic_width=1920)时, 误差折算成像素:\n");
    float re = 2560.0f / 1920.0f;
    printf("  float  : %.6f\n", (double)re);
    printf("  float16: %.6f   误差 %.6f 逻辑单位\n", (double)as_f16(re), (double)(1920.0f*(re-as_f16(re))));
    printf("  Q16.16 : %.6f   误差 %.6f 逻辑单位\n", (double)from_q16(to_q16(re)), (double)(1920.0f*(re-from_q16(to_q16(re)))));
    printf("  Q1.30  : %.8f 误差 %.8f 逻辑单位\n", (double)from_q30(to_q30(re)), (double)(1920.0f*(re-from_q30(to_q30(re)))));
    printf("\n注: 分辨率对齐时(2560x1440 配 1920x1080 逻辑) re = %.6f\n", (double)(2560.0f/1920.0f));
    printf("    逻辑尺寸等于物理尺寸时(1920x1080 配 1920x1080) re = %.6f\n", (double)(1920.0f/1920.0f));
    return 0;
}