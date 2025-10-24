#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdalign.h>

struct DefaultLayout {
    char c;
    int i;
    double d;
};

#pragma pack(push, 1)
struct PackedLayout {
    char c;
    int i;
    double d;
};
#pragma pack(pop)

struct ManualAligned {
    char c;
    alignas(16) double d;
    int i;
};

static void print_default_layout(void) {
    puts("=== 默认对齐策略 ===");
    printf("sizeof(struct DefaultLayout) = %zu\n", sizeof(struct DefaultLayout));
    printf("offset(c) = %zu\n", offsetof(struct DefaultLayout, c));
    printf("offset(i) = %zu\n", offsetof(struct DefaultLayout, i));
    printf("offset(d) = %zu\n", offsetof(struct DefaultLayout, d));
}

static void print_packed_layout(void) {
    puts("\n=== 强制紧凑布局（pack 1） ===");
    printf("sizeof(struct PackedLayout) = %zu\n", sizeof(struct PackedLayout));
    printf("offset(c) = %zu\n", offsetof(struct PackedLayout, c));
    printf("offset(i) = %zu\n", offsetof(struct PackedLayout, i));
    printf("offset(d) = %zu\n", offsetof(struct PackedLayout, d));
}

static void print_manual_aligned(void) {
    puts("\n=== 手动提高对齐要求 ===");
    printf("sizeof(struct ManualAligned) = %zu\n", sizeof(struct ManualAligned));
    printf("offset(c) = %zu\n", offsetof(struct ManualAligned, c));
    printf("offset(d) = %zu\n", offsetof(struct ManualAligned, d));
    printf("offset(i) = %zu\n", offsetof(struct ManualAligned, i));
}

static void demonstrate_cache_friendliness(void) {
    puts("\n=== 缓存友好性示例 ===");

    struct DefaultLayout list[4];
    for (size_t idx = 0; idx < 4; ++idx) {
        list[idx].c = (char)('A' + (int)idx);
        list[idx].i = (int)(idx * 10);
        list[idx].d = (double)idx * 0.5;
    }

    printf("结构体数组占用 %zu 字节\n", sizeof(list));
    printf("ManualAligned 对齐要求：%zu\n", alignof(struct ManualAligned));
}

int main(void) {
    print_default_layout();
    print_packed_layout();
    print_manual_aligned();
    demonstrate_cache_friendliness();
    return 0;
}
