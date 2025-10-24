# 03 - 内存管理

> 深入掌握堆栈模型与动态内存分配，让程序更加稳定、高效且易于调试。

## 📚 模块概览

| 资源类型 | 文件/目录 | 说明 |
|---------|-----------|------|
| 📖 **学习指南** | [`guide.md`](guide.md) | 详细讲解栈与堆、分配函数族、内存泄漏检测、内存对齐与常用库函数 |
| 💡 **示例程序** | [`dynamic_allocation_demo.c`](dynamic_allocation_demo.c) | 正确使用 `malloc`/`calloc`/`realloc`/`free` 的综合示例 |
| ⚠️ **反面案例** | [`memory_leak_example.c`](memory_leak_example.c) | 演示常见内存错误（泄漏、悬垂指针）并对比修复手法 |
| 🧭 **对齐演示** | [`alignment_example.c`](alignment_example.c) | 观察结构体对齐、填充与显式对齐控制 |
| 🎯 **练习题集** | [`exercises/exercises.md`](exercises/exercises.md) | 结合实践的 6 道练习，聚焦诊断与修复思路 |
| ✅ **答案解析** | [`exercises/solutions.md`](exercises/solutions.md) | 逐题拆解思路，附 Valgrind/GDB 建议命令 |

---

## 🎯 学习目标

完成本模块后，你将能够：

- 🔬 解释栈与堆的分工、生命周期与调试手段
- 🧮 正确选择并使用 `malloc` / `calloc` / `realloc` / `free`
- 🧹 诊断并修复内存泄漏、悬垂指针、双重释放等问题
- 📐 理解内存对齐、结构体填充及性能影响
- 🛠️ 熟练使用 Valgrind 与 GDB 追踪内存相关 Bug

---

## 🔗 知识衔接

- **来自上一模块**：在《03_函数与数组》中你已经掌握了静态数组的布局与函数参数传递。本模块在此基础上，引入动态内存的生命周期管理以及更灵活的内存模型。
- **通往下一阶段**：理解内存管理后，可以顺利进入《04_指针与内存》的高级指针技巧、内存池设计与字符串处理实战。

---

## 🧰 推荐工具

| 工具 | 用途 | 安装提示 |
|------|------|----------|
| `valgrind` | 发现内存泄漏、越界读写、未初始化内存 | `sudo apt install valgrind` |
| `gdb` | 精确定位崩溃现场、观察堆栈与变量 | 已在[全局指南](../../README.md)中提供安装步骤 |
| `clang` / `gcc` | 编译 C 程序，配合告警选项捕捉潜在问题 | 推荐开启 `-Wall -Wextra -pedantic -g` |

> 📌 **提示**：结合编译器告警、GDB 单步调试与 Valgrind 报告，可以迅速定位多数内存问题。

---

## 🚀 快速开始

```bash
# 进入本模块目录
cd 04_指针与内存/03_内存管理
```

### 编译与运行示例

```bash
# 1. 正确的动态内存分配流程演示
gcc dynamic_allocation_demo.c -std=c11 -Wall -Wextra -pedantic -g -o dynamic_allocation_demo
./dynamic_allocation_demo

# 2. 内存泄漏与修复对比
gcc memory_leak_example.c -std=c11 -Wall -Wextra -pedantic -g -o memory_leak_example
./memory_leak_example

# 3. 结构体内存对齐观察
gcc alignment_example.c -std=c11 -Wall -Wextra -pedantic -g -o alignment_example
./alignment_example
```

### 调试与检测建议

```bash
# 使用 Valgrind 报告泄漏与非法访问
valgrind --leak-check=full --show-leak-kinds=all ./memory_leak_example

# 使用 GDB 查看崩溃原因或变量状态
gdb ./dynamic_allocation_demo
```

---

## 📝 学习路径建议

1. **阅读 [`guide.md`](guide.md)**：从栈/堆模型切入，理解动态内存的工具箱与约束条件。
2. **动手跑示例**：先运行正确示例，再在反面案例中定位问题，观察 Valgrind/GDB 的输出。
3. **完成练习题**：聚焦 `realloc` 策略、调试命令、对齐推断等核心能力。
4. **扩展阅读**：结合上一模块的数组知识，尝试实现简单内存池或对象管理器，为后续的高级指针与字符串处理打下基础。

---

> 💡 **小贴士**：调试内存问题永远要从“发生在哪一行、哪一次分配”入手。良好的分配/释放习惯（统一入口、统一出口）能让这类问题少一半。
