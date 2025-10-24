# C 语言全局学习指南

![Status](https://img.shields.io/badge/status-active-brightgreen)
![PRs Welcome](https://img.shields.io/badge/PRs-welcome-blue)
![Made With](https://img.shields.io/badge/made%20with-C-orange)
![Learning Path](https://img.shields.io/badge/learning-path-success)

> 面向零基础至进阶学习者的 C 语言自学路线图与资源导航。

## 目录
- [项目目标](#项目目标)
- [五大模块概览](#五大模块概览)
- [推荐学习路径](#推荐学习路径)
- [开发环境准备](#开发环境准备)
  - [安装 GCC/Clang](#安装-gccclang)
  - [配置并使用 GDB 调试](#配置并使用-gdb-调试)
- [示例使用说明](#示例使用说明)
- [目录结构](#目录结构)
- [贡献指引（占位）](#贡献指引占位)
- [常见问题](#常见问题)

## 项目目标
本仓库旨在为学习者提供结构化的 C 语言学习路径，结合理论讲解、示例代码、练习题与拓展阅读，帮助你从零基础逐步掌握 C 语言编程，为系统编程、嵌入式开发或算法竞赛奠定扎实基础。

## 模块概览
| 模块 | 主题 | 简介 |
| :-- | :-- | :-- |
| [01_基础语法](01_基础语法/README.md) | 基础语法 | 变量、数据类型、运算符、输入输出等入门必备知识 |
| [02_控制结构](02_控制结构/README.md) | 控制结构 | 条件语句、循环语句与流程控制的核心概念 |
| [03_函数与数组](03_函数与数组/README.md) | 函数与数组 | 函数的定义与调用、数组与多维数组的使用技巧 |
| [04_指针与内存](04_指针与内存/README.md) | 指针与内存 | 指针基础、内存管理、字符串处理等关键能力 |
| [04_数据结构](04_数据结构/README.md) | 数据结构 | 数组、链表、栈/队列、二叉树等核心结构与实践 |
| [05_文件操作](05_文件操作/README.md) | 文件操作 | 文件读写、缓冲区管理与实际项目中的应用 |

更多拓展资料与学习笔记将集中存放于 [`docs/`](docs/README.md) 目录，配套图示或素材资源将放在 [`assets/`](assets/) 目录。

## 推荐学习路径
1. **环境准备**：根据下文步骤安装编译器与调试工具，确保可以本地编译运行 C 程序。
2. **基础语法启蒙**：从 `01_基础语法` 目录开始，理解 C 语言最基本的语法单元。
3. **掌握控制结构**：通过 `02_控制结构` 中的示例练习条件与循环语句，学会组合各种流程控制。
4. **函数化思维**：在 `03_函数与数组` 模块中练习封装逻辑、管理数组与内存布局。
5. **深入指针世界**：跟进 `04_指针与内存` 的引导，掌握指针运算、动态内存分配及常见踩坑点。
6. **掌握核心数据结构**：通过 `04_数据结构` 的综合教程，构建数组、链表、栈/队列与树的整体认知。
7. **应用于文件操作**：学习 `05_文件操作`，实现读写文件、处理数据持久化等实用能力。
8. **持续巩固**：结合 `docs/` 中的拓展阅读与练习题单进行复习与进阶。

## 开发环境准备

### 安装 GCC/Clang
#### macOS
1. 安装 Xcode Command Line Tools：
   ```bash
   xcode-select --install
   ```
2. 验证版本：
   ```bash
   gcc --version
   clang --version
   ```

#### Ubuntu / Debian 系 Linux
1. 更新软件源并安装 GCC、G++、GDB：
   ```bash
   sudo apt update
   sudo apt install build-essential gdb
   ```
2. 验证安装：
   ```bash
   gcc --version
   g++ --version
   gdb --version
   ```

#### Windows
- **推荐方案：使用 WSL (Windows Subsystem for Linux)**
  1. 启用 WSL 并安装 Ubuntu 子系统：<https://learn.microsoft.com/windows/wsl/install>
  2. 在 WSL 环境内执行 Linux 安装步骤。
- **备用方案：MinGW-w64 / MSYS2**
  1. 下载并安装 MSYS2：<https://www.msys2.org/>
  2. 打开 MSYS2 UCRT64 终端，执行：
     ```bash
     pacman -Syu
     pacman -S mingw-w64-ucrt-x86_64-gcc gdb make
     ```

### 配置并使用 GDB 调试
1. **编译时保留调试符号**：
   ```bash
   gcc main.c -g -o main
   ```
2. **启动调试会话**：
   ```bash
   gdb ./main
   ```
3. **常用调试命令**：
   - `break <行号|函数名>`：设置断点
   - `run [参数]`：启动程序
   - `next` / `step`：单步执行（不进入 / 进入函数）
   - `print <变量>`：查看变量值
   - `bt`：查看调用栈
   - `quit`：退出调试器
4. **创建 `.gdbinit`（可选）**：在用户主目录新增 `.gdbinit`，写入常用配置例如：
   ```
   set pagination off
   set disassembly-flavor intel
   ```

## 示例使用说明
```bash
# 克隆仓库
git clone <repository-url>
cd <repository-directory>

# 切换到指定模块并编译示例（以 01_基础语法 为例）
cd 01_基础语法/examples
# 假设存在 main.c
gcc main.c -o main
./main
```
> 各模块会提供 `examples/`、`exercises/`、`notes/` 等子目录（如适用），以组织不同类型的学习素材。

## 目录结构
```
.
├── 01_基础语法/        # 入门语法与基础练习
├── 02_控制结构/        # 条件、循环与流程控制
├── 03_函数与数组/      # 函数封装与数组操作
├── 04_指针与内存/      # 指针、动态内存、字符串
├── 04_数据结构/        # 线性与树形结构的教程与练习
├── 05_文件操作/        # 文件输入输出与案例
├── assets/             # 图片、图表等素材（占位）
├── docs/               # 学习计划、拓展阅读（占位）
├── README.md           # 全局学习指南
└── .gitignore          # Git 忽略规则
```

## 贡献指引（占位）
欢迎对学习资源、示例代码或练习题目提出改进建议。正式的贡献流程将补充于 `docs/CONTRIBUTING.md`，敬请期待。

## 常见问题
- **需要提前学习其他语言吗？** 不需要，仓库从零基础开始，聚焦 C 语言核心概念。
- **可以用于教学或培训吗？** 可以，欢迎遵循即将发布的授权协议引用与扩展。
- **如何反馈问题？** 请使用 Issues 将问题描述清楚，包括操作系统、编译器版本、错误信息等。

---

> 如果你希望贡献章节、案例或翻译内容，请关注仓库的 Issue 列表与 `docs/` 目录中的路线图。
