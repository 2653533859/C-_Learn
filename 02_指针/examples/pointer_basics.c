#include <stddef.h>
#include <stdio.h>

int main(void) {
    int value = 42;
    int *value_ptr = &value;

    printf("初始值: value=%d, &value=%p\n", value, (void *)&value);
    printf("指针信息: value_ptr=%p, *value_ptr=%d\n", (void *)value_ptr, *value_ptr);

    *value_ptr = 96;
    printf("修改后: value=%d, *value_ptr=%d\n", value, *value_ptr);

    double score = 88.5;
    double *score_ptr = &score;
    printf("混合类型: score=%.1f, score_ptr=%p\n", score, (void *)score_ptr);

    int numbers[] = {1, 2, 3, 4};
    int *iter = numbers;
    for (size_t i = 0; i < 4; ++i) {
        printf("numbers[%zu]=%d, iter+%zu -> %d\n", i, numbers[i], i, *(iter + i));
    }

    return 0;
}