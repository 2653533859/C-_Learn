# 指针模块练习题

> **练习说明**：题目按主题与难度拆分。推荐先完成标记为 🟢 的基础题，再挑战 🟡 / 🔴 题巩固理解。所有题目均在对应小节给出了提示与注意事项。

## 1. 指针基础

### 1.1 指针初始化检查 🟢
编写一个程序，声明一个 `int` 指针与一个 `double` 指针，要求：
1. 分别初始化为 `NULL`。
2. 使用 `if` 判断指针是否为空，并打印提示信息。
3. 在确认安全后，让它们指向对应类型的变量并输出变量值与地址。

**提示**：使用 `%p` 打印地址，记得显式转换为 `(void *)`。

### 1.2 指针交换值 🟢
实现一个 `swap_int(int *a, int *b)` 函数，通过指针交换两个整数。编写完整示例验证函数，确保修改结果可以在 `main` 函数中观察到。

### 1.3 指针算术演练 🟡
创建一个含 5 个元素的整型数组，通过指针遍历数组：
- 使用 `while` 循环迭代指针直至数组末尾。
- 统计所有元素的和。
- 打印每次迭代的指针地址和当前值。

## 2. 指针与数组

### 2.1 反转数组（原地操作） 🟡
编写 `void reverse(int *arr, size_t length)`，要求使用双指针技术原地反转整型数组，禁止创建额外数组。提供示例证明函数有效。

### 2.2 查找第一个出现位置 🟡
实现 `int *find_first(int *arr, size_t length, int target)`，返回指向目标值的指针；若不存在返回 `NULL`。在 `main` 中演示获取到的指针如何用于修改原数组。

### 2.3 指针数组统计 🔴
定义 `const char *languages[] = {"C", "Go", "Rust", "Swift", NULL};`，使用指针遍历数组：
1. 打印每个字符串及其长度。
2. 统计总字符数。
3. 计算第一个和最后一个有效元素之间的指针距离（单位：元素个数）。

## 3. 指针与函数

### 3.1 最值输出 🟡
实现 `void min_max(const int *arr, size_t length, int *min_value, int *max_value)`，通过指针参数返回数组中的最小值与最大值，禁止使用全局变量。

### 3.2 安全输入函数 🟡
封装一个函数 `int read_int(int *out_value)`，从标准输入读取整数：
- 读取成功返回 1，并将结果写入 `out_value`。
- 输入无效返回 0，不改变 `out_value`。
- 函数内部需检查指针是否为 `NULL`。

### 3.3 动态缓冲区管理 🔴
编写一个函数 `int append_line(char **buffer, size_t *length, const char *line)`：
- 若 `*buffer == NULL`，使用 `malloc` 分配足够空间复制 `line`。
- 否则使用 `realloc` 扩容并在末尾追加 `line`。
- 更新 `*length` 表示缓冲区当前字符总数。
- 返回 1 表示成功，0 表示内存分配失败。

## 4. 多级指针

### 4.1 生成二维数组 🟡
实现 `int **create_matrix(size_t rows, size_t cols)`，使用多级指针创建二维整型数组，要求：
- 返回的矩阵已初始化为 0。
- 调用者负责释放：先 `free` 每行，再 `free` 行指针数组。

### 4.2 交换指针指向 🟡
给定 `char *names[] = {"Alice", "Bob", "Carol"};`，编写 `void rotate(char **array, size_t length)`，将所有指针向左循环移动一位。要求使用指向指针的指针完成交换。

### 4.3 链表插入 🔴
设计单向链表节点：
```c
typedef struct Node {
    int value;
    struct Node *next;
} Node;
```
实现 `void insert_after(Node **head, int target, int new_value)`：
- 在链表中找到 `value == target` 的节点，在其后插入新节点。
- 若目标不存在，节点追加到链表末尾。
- 使用双指针（`Node **`）处理头节点可能为空的情况。

## 5. 函数指针与回调

### 5.1 计算器回调 🟡
定义 `typedef double (*binary_op)(double, double);`，实现加减乘除四个函数。
- 编写 `double execute(binary_op op, double a, double b)`。
- 在 `main` 中根据用户输入的运算符选择合适的函数指针并输出结果。

### 5.2 事件分发器 🟡
创建 `typedef void (*event_handler)(void);`，定义 3 个不同的事件处理函数。
- 使用函数指针数组存储处理器。
- 编写 `void dispatch(event_handler *handlers, size_t count, size_t index)` 执行指定事件，注意越界检查。

### 5.3 函数指针排序 🔴
实现一个简化版的排序函数：
```c
void sort_ints(int *arr, size_t length, int (*cmp)(int a, int b));
```
- 当 `cmp(a, b) > 0` 时交换元素（选择排序或冒泡皆可）。
- 提供升序与降序的比较函数。
- 编写完整演示验证排序结果正确。

## 6. 进阶挑战

1. **内存快照工具 🔴**：实现一个函数 `void dump_bytes(const void *data, size_t length)`，按十六进制打印任意内存区域，并在输出中标注指针地址段。要求使用 `const unsigned char *` 遍历数据。
2. **回调驱动状态机 🔴**：构建一个简单的状态机，包含三个状态与事件，根据输入字符触发状态转换。要求使用函数指针数组维护状态转移表，并打印每次状态变化。