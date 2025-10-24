# 05 - 文件操作

文件操作是将程序数据持久化、构建工具链以及与外部系统交互的关键技能。本模块聚焦 C 标准库的文件 I/O，帮助你掌握文本/二进制读写、文件定位与标准流重定向等核心能力。

---

## 📚 模块概览

| 资源类型 | 文件/目录 | 说明 |
|---------|-----------|------|
| 📖 **详尽指南** | [`guide.md`](guide.md) | 覆盖文件打开/关闭、文本与二进制读写、`fseek`/`ftell`、标准流重定向、错误处理与跨平台要点 |
| 💡 **示例程序** | [`examples/text_file_io.c`](examples/text_file_io.c) | 文本文件的写入与逐行读取演示 |
| 💡 **示例程序** | [`examples/binary_file_io.c`](examples/binary_file_io.c) | 结构体数据的二进制序列化与读取 |
| 💡 **示例程序** | [`examples/file_seek_demo.c`](examples/file_seek_demo.c) | `fseek`/`ftell` 在随机访问场景中的应用 |
| 💡 **示例程序** | [`examples/stdio_redirection.c`](examples/stdio_redirection.c) | 标准输入输出的重定向与处理统计 |
| 🎯 **练习题** | [`exercises/exercises.md`](exercises/exercises.md) | 实用型练习（日志分析、文件复制、统计、数据提取） |
| ✅ **参考答案** | [`exercises/solutions.md`](exercises/solutions.md) | 每个练习的示例实现与扩展思路 |

---

## 🎯 学习目标

- 掌握 `fopen`/`fclose` 等文件生命周期管理函数与常用打开模式。
- 能区分文本与二进制文件，熟悉 `fgets`、`fputs`、`fread`、`fwrite` 的使用场景。
- 理解文件定位、随机访问原理，并能利用 `fseek`/`ftell` 构建高效的数据处理流程。
- 学会使用标准流（`stdin` / `stdout` / `stderr`）与重定向机制在命令行环境中搭建数据管道。
- 建立完善的错误处理与跨平台意识，避免常见 I/O 踩坑。

---

## 🧠 核心知识点速览

1. **文件模式与缓冲**：`r`/`w`/`a` 及其组合模式，文本/二进制差异，缓冲区刷新策略。
2. **文本处理**：逐行读取、格式化输出、安全地解析数据，理解编码与换行转换。
3. **二进制序列化**：结构体写入/读取、对齐与字节序、跨平台数据交换注意事项。
4. **文件定位**：`fseek`、`ftell`、`rewind` 的使用技巧，以及 64 位偏移的替代 API。
5. **标准流重定向**：Shell 重定向符号、`freopen`、在管道中的健壮读写策略。
6. **错误处理**：`errno`、`perror`、`ferror`、`feof` 的协同使用与恢复机制。

---

## 🧪 推荐实践步骤

1. **阅读理论**：从 [`guide.md`](guide.md) 入手，理解文件流的工作原理与常见 API。
2. **运行示例**：在 `examples/` 中依次编译运行四个示例，观察输出并尝试修改参数。
3. **动手实现**：完成 `exercises/` 目录中的练习题，重点关注错误处理与边界情况。
4. **复盘总结**：记录遇到的问题，参考 `solutions.md` 对比不同实现方式，形成个人笔记。

---

## 💡 示例程序详解

以下命令均在仓库根目录执行，或进入 `05_文件操作/examples` 后执行。

### 1. 文本文件读写：`text_file_io.c`

```bash
cd 05_文件操作/examples
gcc text_file_io.c -o text_file_io
gcc text_file_io.c -o text_file_io -Wall -Wextra -std=c11  # 推荐
./text_file_io
```

**预期输出**：
```
Reading back from sample_text.txt:
C programming makes file I/O manageable.
Always check the return value of fopen.
Remember to close files to flush buffers.
```

> 运行后会生成 `sample_text.txt`，可用于后续练习或与其他示例搭配。

### 2. 二进制文件读写：`binary_file_io.c`

```bash
cd 05_文件操作/examples
gcc binary_file_io.c -o binary_file_io
./binary_file_io
```

