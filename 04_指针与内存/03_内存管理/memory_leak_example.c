#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    char *title;
    unsigned pages;
};

static char *duplicate_string(const char *source) {
    size_t length = strlen(source) + 1;
    char *copy = malloc(length);
    if (!copy) {
        return NULL;
    }
    memcpy(copy, source, length);
    return copy;
}

static void leak_demo(int fix_leak) {
    puts("=== 内存泄漏示例 ===");

    struct Book *book = malloc(sizeof(*book));
    if (!book) {
        perror("malloc book failed");
        return;
    }

    book->title = duplicate_string("C Memory Management");
    if (!book->title) {
        perror("malloc title failed");
        free(book);
        return;
    }
    book->pages = 320;

    printf("书籍：%s（%u 页）\n", book->title, book->pages);

    if (!fix_leak) {
        puts("⚠️  未释放 book 或 title，程序结束后仍占用内存。");
        return;
    }

    puts("✅ 修复：按所有权顺序释放资源。");
    free(book->title);
    free(book);
}

static void dangling_pointer_demo(void) {
    puts("\n=== 悬垂指针示例 ===");

    int *value = malloc(sizeof(*value));
    if (!value) {
        perror("malloc failed");
        return;
    }
    *value = 42;
    printf("分配地址：%p，内容：%d\n", (void *)value, *value);

    puts("错误示范（默认跳过以避免未定义行为）：释放后继续解引用。");
#ifdef TRIGGER_USE_AFTER_FREE
    free(value);
    printf("释放后访问：%d (未定义行为)\n", *value);
#else
    puts("编译时添加 -DTRIGGER_USE_AFTER_FREE 可观察崩溃或异常输出。");
    free(value);
#endif

    value = NULL;
    puts("修复：释放后将指针清空，并在使用前检查是否为 NULL。");
}

static void double_free_demo(int trigger_double_free) {
    puts("\n=== 双重释放示例 ===");

    int *buffer = malloc(16 * sizeof(*buffer));
    if (!buffer) {
        perror("malloc failed");
        return;
    }

    for (size_t i = 0; i < 16; ++i) {
        buffer[i] = (int)i;
    }

    free(buffer);

    if (trigger_double_free) {
        puts("⚠️  触发双重释放，可能导致程序崩溃。");
        free(buffer);
    } else {
        puts("✅ 修复：释放后立即将指针置为 NULL，避免重复释放。");
        buffer = NULL;
    }
}

int main(void) {
    leak_demo(0);
    leak_demo(1);

    dangling_pointer_demo();

    double_free_demo(0);
#ifdef TRIGGER_DOUBLE_FREE
    double_free_demo(1);
#endif

    puts("\n提示：使用 Valgrind 检测泄漏或开启 AddressSanitizer 观察未定义行为。\n");
    return 0;
}
