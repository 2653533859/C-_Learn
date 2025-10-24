# 指针模块参考答案

> ⚠️ 本答案供对照与自查之用。建议先独立完成练习，再对比思路、关注边界与常见错误。

## 1. 指针基础

### 1.1 指针初始化检查
```c
#include <stdio.h>

int main(void) {
    int *int_ptr = NULL;
    double *double_ptr = NULL;

    if (int_ptr == NULL) {
        puts("int_ptr 未指向有效地址");
    }
    if (double_ptr == NULL) {
        puts("double_ptr 未指向有效地址");
    }

    int value = 10;
    double score = 99.5;
    int_ptr = &value;
    double_ptr = &score;

    printf("value=%d, &value=%p, int_ptr=%p\n", value, (void *)&value, (void *)int_ptr);
    printf("score=%.1f, &score=%p, double_ptr=%p\n", score, (void *)&score, (void *)double_ptr);
    return 0;
}
```
- 先判断指针是否为 `NULL` 再使用，有助于定位潜在的未初始化访问。

### 1.2 指针交换值
```c
#include <stdio.h>

static void swap_int(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(void) {
    int x = 3;
    int y = 8;
    swap_int(&x, &y);
    printf("x=%d, y=%d\n", x, y);
    return 0;
}
```
- 通过指针修改实参值，函数内部无需返回即可实现交换。

### 1.3 指针算术演练
```c
#include <stddef.h>
#include <stdio.h>

int main(void) {
    int data[] = {2, 4, 6, 8, 10};
    int *cursor = data;
    int *end = data + 5;
    int sum = 0;

    while (cursor < end) {
        printf("地址=%p 值=%d\n", (void *)cursor, *cursor);
        sum += *cursor;
        ++cursor;
    }

    printf("总和=%d\n", sum);
    return 0;
}
```
- 使用 `end` 指针标记终点，可避免越界。

## 2. 指针与数组

### 2.1 反转数组（原地操作）
```c
#include <stddef.h>

void reverse(int *arr, size_t length) {
    int *left = arr;
    int *right = arr + length - 1;
    while (left < right) {
        int tmp = *left;
        *left = *right;
        *right = tmp;
        ++left;
        --right;
    }
}
```
- 雙指针夹逼方式原地交换，不额外占用内存。

### 2.2 查找第一个出现位置
```c
#include <stddef.h>

int *find_first(int *arr, size_t length, int target) {
    for (size_t i = 0; i < length; ++i) {
        if (arr[i] == target) {
            return &arr[i];
        }
    }
    return NULL;
}
```
- 返回指向数组内部元素的指针，调用者可直接修改原数组。

### 2.3 指针数组统计
```c
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    const char *languages[] = {"C", "Go", "Rust", "Swift", NULL};
    const char **cursor = languages;
    size_t total_chars = 0;
    size_t count = 0;

    while (*cursor != NULL) {
        size_t len = strlen(*cursor);
        printf("%s (长度=%zu)\n", *cursor, len);
        total_chars += len;
        ++cursor;
        ++count;
    }

    printf("总字符数=%zu\n", total_chars);
    printf("指针距离=%zu\n", cursor - languages - 1);
    return 0;
}
```
- `cursor - languages - 1` 表示首尾之间的元素数，注意 NULL 终止。

## 3. 指针与函数

### 3.1 最值输出
```c
#include <stddef.h>
#include <stdio.h>

void min_max(const int *arr, size_t length, int *min_value, int *max_value) {
    if (length == 0 || min_value == NULL || max_value == NULL) {
        return;
    }
    int min_v = arr[0];
    int max_v = arr[0];
    for (size_t i = 1; i < length; ++i) {
        if (arr[i] < min_v) min_v = arr[i];
        if (arr[i] > max_v) max_v = arr[i];
    }
    *min_value = min_v;
    *max_value = max_v;
}
```
- 函数内部使用局部变量暂存结果，最后写回指针。

### 3.2 安全输入函数
```c
#include <stdio.h>

int read_int(int *out_value) {
    if (out_value == NULL) {
        return 0;
    }

    int temp = 0;
    int matched = scanf("%d", &temp);
    if (matched == 1) {
        *out_value = temp;
        return 1;
    }
    return 0;
}
```
- 使用临时变量避免在读取失败时污染输出。

