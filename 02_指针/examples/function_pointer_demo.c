#include <stdio.h>

typedef int (*int_comparator)(int, int);
typedef void (*action)(const char *);

static int ascending(int a, int b) {
    return a - b;
}

static int descending(int a, int b) {
    return b - a;
}

static void show_message(const char *text) {
    printf("回调: %s\n", text);
}

static int apply_comparator(int a, int b, int_comparator cmp) {
    return cmp(a, b);
}

int main(void) {
    int x = 7;
    int y = 3;

    printf("函数指针比较:\n");
    printf("ascending(%d, %d) = %d\n", x, y, apply_comparator(x, y, ascending));
    printf("descending(%d, %d) = %d\n", x, y, apply_comparator(x, y, descending));

    action steps[] = {
        show_message,
        show_message
    };

    steps[0]("准备执行任务");
    steps[1]("任务完成");

    int_comparator dynamic_cmp = NULL;
    dynamic_cmp = (x > y) ? ascending : descending;
    printf("动态选择: result=%d\n", dynamic_cmp(x, y));

    return 0;
}
