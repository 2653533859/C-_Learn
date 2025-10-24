#include <stddef.h>
#include <stdio.h>

static void print_with_pointer(const int *data, size_t length) {
    printf("使用指针遍历: ");
    for (size_t i = 0; i < length; ++i) {
        printf("%d ", *(data + i));
    }
    printf("\n");
}

static void print_with_index(const int (*matrix)[3], size_t rows) {
    printf("二维数组遍历:\n");
    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < 3; ++c) {
            printf("[%zu][%zu]=%d ", r, c, matrix[r][c]);
        }
        printf("\n");
    }
}

int main(void) {
    int numbers[] = {10, 20, 30, 40, 50};
    int *head = numbers;
    int *tail = numbers + 4;

    printf("数组基础信息:\n");
    printf("numbers 首地址=%p, head=%p, tail=%p\n", (void *)numbers, (void *)head, (void *)tail);
    printf("首尾元素: head -> %d, tail -> %d\n", *head, *tail);

    print_with_pointer(numbers, 5);

    printf("指针移动示例:\n");
    for (int *p = numbers; p < numbers + 5; ++p) {
        printf("地址=%p, 值=%d\n", (void *)p, *p);
    }

    int matrix[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    print_with_index(matrix, 2);

    int *row_pointers[2];
    row_pointers[0] = matrix[0];
    row_pointers[1] = matrix[1];

    printf("指针数组访问:\n");
    for (size_t r = 0; r < 2; ++r) {
        for (size_t c = 0; c < 3; ++c) {
            printf("row%zu[%zu]=%d ", r, c, row_pointers[r][c]);
        }
        printf("\n");
    }

    return 0;
}
