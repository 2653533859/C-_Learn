#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define NAME_LEN 32

/*
 * 数组与字符串示例
 * - 演示顺序存储的遍历、查找、旋转等操作
 * - 展示结构体数组与字符串处理的结合
 */

struct Student {
    char name[NAME_LEN];
    int scores[3];
};

static int array_sum(const int *arr, size_t len) {
    int total = 0;
    for (size_t i = 0; i < len; ++i) {
        total += arr[i];
    }
    return total;
}

static int array_max(const int *arr, size_t len) {
    assert(len > 0);
    int max = arr[0];
    for (size_t i = 1; i < len; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

/* 循环右移数组，steps 可以大于 len */
static void rotate_right(int *arr, size_t len, size_t steps) {
    if (len == 0) {
        return;
    }
    steps %= len;
    if (steps == 0) {
        return;
    }

    int buffer[64];
    if (len > sizeof(buffer) / sizeof(buffer[0])) {
        /* 为教学简化，这里只处理不超过 64 的数组 */
        fprintf(stderr, "rotate_right: len too large for demo\n");
        return;
    }

    memcpy(buffer, arr + (len - steps), steps * sizeof(int));
    memmove(arr + steps, arr, (len - steps) * sizeof(int));
    memcpy(arr, buffer, steps * sizeof(int));
}

static void reverse_string(char *str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; ++i) {
        char tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
}

static size_t count_char(const char *str, char target) {
    size_t count = 0;
    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (str[i] == target) {
            ++count;
        }
    }
    return count;
}

static double student_average(const struct Student *stu) {
    int total = 0;
    for (size_t i = 0; i < 3; ++i) {
        total += stu->scores[i];
    }
    return total / 3.0;
}

static void test_array_operations(void) {
    int scores[] = {72, 95, 68, 88, 91};
    size_t len = sizeof(scores) / sizeof(scores[0]);

    assert(array_sum(scores, len) == 414);
    assert(array_max(scores, len) == 95);

    rotate_right(scores, len, 2);
    int expected_after_rotate[] = {88, 91, 72, 95, 68};
    for (size_t i = 0; i < len; ++i) {
        assert(scores[i] == expected_after_rotate[i]);
    }
}

static void test_string_operations(void) {
    char greeting[32] = "data structure";
    reverse_string(greeting);
    assert(strcmp(greeting, "erutcurts atad") == 0);

    reverse_string(greeting); /* 还原 */
    assert(count_char(greeting, 't') == 2);

    char buffer[NAME_LEN];
    snprintf(buffer, sizeof(buffer), "%s %d", "Topic", 4);
    assert(strcmp(buffer, "Topic 4") == 0);
}

static void test_struct_array(void) {
    struct Student students[2] = {
        {.name = "Alice", .scores = {85, 90, 92}},
        {.name = "Bob", .scores = {78, 88, 84}},
    };

    double avg0 = student_average(&students[0]);
    double avg1 = student_average(&students[1]);
    assert(avg0 > avg1);

    /* 验证结构体数组在内存中连续存储 */
    uintptr_t addr0 = (uintptr_t)&students[0];
    uintptr_t addr1 = (uintptr_t)&students[1];
    size_t stride = sizeof(struct Student);
    assert(addr1 - addr0 == stride);
}

int main(void) {
    puts("[array_string_demo] Running tests...");
    test_array_operations();
    test_string_operations();
    test_struct_array();
    puts("[array_string_demo] All tests passed!\n");
    return 0;
}
