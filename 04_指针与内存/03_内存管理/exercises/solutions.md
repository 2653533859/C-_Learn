# 03 - 内存管理｜练习题详解

> 以下参考答案给出核心思路与示例命令，实际项目中请根据上下文调整实现细节。

---

## 题目 1｜动态数组扩容策略

- **内存流程**：当 `size == capacity` 时调用 `realloc` 扩容，旧数据会在新内存的前半部分保留。扩容成功后更新 `capacity` 并写入新元素。
- **初始化策略**：当 `capacity == 0` 时，先设置一个最小容量（如 `*capacity = 4`），再调用 `realloc`/`malloc`。常见写法：
  ```c
  if (*capacity == 0) {
      *capacity = 4;
      data = realloc(NULL, *capacity * sizeof(*data));
      if (!data) return NULL;
  }
  ```
- **调用方检查**：
  ```c
  arr = append_value(arr, &size, &capacity, value);
  if (!arr) {
      // 记录错误并释放已有资源
  }
  ```

---

## 题目 2｜泄漏定位与修复

- **问题**：当 `fopen` 失败或 `fgets` 失败时，`buffer` 没有释放，造成内存泄漏。`fopen` 失败时返回前未关闭 `FILE*`。
- **修复示例**：
  ```c
  char *load_config_path(void) {
      char *buffer = malloc(256);
      if (!buffer) {
          return NULL;
      }

      FILE *fp = fopen("/etc/myapp.conf", "r");
      if (!fp) {
          free(buffer);
          return NULL;
      }

      if (!fgets(buffer, 256, fp)) {
          fclose(fp);
          free(buffer);
          return NULL;
      }

      fclose(fp);
      return buffer;
  }
  ```
- **Valgrind 命令**：`valgrind --leak-check=full --show-leak-kinds=all ./your_program`

---

## 题目 3｜`realloc` 的陷阱

- **潜在问题**：若 `realloc` 失败，函数返回 `NULL`，原指针也丢失，导致内存泄漏。
- **安全写法**：
  ```c
  int *resize(int *data, size_t new_count) {
      int *tmp = realloc(data, new_count * sizeof(*data));
      if (!tmp) {
          return NULL; // 调用者仍持有原指针，可选择释放或继续使用
      }
      return tmp;
  }
  ```
- **缩容策略**：在调用前，若需要丢弃多余元素，应按照业务逻辑处理；缩容成功后如果想清理被移除元素，可在调用前手动处理或在 `realloc` 成功后对尾部数据进行重置。

---

## 题目 4｜调试命令设计

1. **GDB 断点**：在 `free` 与 `double_free_demo` 开始处下断点，例如 `break free`、`break double_free_demo`。可使用 `watch buffer` 或 `watch *buffer_ptr` 监测指针值。
2. **查看指针状态**：
   - `print buffer` 查看指针地址。
   - 单步执行后再次 `print buffer`，确认指针是否被置为 `NULL`。
   - 使用 `backtrace` 获取调用栈，确认释放顺序。
3. **Valgrind 命令**：`valgrind --leak-check=full --track-origins=yes ./memory_leak_example`

---

## 题目 5｜结构体对齐推断

- **尺寸推断**：在 64 位系统上，`double` 要求 8 字节对齐，`int` 通常为 4 字节，`short` 为 2 字节。可能的布局：
  - `char type` 占用偏移 0，后跟 7 字节填充
  - `double price` 偏移 8
  - `int count` 偏移 16
  - `short flag` 偏移 20，末尾再填充 6 字节
  - 因此 `sizeof(struct Record)` 可能为 24。
- **重新排列**：
  ```c
  struct Record {
      double price;
      int count;
      short flag;
      char type;
  };
  ```
  此时可能仅需 16 字节（取决于编译器）。
- **协议需求**：可使用 `#pragma pack(push, 1)` / `#pragma pack(pop)` 或 GCC 的 `__attribute__((packed))`。副作用是访问性能下降，且在部分架构上可能导致未对齐访问异常。

---

## 题目 6｜诊断悬垂指针

- **问题根源**：函数返回了已释放的堆内存，调用者获得悬垂指针，后续访问导致崩溃。
- **AddressSanitizer 命令**：
  ```bash
  gcc your_file.c -std=c11 -Wall -Wextra -pedantic -fsanitize=address -g -o your_prog
  ./your_prog
  ```
- **单元测试思路**：
  ```c
  void test_build_message(void) {
      char *msg = build_message();
      assert(msg != NULL);
      ASSERT_STREQ("Hello, ...", msg);
      free(msg);
  }
  ```
  配合 AddressSanitizer 或 Valgrind 运行测试用例，确保函数不返回已释放的指针。正确实现应由调用方负责释放返回值，函数内部不应提前 `free`。
