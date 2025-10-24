# 03 - 内存管理｜练习题

> 将指南中的概念应用到实际代码中，聚焦内存分配策略、错误定位与调试命令。

## 使用方式

1. 尝试独立完成题目，必要时结合 `dynamic_allocation_demo.c` 等示例复习概念。
2. 如需提示，可使用 Valgrind 或 GDB 验证自己的推断。
3. 对照 [`solutions.md`](solutions.md) 检查思路是否完整，并记录仍存疑点。

---

### 题目 1｜动态数组扩容策略（🟢 简单）

给定以下函数片段：

```c
int *append_value(int *data, size_t *size, size_t *capacity, int value) {
    if (*size == *capacity) {
        size_t new_capacity = *capacity * 2;
        int *tmp = realloc(data, new_capacity * sizeof(*data));
        if (!tmp) {
            return NULL;
        }
        data = tmp;
        *capacity = new_capacity;
    }
    data[*size] = value;
    (*size)++;
    return data;
}
```

- 说明这段代码的内存管理流程。
- 若初始 `capacity = 0`，请给出初始化策略。
- 写出调用方在追加元素后需要执行的安全检查。

---

### 题目 2｜泄漏定位与修复（🟡 中等）

观察下列简化的配置读取函数：

```c
char *load_config_path(void) {
    char *buffer = malloc(256);
    FILE *fp = fopen("/etc/myapp.conf", "r");
    if (!fp) {
        return NULL;
    }

    if (!fgets(buffer, 256, fp)) {
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return buffer;
}
```

- 解释其中的资源泄漏问题。
- 给出修复方案，并说明失败路径如何清理资源。
- 使用 Valgrind 验证修复是否生效（写出命令）。

---

### 题目 3｜`realloc` 的陷阱（🟡 中等）

分析以下代码：

```c
int *resize(int *data, size_t new_count) {
    data = realloc(data, new_count * sizeof(*data));
    if (!data) {
        return NULL;
    }
    return data;
}
```

- 指出潜在的问题。
- 修改函数以确保在 `realloc` 失败时仍可访问原始内存。
- 若希望缩小数组并释放多余元素，应在调用 `resize` 之前或之后做哪些处理？

---

### 题目 4｜调试命令设计（🔴 困难）

某个程序在 `memory_leak_example.c` 的双重释放演示上崩溃。假设你只能使用标准调试工具，写出一份最小化的调试计划，包括：

1. GDB 中需要设置的断点和监视点。
2. 如何使用 GDB 查看指针释放前后的状态。
3. 一条 Valgrind 命令，用于验证修复后是否仍存在内存错误。

---

### 题目 5｜结构体对齐推断（🟡 中等）

考虑以下结构体：

```c
struct Record {
    char type;
    double price;
    int count;
    short flag;
};
```

- 在常见的 64 位系统上，推测 `sizeof(struct Record)` 的可能值，并解释原因。
- 重新排列成员以减少填充字节。
- 若要求网络协议中字段完全按顺序排列，应该使用哪种对齐控制方法？有哪些副作用？

---

### 题目 6｜诊断悬垂指针（🔴 困难）

你在大型项目中遇到如下简化的崩溃：

```c
char *build_message(void) {
    char *msg = malloc(32);
    snprintf(msg, 32, "Hello, %s", getenv("USER"));
    free(msg);
    return msg;
}
```

- 指出导致崩溃的本质原因。
- 结合 AddressSanitizer，写出能够捕获此类错误的编译与运行命令。
- 设计一个单元测试用例，确保未来修改不会再次引入悬垂指针。