**预期输出**：
```
Loaded 3 tasks from tasks.bin:
Scanner    | Level:  1 | Progress:  35.0%
Parser     | Level:  2 | Progress:  75.0%
Emitter    | Level:  3 | Progress:  90.0%
```

> 程序会写入 `tasks.bin`，这是一个无格式的二进制文件，可使用十六进制工具（`xxd`, `hexdump`）观察其字节布局。

### 3. 文件定位演示：`file_seek_demo.c`

```bash
cd 05_文件操作/examples
gcc file_seek_demo.c -o file_seek_demo
./file_seek_demo
```

**预期输出**：
```
After write -> position: 26
Rewound -> position: 0
Character at offset 5: F
After reading offset 5 -> position: 6
Third character from end: X
After reading from end -> position: 24
```

> 尝试修改 `fseek` 的偏移量，观察 `ftell` 返回值如何变化，并思考在大文件中如何利用该机制实现随机访问。

### 4. 标准流重定向：`stdio_redirection.c`

```bash
cd 05_文件操作/examples
gcc stdio_redirection.c -o stdio_redirection
./stdio_redirection < sample_text.txt > duplicated.txt
cat duplicated.txt
```

**终端输出（标准错误流）**：
```
Processed 3 lines, 123 bytes
```

**`duplicated.txt` 内容**（与 `sample_text.txt` 一致）：
```
C programming makes file I/O manageable.
Always check the return value of fopen.
Remember to close files to flush buffers.
```

> 将标准输入/输出重定向到文件后，只有标准错误（`stderr`）仍显示在终端，这也是在管道/批处理脚本中报告统计信息的常见方式。

---

## 🎯 实战练习

| 练习 | 难度 | 目标概述 |
|------|------|----------|
| 日志等级统计 | 🟢 | 解析文本日志，统计不同严重级别的出现次数 |
| 二进制文件复制 | 🟡 | 实现跨平台可靠的文件复制工具，关注缓冲与错误处理 |
| 文件统计器 | 🟡 | 计算行数、单词数、字节数，兼容标准输入 |
| 部分文件提取 | 🔴 | 使用 `fseek`/`ftell` 高效提取大文件的指定片段 |

详见 [`exercises/exercises.md`](exercises/exercises.md)，参考解法位于 [`exercises/solutions.md`](exercises/solutions.md)。

---

## 🛠️ 常见问题排查指引

| 场景 | 可能原因 | 排查步骤 |
|------|----------|----------|
| `fopen` 返回 `NULL` | 路径错误、权限不足、文件不存在 | 打印 `perror("fopen")`；在 Windows 确认路径分隔符；检查文件是否被占用 |
| 读取文本时出现乱码 | 编码不一致、以文本模式读取二进制文件 | 使用二进制模式打开并自行处理编码；确认源文件编码为 UTF-8 |
| 二进制复制后的文件损坏 | 使用文本模式导致换行被转换、写入不完整 | 保证模式为 `rb`/`wb`；检查 `fwrite` 返回值并刷新缓冲区 |
| `ftell` 返回 `-1` | 定位失败、文件不支持随机访问 | 检查 `errno`，避免对管道/设备使用随机访问；必要时改用 `fseeko`/`ftello` |
| 终端没有输出，但文件为空 | 标准输出被重定向到文件但写入失败 | 检查 `stderr` 是否有错误提示；确认目标路径存在且磁盘空间充足 |

> 建议在关键 I/O 操作后立刻检查返回值，并使用 `perror` 或 `strerror(errno)` 提供明确的错误提示。

---

## ✅ 自测清单

- [ ] 能说出文本与二进制模式的区别，并知道何时使用 `b` 后缀。
- [ ] 熟悉 `fgets`、`fputs`、`fread`、`fwrite` 的参数含义与返回值。
- [ ] 能使用 `fseek`/`ftell` 实现随机访问，并理解 `SEEK_SET`、`SEEK_CUR`、`SEEK_END`。
- [ ] 知道如何在 Shell 中使用 `<`, `>`, `2>`, `|` 对标准流进行重定向。
- [ ] 每次文件操作后都会检查返回值，并在失败时输出清晰的诊断信息。

完成以上检查后，你已经具备在 C 语言中处理各种文件 I/O 需求的能力！继续挑战更大型的项目或结合前面模块的知识，打造属于你的文件处理工具链吧。
