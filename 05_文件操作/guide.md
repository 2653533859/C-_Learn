# 文件操作进阶指南

文件输入输出（File I/O）是 C 语言在实际项目中最常见的功能之一。本指南围绕标准 I/O 库（`stdio.h`）展开，从文件打开/关闭、文本与二进制读写、文件定位到标准流重定向，帮助你在不同平台上编写可靠的文件处理代码。

---

## 1. 标准 I/O 库概览

- C 标准库通过抽象的 **文件流（`FILE *`）** 来管理输入输出。无论是磁盘文件、管道还是内存流，本质上都被统一成“流”。
- 每个进程默认拥有三个已经打开的标准流：`stdin`（标准输入）、`stdout`（标准输出）和 `stderr`（标准错误）。
- 所有文件操作函数均声明于 `<stdio.h>`：包括 `fopen`、`fclose`、`fread`、`fwrite`、`fseek`、`fprintf`、`fscanf` 等。

---

## 2. 打开与关闭文件

### 2.1 `fopen`、`freopen` 与文件模式

使用 `fopen` 打开文件时，需要提供文件路径与模式字符串。常见模式如下：

| 模式 | 说明 | 文件不存在时 | 光标位置 |
|------|------|--------------|----------|
| `r`  | 以文本模式读取 | 打开失败 | 文件开头 |
| `w`  | 以文本模式写入（覆盖） | 创建新文件 | 文件开头 |
| `a`  | 以文本模式追加 | 创建新文件 | 文件末尾 |
| `r+` | 以文本模式读写 | 打开失败 | 文件开头 |
| `w+` | 以文本模式读写（覆盖） | 创建新文件 | 文件开头 |
| `a+` | 以文本模式读写（追加） | 创建新文件 | 文件末尾 |
| `rb` / `wb` / `ab` | 以二进制方式读/写/追加 | 参照对应文本模式 | 参照对应文本模式 |

> ✅ **建议**：在 Windows 上处理二进制文件时一定要带上 `b` 后缀，否则系统会自动转换换行符，导致数据损坏。

`freopen` 可用于将标准流重定向到指定文件，例如：

```c
freopen("output.log", "w", stdout);  // 将标准输出写入文件
```

### 2.2 正确关闭文件

- 使用完文件后调用 `fclose(fp);` 释放资源并刷新缓冲区。
- 如果 `fclose` 返回 `EOF`，说明关闭失败（常见于网络/管道中断或磁盘写满）。

### 2.3 错误处理示例

```c
FILE *fp = fopen("data.txt", "r");
if (fp == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
}

// ... 文件操作 ...

if (fclose(fp) == EOF) {
    perror("fclose");
}
```

`perror` 会结合当前的 `errno` 值输出系统级错误信息，是诊断失败原因的利器。

---

## 3. 文本文件读写

### 3.1 常用函数

- 写入：`fprintf`、`fputs`、`fputc`
- 读取：`fscanf`、`fgets`、`fgetc`

推荐使用基于缓冲的 `fgets`/`fputs` 读取整行文本，避免格式化输入带来的解析风险：

```c
char line[256];
while (fgets(line, sizeof line, fp)) {
    printf("%s", line);
}

if (ferror(fp)) {
    perror("读取失败");
}
```

### 3.2 字符编码与换行

- 不同平台的换行符不同：Unix/Linux 使用 `\n`，Windows 使用 `\r\n`。标准库会在文本模式下自动转换。
- 如果需要处理 UTF-8 或多字节编码，建议使用二进制模式读取字节流并通过额外库解析。

---

## 4. 二进制文件读写

二进制模式下不会对数据做任何转换，尤其适合存储结构体、图像或音频等原始数据。

### 4.1 `fwrite` 与 `fread`

```c
typedef struct {
    char name[32];
    int age;
    double score;
} Student;

Student students[] = {
    {"Alice", 19, 92.5},
    {"Bob", 20, 85.0}
};

FILE *fp = fopen("students.bin", "wb");
if (fp == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
}

size_t written = fwrite(students, sizeof(Student), 2, fp);
if (written != 2) {
    perror("fwrite");
}
fclose(fp);
```