### 3.3 动态缓冲区管理
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int append_line(char **buffer, size_t *length, const char *line) {
    if (buffer == NULL || length == NULL || line == NULL) {
        return 0;
    }

    size_t line_len = strlen(line);
    size_t new_length = *length + line_len;
    char *new_buffer = NULL;

    if (*buffer == NULL) {
        new_buffer = malloc(new_length + 1);
        if (new_buffer == NULL) {
            return 0;
        }
        memcpy(new_buffer, line, line_len + 1);
    } else {
        new_buffer = realloc(*buffer, new_length + 1);
        if (new_buffer == NULL) {
            return 0;
        }
        memcpy(new_buffer + *length, line, line_len + 1);
    }

    *buffer = new_buffer;
    *length = new_length;
    return 1;
}
```
- 注意 `realloc` 失败时保持原指针不变；成功后更新长度与指针。

## 4. 多级指针

### 4.1 生成二维数组
```c
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int **create_matrix(size_t rows, size_t cols) {
    int **matrix = calloc(rows, sizeof(int *));
    if (matrix == NULL) {
        return NULL;
    }

    for (size_t r = 0; r < rows; ++r) {
        matrix[r] = calloc(cols, sizeof(int));
        if (matrix[r] == NULL) {
            for (size_t i = 0; i < r; ++i) {
                free(matrix[i]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}
```
- `calloc` 自动初始化为 0，失败时需要逐层释放已分配的内存。

### 4.2 交换指针指向
```c
#include <stddef.h>

void rotate(char **array, size_t length) {
    if (length == 0) {
        return;
    }
    char *first = array[0];
    for (size_t i = 0; i + 1 < length; ++i) {
        array[i] = array[i + 1];
    }
    array[length - 1] = first;
}
```
- 通过指向指针的访问修改原数组存储的指针值。

### 4.3 链表插入
```c
#include <stddef.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

void insert_after(Node **head, int target, int new_value) {
    if (head == NULL) {
        return;
    }

    Node **cursor = head;
    while (*cursor != NULL && (*cursor)->value != target) {
        cursor = &(*cursor)->next;
    }

    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return;
    }
    new_node->value = new_value;

    if (*cursor == NULL) {
        new_node->next = NULL;
        *cursor = new_node;
    } else {
        new_node->next = (*cursor)->next;
        (*cursor)->next = new_node;
    }
}
```
- 使用 `Node **` 可覆盖头节点为空或找到末尾的情况。

## 5. 函数指针与回调

### 5.1 计算器回调
```c
#include <stdio.h>

typedef double (*binary_op)(double, double);

double add(double a, double b) { return a + b; }
double sub(double a, double b) { return a - b; }
double mul(double a, double b) { return a * b; }
double divide(double a, double b) { return b == 0.0 ? 0.0 : a / b; }

double execute(binary_op op, double a, double b) {
    return op(a, b);
}
```
- 调用前检查除数为零，避免未定义行为。

### 5.2 事件分发器
```c
#include <stddef.h>
#include <stdio.h>

typedef void (*event_handler)(void);

void dispatch(event_handler *handlers, size_t count, size_t index) {
    if (handlers == NULL || index >= count || handlers[index] == NULL) {
        puts("无效的事件编号");
        return;
    }
    handlers[index]();
}
```
- 派发前做空指针和越界校验，避免崩溃。

### 5.3 函数指针排序
```c
#include <stddef.h>

void sort_ints(int *arr, size_t length, int (*cmp)(int a, int b)) {
    for (size_t i = 0; i < length; ++i) {
        for (size_t j = i + 1; j < length; ++j) {
            if (cmp(arr[i], arr[j]) > 0) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

int ascending(int a, int b) { return a - b; }
int descending(int a, int b) { return b - a; }
```
- 以简单的选择排序演示如何使用自定义比较器。

## 6. 进阶挑战

### 6.1 内存快照工具
```c
#include <stdio.h>

void dump_bytes(const void *data, size_t length) {
    const unsigned char *bytes = (const unsigned char *)data;
    for (size_t i = 0; i < length; ++i) {
        if (i % 8 == 0) {
            printf("\n%p: ", (const void *)(bytes + i));
        }
        printf("%02X ", bytes[i]);
    }
    printf("\n");
}
```
- 每 8 字节换行并打印当前地址，便于观察内存布局。

### 6.2 回调驱动状态机
```c
#include <stdio.h>

typedef enum { STATE_IDLE, STATE_RUNNING, STATE_DONE, STATE_COUNT } state_t;
typedef state_t (*transition)(void);

static state_t to_running(void) { puts("进入 RUNNING"); return STATE_RUNNING; }
static state_t to_done(void) { puts("进入 DONE"); return STATE_DONE; }
static state_t reset(void) { puts("重置为 IDLE"); return STATE_IDLE; }

int main(void) {
    transition table[STATE_COUNT][2] = {
        { to_running, reset },
        { to_done, reset },
        { reset, reset }
    };

    state_t state = STATE_IDLE;
    char input = 0;
    while (scanf(" %c", &input) == 1) {
        size_t event = (input == 'n'); /* 'n' 触发前进，其它字符触发重置 */
        state = table[state][event]();
    }
    return 0;
}
```
- 使用函数指针二维数组保存状态转移逻辑，简化条件分支。

---

> ✅ 对照参考答案后，建议总结自己在边界处理、指针空值检查、内存释放顺序上的经验，形成专属的指针调试清单。