#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_int_array(const int *values, size_t count) {
    printf("[ ");
    for (size_t i = 0; i < count; ++i) {
        printf("%d", values[i]);
        if (i + 1 < count) {
            printf(", ");
        }
    }
    printf(" ]\n");
}

static void malloc_realloc_demo(void) {
    puts("=== malloc + realloc 演示 ===");

    size_t count = 4;
    int *numbers = malloc(count * sizeof(*numbers));
    if (!numbers) {
        perror("malloc failed");
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        numbers[i] = (int)(i * i);
    }

    puts("初始数组：");
    print_int_array(numbers, count);

    puts("扩容到 8 个元素（保留旧数据）");
    size_t new_count = 8;
    int *tmp = realloc(numbers, new_count * sizeof(*numbers));
    if (!tmp) {
        perror("realloc failed");
        free(numbers);
        return;
    }
    numbers = tmp;

    for (size_t i = count; i < new_count; ++i) {
        numbers[i] = (int)(i * i);
    }
    print_int_array(numbers, new_count);

    puts("缩容到 5 个元素");
    new_count = 5;
    tmp = realloc(numbers, new_count * sizeof(*numbers));
    if (!tmp) {
        perror("realloc failed");
        free(numbers);
        return;
    }
    numbers = tmp;
    print_int_array(numbers, new_count);

    free(numbers);
}

static void calloc_demo(void) {
    puts("\n=== calloc 零初始化演示 ===");

    size_t count = 6;
    int *scores = calloc(count, sizeof(*scores));
    if (!scores) {
        perror("calloc failed");
        return;
    }

    puts("初始值（全部为 0）：");
    print_int_array(scores, count);

    for (size_t i = 0; i < count; ++i) {
        scores[i] = (int)(i + 80);
    }
    puts("更新后的成绩：");
    print_int_array(scores, count);

    free(scores);
}

static void string_builder_demo(void) {
    puts("\n=== realloc 构建字符串缓冲区 ===");

    const char *fragments[] = {
        "C", " 语言", " 内存", " 管理", " 演示"
    };
    const size_t fragment_count = sizeof(fragments) / sizeof(fragments[0]);

    size_t capacity = 16;
    size_t length = 0;
    char *buffer = malloc(capacity);
    if (!buffer) {
        perror("malloc failed");
        return;
    }
    buffer[0] = '\0';

    for (size_t i = 0; i < fragment_count; ++i) {
        size_t fragment_len = strlen(fragments[i]);
        if (length + fragment_len + 1 > capacity) {
            while (length + fragment_len + 1 > capacity) {
                capacity *= 2;
            }
            char *tmp = realloc(buffer, capacity);
            if (!tmp) {
                perror("realloc failed");
                free(buffer);
                return;
            }
            buffer = tmp;
        }
        memcpy(buffer + length, fragments[i], fragment_len);
        length += fragment_len;
        buffer[length] = '\0';
    }

    printf("结果字符串：%s\n", buffer);
    printf("最终容量：%zu 字节\n", capacity);

    free(buffer);
}

static void cleanup_on_failure_demo(void) {
    puts("\n=== 失败路径清理策略 ===");

    size_t rows = 3;
    size_t cols = 4;
    int **matrix = calloc(rows, sizeof(*matrix));
    if (!matrix) {
        perror("calloc failed");
        return;
    }

    size_t allocated_rows = 0;
    for (; allocated_rows < rows; ++allocated_rows) {
        matrix[allocated_rows] = malloc(cols * sizeof(**matrix));
        if (!matrix[allocated_rows]) {
            perror("malloc failed");
            break;
        }

        for (size_t col = 0; col < cols; ++col) {
            matrix[allocated_rows][col] = (int)(allocated_rows * cols + col);
        }
    }

    if (allocated_rows != rows) {
        puts("分配失败，释放已申请的行");
        for (size_t row = 0; row < allocated_rows; ++row) {
            free(matrix[row]);
        }
        free(matrix);
        return;
    }

    puts("成功分配二维数组，前几项如下：");
    for (size_t row = 0; row < rows; ++row) {
        print_int_array(matrix[row], cols);
    }

    for (size_t row = 0; row < rows; ++row) {
        free(matrix[row]);
    }
    free(matrix);
}

int main(void) {
    malloc_realloc_demo();
    calloc_demo();
    string_builder_demo();
    cleanup_on_failure_demo();
    return 0;
}