读取时同样使用 `fread`，并检查返回值来判断是否读取完整结构体。需要注意不同平台的字节序和结构体对齐问题，如需跨平台共享二进制文件，最好使用标准化格式（JSON、Protocol Buffers 等）。

### 4.2 缓冲与刷新

- 标准 I/O 默认使用缓冲模式：行缓冲（`stdout`）、全缓冲（文件）或无缓冲（`stderr`）。
- 可以使用 `fflush(fp)` 主动刷新缓冲区，确保数据立即写入磁盘。

---

## 5. 文件定位：`fseek` 与 `ftell`

- `ftell(fp)` 返回当前文件位置（自文件开头起的偏移量，单位为字节）。
- `fseek(fp, offset, origin)` 允许将文件指针移动到指定位置：
  - `origin = SEEK_SET`：相对于文件开头
  - `origin = SEEK_CUR`：相对于当前位置
  - `origin = SEEK_END`：相对于文件末尾
- `rewind(fp)` 等价于 `fseek(fp, 0, SEEK_SET)`，并且会清除错误和 EOF 状态。

示例：

```c
if (fseek(fp, -5, SEEK_END) == 0) {
    long pos = ftell(fp);
    printf("当前位置: %ld\n", pos);
}
```

> 💡 **大文件支持**：在 32 位系统或需要处理超过 2 GB 的文件时，使用 `fseeko`/`ftello`（POSIX）或 `_fseeki64`/`_ftelli64`（Windows）以支持 64 位文件偏移。

---

## 6. 标准流与重定向

- 程序内部可以直接读写 `stdin`、`stdout`、`stderr`。
- Shell 或终端可以使用重定向改变标准流的数据来源或去向：
  - `./app < input.txt`：将 `input.txt` 作为标准输入
  - `./app > output.txt`：将标准输出写入文件
  - `./app 2> error.log`：将标准错误写入文件
  - `producer | consumer`：通过管道将前者的输出作为后者的输入
- 想在代码中重定向，可使用 `freopen` 或平台特定 API。

---

## 7. 错误检测与状态处理

- **错误标志**：当读取失败或触及 EOF 时，`ferror` 与 `feof` 会被设置。
- **清除状态**：使用 `clearerr(fp)` 重置错误与 EOF 状态。
- **系统错误码**：许多 I/O 函数失败时会设置 `errno`，可配合 `perror` 或 `strerror(errno)` 输出详情。

```c
if (fgets(buf, sizeof buf, fp) == NULL) {
    if (feof(fp)) {
        puts("已到文件末尾");
    } else if (ferror(fp)) {
        perror("fgets");
    }
}
```

---

## 8. 跨平台注意事项

1. **路径与编码**：Windows 使用 `\\` 作为目录分隔符，建议统一使用正斜杠 `/` 或借助平台宏处理。对于包含非 ASCII 字符的路径，可使用宽字符 API（如 `_wfopen`）。
2. **文本 vs. 二进制**：Windows 的文本模式会自动翻译换行符，导致文件大小和内容发生变化。跨平台传输时优先使用二进制模式并自行处理换行。
3. **字节序**：不同 CPU 可能使用小端或大端字节序。若需要网络传输或跨平台共享，建议序列化为标准格式并显式处理字节序。
4. **文件锁**：POSIX 与 Windows 对文件锁机制（`flock`、`LockFileEx`）支持不同。并发写入时需要额外的同步策略。
5. **缓冲刷新**：程序异常终止时缓冲区可能未写出数据。关键写入后调用 `fflush`，或使用 `fsync`（POSIX）/`_commit`（Windows）确保落盘。

---

## 9. 小结

- 熟悉 `fopen`、`fclose`、`fread`、`fwrite`、`fseek`、`ftell`、`fflush` 等核心 API 是文件操作的基础。
- 文本模式适合人类可读的数据，而二进制模式适合性能敏感或固定格式的数据。
- 良好的错误处理与跨平台意识能显著提升程序的鲁棒性。
- 结合本指南与示例程序，动手编写、调试、重定向文件 I/O，将理论转化为实践能力。
