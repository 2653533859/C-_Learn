# 01_基础语法 练习题答案与解析

本文档提供所有练习题的参考答案和详细解析。建议先独立完成练习，再查看本文档。

---

## 第一部分：数据类型与变量

### 1.1 变量交换 🟢

#### 解法一：使用临时变量

```c
#include <stdio.h>

int main() {
    int a, b, temp;
    
    printf("请输入两个整数: ");
    scanf("%d %d", &a, &b);
    
    printf("交换前: a = %d, b = %d\n", a, b);
    
    // 使用临时变量交换
    temp = a;
    a = b;
    b = temp;
    
    printf("交换后: a = %d, b = %d\n", a, b);
    
    return 0;
}
```

#### 解法二：使用算术运算（不推荐，可能溢出）

```c
a = a + b;
b = a - b;
a = a - b;
```

#### 解法三：使用异或运算（适用于整数）

```c
a = a ^ b;
b = a ^ b;
a = a ^ b;
```

**解析**：
- 方法一最直观、安全，推荐使用
- 方法二可能导致溢出，不推荐
- 方法三利用异或的性质 `a ^ a = 0` 和 `a ^ 0 = a`，但可读性差

---

### 1.2 数据类型大小检测 🟢

```c
#include <stdio.h>

int main() {
    printf("========================================\n");
    printf("   基本数据类型大小检测\n");
    printf("========================================\n\n");
    
    printf("类型              大小(字节)\n");
    printf("--------------------------------\n");
    printf("char              %lu\n", sizeof(char));
    printf("unsigned char     %lu\n", sizeof(unsigned char));
    printf("short             %lu\n", sizeof(short));
    printf("unsigned short    %lu\n", sizeof(unsigned short));
    printf("int               %lu\n", sizeof(int));
    printf("unsigned int      %lu\n", sizeof(unsigned int));
    printf("long              %lu\n", sizeof(long));
    printf("unsigned long     %lu\n", sizeof(unsigned long));
    printf("long long         %lu\n", sizeof(long long));
    printf("float             %lu\n", sizeof(float));
    printf("double            %lu\n", sizeof(double));
    printf("long double       %lu\n", sizeof(long double));
    printf("void*             %lu\n", sizeof(void*));
    
    return 0;
}
```

**解析**：
- `sizeof` 返回类型为 `size_t`，使用 `%lu` 格式说明符
- 不同系统/编译器可能有不同结果（如 `long` 在 32 位系统为 4 字节，64 位为 8 字节）
- 指针大小通常与系统位数相关（32 位系统 4 字节，64 位系统 8 字节）

---

### 1.3 温度转换器 🟢

```c
#include <stdio.h>

int main() {
    float celsius, fahrenheit;
    
    printf("请输入摄氏温度: ");
    scanf("%f", &celsius);
    
    // 转换公式: F = C * 9/5 + 32
    fahrenheit = celsius * 9.0 / 5.0 + 32;
    
    printf("摄氏温度: %.1f°C\n", celsius);
    printf("华氏温度: %.1f°F\n", fahrenheit);
    
    return 0;
}
```

**解析**：
- 使用 `9.0 / 5.0` 而非 `9 / 5`，避免整数除法导致精度丢失
- `%.1f` 格式化输出保留一位小数
- 常见温度对照：0°C = 32°F, 100°C = 212°F

**拓展**：添加反向转换和开尔文转换

```c
// 华氏转摄氏: C = (F - 32) * 5/9
celsius = (fahrenheit - 32) * 5.0 / 9.0;

// 摄氏转开尔文: K = C + 273.15
float kelvin = celsius + 273.15;
```

---

### 1.4 圆的计算 🟡

```c
#include <stdio.h>

#define PI 3.14159

int main() {
    float radius, circumference, area;
    
    printf("请输入圆的半径: ");
    scanf("%f", &radius);
    
    // 计算周长: C = 2πr
    circumference = 2 * PI * radius;
    
    // 计算面积: A = πr²
    area = PI * radius * radius;
    
    printf("半径: %.2f\n", radius);
    printf("周长: %.2f\n", circumference);
    printf("面积: %.2f\n", area);
    
    return 0;
}
```

**解析**：
- 使用 `#define` 定义常量 PI，便于维护和修改
- 面积公式也可以写成 `PI * pow(radius, 2)`（需要 `#include <math.h>`）
- 注意半径的平方使用 `radius * radius` 而非 `radius ^ 2`（`^` 是异或运算符）

**常见错误**：
```c
// ❌ 错误
#define PI = 3.14159  // 不需要等号
area = PI * radius ^ 2;  // ^ 不是幂运算

// ✅ 正确
#define PI 3.14159
area = PI * radius * radius;
```

---

### 1.5 字符 ASCII 码分析 🟡

```c
#include <stdio.h>

int main() {
    char ch;
    
    printf("请输入一个字符: ");
    scanf(" %c", &ch);  // 注意 %c 前的空格，跳过空白字符
    
    printf("字符: '%c'\n", ch);
    printf("ASCII 码: %d\n", (int)ch);
    
    // 判断字符类型
    printf("类型: ");
    if (ch >= 'A' && ch <= 'Z') {
        printf("大写字母\n");
    } else if (ch >= 'a' && ch <= 'z') {
        printf("小写字母\n");
    } else if (ch >= '0' && ch <= '9') {
        printf("数字\n");
    } else if (ch == ' ') {
        printf("空格\n");
    } else {
        printf("其他字符\n");
    }
    
    return 0;
}
```

**解析**：
- `scanf(" %c", &ch)` 前的空格用于跳过之前输入的换行符
- 字符本质是整数，可以直接与数字比较
- ASCII 码范围：
  - '0'-'9': 48-57
  - 'A'-'Z': 65-90
  - 'a'-'z': 97-122

**拓展**：大小写转换

```c
// 大写转小写（差值为 32）
if (ch >= 'A' && ch <= 'Z') {
    char lower = ch + 32;
    printf("小写形式: %c\n", lower);
}

// 小写转大写
if (ch >= 'a' && ch <= 'z') {
    char upper = ch - 32;
    printf("大写形式: %c\n", upper);
}

// 使用标准库函数（推荐）
#include <ctype.h>
if (isupper(ch)) printf("大写字母\n");
if (islower(ch)) printf("小写字母\n");
char lower = tolower(ch);
char upper = toupper(ch);
```

---

## 第二部分：运算符与表达式

### 2.1 基本计算器 🟢

```c
#include <stdio.h>

int main() {
    int num1, num2;
    char op;
    
    printf("请输入表达式（如 15 + 7）: ");
    scanf("%d %c %d", &num1, &op, &num2);
    
    printf("%d %c %d = ", num1, op, num2);
    
    switch (op) {
        case '+':
            printf("%d\n", num1 + num2);
            break;
        case '-':
            printf("%d\n", num1 - num2);
            break;
        case '*':
            printf("%d\n", num1 * num2);
            break;
        case '/':
            if (num2 != 0) {
                printf("%.2f\n", (float)num1 / num2);
            } else {
                printf("错误：除数不能为零\n");
            }
            break;
        case '%':
            if (num2 != 0) {
                printf("%d\n", num1 % num2);
            } else {
                printf("错误：除数不能为零\n");
            }
            break;
        default:
            printf("错误：不支持的运算符\n");
    }
    
    return 0;
}
```

**解析**：
- 使用 `switch` 语句处理多种运算符
- 除法和取模运算前必须检查除数是否为零
- 整数除法使用类型转换 `(float)num1 / num2` 得到小数结果

**拓展**：添加幂运算和更多功能

```c
case '^':  // 幂运算
    printf("%.2f\n", pow(num1, num2));  // 需要 #include <math.h>
    break;
```

---

### 2.2 闰年判断 🟢

```c
#include <stdio.h>

int main() {
    int year;
    
    printf("请输入年份: ");
    scanf("%d", &year);
    
    // 闰年规则：能被4整除但不能被100整除，或者能被400整除
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        printf("%d 年是闰年\n", year);
    } else {
        printf("%d 年不是闰年\n", year);
    }
    
    return 0;
}
```

**解析**：
- 闰年判断逻辑：`(year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)`
- 优先级：`%` > `==` > `!=` > `&&` > `||`
- 示例：
  - 2000 年：能被 400 整除 → 闰年 ✓
  - 1900 年：能被 100 整除但不能被 400 整除 → 平年 ✗
  - 2024 年：能被 4 整除但不能被 100 整除 → 闰年 ✓

**优化版本**（短路求值）

```c
int isLeapYear = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
```

---

### 2.3 最大值与最小值 🟡

```c
#include <stdio.h>

int main() {
    int a, b, c;
    
    printf("请输入三个整数: ");
    scanf("%d %d %d", &a, &b, &c);
    
    // 使用三目运算符找最大值
    int max = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
    
    // 使用三目运算符找最小值
    int min = (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
    
    printf("最大值: %d\n", max);
    printf("最小值: %d\n", min);
    
    return 0;
}
```

**解析**：
- 三目运算符嵌套：`条件1 ? (条件2 ? 值1 : 值2) : (条件3 ? 值3 : 值4)`
- 逻辑：先比较前两个数，得到较大/小者后再与第三个数比较

**替代方案**（使用 if 语句，更清晰）

```c
int max = a;
if (b > max) max = b;
if (c > max) max = c;

int min = a;
if (b < min) min = b;
if (c < min) min = c;
```

**拓展**：封装成函数

```c
int max3(int a, int b, int c) {
    int max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    return max;
}
```

---

### 2.4 位运算权限系统 🔴

```c
#include <stdio.h>

#define READ    0x01  // 0001 = 1
#define WRITE   0x02  // 0010 = 2
#define EXECUTE 0x04  // 0100 = 4

void printPermissions(int perm) {
    printf("当前权限: %d\n", perm);
    printf("权限列表:\n");
    printf("  %s READ\n", (perm & READ) ? "✔" : "✘");
    printf("  %s WRITE\n", (perm & WRITE) ? "✔" : "✘");
    printf("  %s EXECUTE\n", (perm & EXECUTE) ? "✔" : "✘");
}

int main() {
    int permission;
    
    printf("请输入初始权限值: ");
    scanf("%d", &permission);
    
    printPermissions(permission);
    
    // 添加写权限
    printf("\n添加写权限...\n");
    permission |= WRITE;  // 等价于 permission = permission | WRITE
    printPermissions(permission);
    
    // 删除读权限
    printf("\n删除读权限...\n");
    permission &= ~READ;  // 等价于 permission = permission & (~READ)
    printPermissions(permission);
    
    // 切换执行权限
    printf("\n切换执行权限...\n");
    permission ^= EXECUTE;  // 有则删除，无则添加
    printPermissions(permission);
    
    return 0;
}
```

**解析**：

1. **检查权限**：`permission & READ`
   - 示例：`5 & 1 = 0101 & 0001 = 0001` → 有读权限

2. **添加权限**：`permission |= WRITE`
   - 示例：`5 | 2 = 0101 | 0010 = 0111` → 添加写权限

3. **删除权限**：`permission &= ~READ`
   - 示例：`5 & ~1 = 0101 & 1110 = 0100` → 删除读权限

4. **切换权限**：`permission ^= EXECUTE`
   - 示例：`5 ^ 4 = 0101 ^ 0100 = 0001` → 切换执行权限

**实际应用**：
- Linux 文件权限：`rwxrwxrwx` (owner/group/others)
- 游戏角色技能系统
- 网络协议标志位

---

### 2.5 运算符优先级挑战 🔴

```c
#include <stdio.h>

int main() {
    printf("========================================\n");
    printf("   运算符优先级挑战\n");
    printf("========================================\n\n");
    
    int a = 5, b = 10, c = 15;
    int result;
    
    // 表达式 1: a + b * c
    result = a + b * c;
    printf("表达式: a + b * c\n");
    printf("计算过程: 5 + 10 * 15 = 5 + 150 = 155\n");
    printf("结果: %d\n", result);
    printf("说明: * 优先级高于 +，先计算乘法\n\n");
    
    // 表达式 2: (a + b) * c
    result = (a + b) * c;
    printf("表达式: (a + b) * c\n");
    printf("计算过程: (5 + 10) * 15 = 15 * 15 = 225\n");
    printf("结果: %d\n", result);
    printf("说明: 括号改变运算顺序\n\n");
    
    // 表达式 3: a++ + ++b（重新初始化）
    a = 5; b = 10; c = 15;
    result = a++ + ++b;
    printf("表达式: a++ + ++b (初始 a=5, b=10)\n");
    printf("计算过程: a++ 使用后自增(5)，++b 先自增后使用(11)\n");
    printf("结果: %d, 之后 a=%d, b=%d\n", result, a, b);
    printf("说明: 前缀++先增后用，后缀++先用后增\n\n");
    
    // 表达式 4: a > b ? a : b（重新初始化）
    a = 5; b = 10;
    result = a > b ? a : b;
    printf("表达式: a > b ? a : b (a=5, b=10)\n");
    printf("计算过程: 5 > 10 ? 5 : 10 → 条件为假，返回 10\n");
    printf("结果: %d\n", result);
    printf("说明: 三目运算符，条件为真返回第一个值，否则返回第二个值\n\n");
    
    // 表达式 5: a & b | c（重新初始化）
    a = 5; b = 10; c = 15;
    result = a & b | c;
    printf("表达式: a & b | c (a=5, b=10, c=15)\n");
    printf("二进制: 0101 & 1010 | 1111\n");
    printf("计算过程: (5 & 10) | 15 = 0 | 15 = 15\n");
    printf("结果: %d\n", result);
    printf("说明: & 优先级高于 |，先计算按位与\n\n");
    
    return 0;
}
```

**关键点总结**：

| 运算符类型 | 优先级（高→低） | 示例 |
|-----------|----------------|------|
| 括号 | 最高 | `()` |
| 一元运算符 | 高 | `++`, `--`, `!`, `~` |
| 算术运算符 | 中高 | `*`, `/`, `%` > `+`, `-` |
| 关系运算符 | 中 | `<`, `>`, `<=`, `>=` > `==`, `!=` |
| 逻辑运算符 | 中低 | `&&` > `||` |
| 三目运算符 | 低 | `? :` |
| 赋值运算符 | 最低 | `=`, `+=`, `-=` |

---

## 第三部分：控制流

### 3.1 成绩等级判定 🟢

```c
#include <stdio.h>

int main() {
    int score;
    
    printf("请输入分数（0-100）: ");
    scanf("%d", &score);
    
    // 输入验证
    if (score < 0 || score > 100) {
        printf("错误：分数必须在 0-100 之间\n");
        return 1;
    }
    
    printf("分数: %d\n", score);
    printf("等级: ");
    
    if (score >= 90) {
        printf("A (优秀)\n");
    } else if (score >= 80) {
        printf("B (良好)\n");
    } else if (score >= 70) {
        printf("C (中等)\n");
    } else if (score >= 60) {
        printf("D (及格)\n");
    } else {
        printf("F (不及格)\n");
    }
    
    return 0;
}
```

**解析**：
- 使用 if-else if-else 多分支结构
- 注意判断顺序：从高到低，避免逻辑错误
- 添加输入验证，提高程序健壮性

**替代方案**（使用 switch，适用于整除10的情况）

```c
switch (score / 10) {
    case 10:
    case 9:
        printf("A (优秀)\n");
        break;
    case 8:
        printf("B (良好)\n");
        break;
    case 7:
        printf("C (中等)\n");
        break;
    case 6:
        printf("D (及格)\n");
        break;
    default:
        printf("F (不及格)\n");
}
```

---

### 3.2 星期查询器 🟢

```c
#include <stdio.h>

int main() {
    int day;
    
    printf("请输入数字（1-7）: ");
    scanf("%d", &day);
    
    switch (day) {
        case 1:
            printf("星期一\n");
            break;
        case 2:
            printf("星期二\n");
            break;
        case 3:
            printf("星期三\n");
            break;
        case 4:
            printf("星期四\n");
            break;
        case 5:
            printf("星期五\n");
            break;
        case 6:
            printf("星期六\n");
            break;
        case 7:
            printf("星期日\n");
            break;
        default:
            printf("错误：输入必须在 1-7 之间\n");
    }
    
    return 0;
}
```

**解析**：
- 每个 case 后必须加 `break`，否则会发生"贯穿"（fall-through）
- `default` 处理无效输入

**拓展**：使用数组优化

```c
const char *weekdays[] = {
    "星期日", "星期一", "星期二", "星期三",
    "星期四", "星期五", "星期六"
};

if (day >= 1 && day <= 7) {
    printf("%s\n", weekdays[day % 7]);
} else {
    printf("错误：输入必须在 1-7 之间\n");
}
```

---

### 3.3 数字求和 🟡

```c
#include <stdio.h>

int main() {
    int n;
    printf("请输入正整数 N: ");
    scanf("%d", &n);
    
    // 方法一：while 循环
    int sum1 = 0, i = 1;
    while (i <= n) {
        sum1 += i;
        i++;
    }
    printf("使用 while 循环: 1 到 %d 的和 = %d\n", n, sum1);
    
    // 方法二：do-while 循环
    int sum2 = 0;
    i = 1;
    do {
        sum2 += i;
        i++;
    } while (i <= n);
    printf("使用 do-while 循环: 1 到 %d 的和 = %d\n", n, sum2);
    
    // 方法三：for 循环
    int sum3 = 0;
    for (i = 1; i <= n; i++) {
        sum3 += i;
    }
    printf("使用 for 循环: 1 到 %d 的和 = %d\n", n, sum3);
    
    // 数学公式验证
    int sum_formula = n * (n + 1) / 2;
    printf("使用数学公式: 1 到 %d 的和 = %d\n", n, sum_formula);
    
    return 0;
}
```

**解析**：

1. **while 循环**：先判断条件，再执行循环体
2. **do-while 循环**：先执行一次循环体，再判断条件（至少执行一次）
3. **for 循环**：最紧凑，适合计数型循环
4. **数学公式**：`S = n(n+1)/2`，时间复杂度 O(1)

**性能对比**：
- 循环方法：O(n)
- 公式方法：O(1)
- 对于 n = 1000000，公式方法快数百万倍

---

### 3.4 素数打印 🟡

```c
#include <stdio.h>
#include <math.h>

int main() {
    int n;
    printf("请输入正整数 N: ");
    scanf("%d", &n);
    
    printf("小于 %d 的素数:\n", n);
    
    for (int num = 2; num < n; num++) {
        int is_prime = 1;  // 假设是素数
        
        // 优化：只需检查到 sqrt(num)
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                is_prime = 0;  // 不是素数
                break;  // 找到一个因子就可以退出
            }
        }
        
        if (is_prime) {
            printf("%d ", num);
        }
    }
    printf("\n");
    
    return 0;
}
```

**解析**：

1. **素数定义**：大于 1 且只能被 1 和自己整除的数
2. **优化技巧**：
   - 只需检查到 √n，因为如果 n 有因子，必有一个 ≤ √n
   - 找到一个因子就可以立即 `break`
3. **时间复杂度**：O(n√n)

**进一步优化**（埃拉托斯特尼筛法）

```c
void sieveOfEratosthenes(int n) {
    int prime[n + 1];
    for (int i = 0; i <= n; i++) prime[i] = 1;
    
    for (int p = 2; p * p <= n; p++) {
        if (prime[p]) {
            for (int i = p * p; i <= n; i += p) {
                prime[i] = 0;
            }
        }
    }
    
    printf("小于 %d 的素数:\n", n);
    for (int i = 2; i < n; i++) {
        if (prime[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}
```

时间复杂度：O(n log log n)

---

### 3.5 数字金字塔 🔴

```c
#include <stdio.h>

int main() {
    int n;
    printf("请输入层数 N (1-9): ");
    scanf("%d", &n);
    
    if (n < 1 || n > 9) {
        printf("错误：N 必须在 1-9 之间\n");
        return 1;
    }
    
    for (int i = 1; i <= n; i++) {
        // 打印前导空格
        for (int j = 0; j < n - i; j++) {
            printf(" ");
        }
        
        // 打印递增数字
        for (int j = 1; j <= i; j++) {
            printf("%d", j);
        }
        
        // 打印递减数字
        for (int j = i - 1; j >= 1; j--) {
            printf("%d", j);
        }
        
        printf("\n");
    }
    
    return 0;
}
```

**解析**：

1. **空格计算**：第 i 行前面有 (n - i) 个空格
2. **递增部分**：1 到 i
3. **递减部分**：i-1 到 1

**规律分析**（以 n=5 为例）：

```
第1行: 4空格 + "1" + ""           → "    1"
第2行: 3空格 + "12" + "1"         → "   121"
第3行: 2空格 + "123" + "21"       → "  12321"
第4行: 1空格 + "1234" + "321"     → " 1234321"
第5行: 0空格 + "12345" + "4321"   → "123454321"
```

**拓展**：字母金字塔

```c
for (int i = 1; i <= n; i++) {
    for (int j = 0; j < n - i; j++) printf(" ");
    for (int j = 0; j < i; j++) printf("%c", 'A' + j);
    for (int j = i - 2; j >= 0; j--) printf("%c", 'A' + j);
    printf("\n");
}
```

输出（n=5）：
```
    A
   ABA
  ABCBA
 ABCDCBA
ABCDEDCBA
```

---

## 第四部分：函数基础

### 4.1 函数封装 - 判断奇偶 🟢

```c
#include <stdio.h>

// 函数声明
int isEven(int n);

int main() {
    int num;
    
    printf("请输入一个整数: ");
    scanf("%d", &num);
    
    if (isEven(num)) {
        printf("%d 是偶数\n", num);
    } else {
        printf("%d 是奇数\n", num);
    }
    
    // 测试多个数字
    printf("\n测试 1 到 10:\n");
    for (int i = 1; i <= 10; i++) {
        printf("%d: %s\n", i, isEven(i) ? "偶数" : "奇数");
    }
    
    return 0;
}

// 函数定义
int isEven(int n) {
    return n % 2 == 0;  // 偶数返回 1，奇数返回 0
}
```

**解析**：
- 函数返回 `int` 类型（0 或 1），可用作布尔值
- `n % 2 == 0` 等价于 `!(n % 2)` 或 `(n & 1) == 0`（位运算）

**拓展**：多个判断函数

```c
int isOdd(int n) { return n % 2 != 0; }
int isPositive(int n) { return n > 0; }
int isNegative(int n) { return n < 0; }
int isZero(int n) { return n == 0; }
```

---

### 4.2 函数封装 - 阶乘计算 🟡

#### 循环实现

```c
#include <stdio.h>

long long factorialIterative(int n) {
    if (n < 0) return -1;  // 负数无阶乘
    if (n == 0 || n == 1) return 1;
    
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}
```

#### 递归实现

```c
long long factorialRecursive(int n) {
    if (n < 0) return -1;
    if (n == 0 || n == 1) return 1;
    return n * factorialRecursive(n - 1);
}
```

#### 主函数

```c
int main() {
    int n;
    printf("请输入一个非负整数: ");
    scanf("%d", &n);
    
    if (n < 0) {
        printf("错误：阶乘仅对非负整数定义\n");
        return 1;
    }
    
    long long result1 = factorialIterative(n);
    long long result2 = factorialRecursive(n);
    
    printf("%d! = %lld (循环方法)\n", n, result1);
    printf("%d! = %lld (递归方法)\n", n, result2);
    
    return 0;
}
```

**性能对比**：

| 方法 | 时间复杂度 | 空间复杂度 | 优点 | 缺点 |
|------|-----------|-----------|------|------|
| 循环 | O(n) | O(1) | 高效、无栈溢出风险 | 代码稍长 |
| 递归 | O(n) | O(n) | 代码简洁、直观 | 可能栈溢出 |

**递归调用过程**（以 5! 为例）：

```
factorial(5)
  → 5 * factorial(4)
    → 4 * factorial(3)
      → 3 * factorial(2)
        → 2 * factorial(1)
          → 1
        → 2 * 1 = 2
      → 3 * 2 = 6
    → 4 * 6 = 24
  → 5 * 24 = 120
```

---

### 4.3 多函数协作 - 温度转换器升级 🟡

```c
#include <stdio.h>

// 函数声明
float celsiusToFahrenheit(float c);
float fahrenheitToCelsius(float f);
float celsiusToKelvin(float c);
void printMenu();

int main() {
    int choice;
    float temp, result;
    
    do {
        printMenu();
        printf("请选择: ");
        scanf("%d", &choice);
        
        if (choice >= 1 && choice <= 3) {
            printf("输入温度: ");
            scanf("%f", &temp);
        }
        
        switch (choice) {
            case 1:
                result = celsiusToFahrenheit(temp);
                printf("%.2f°C = %.2f°F\n\n", temp, result);
                break;
            case 2:
                result = fahrenheitToCelsius(temp);
                printf("%.2f°F = %.2f°C\n\n", temp, result);
                break;
            case 3:
                result = celsiusToKelvin(temp);
                printf("%.2f°C = %.2fK\n\n", temp, result);
                break;
            case 4:
                printf("退出程序\n");
                break;
            default:
                printf("无效选择，请重新输入\n\n");
        }
    } while (choice != 4);
    
    return 0;
}

void printMenu() {
    printf("========================================\n");
    printf("       温度转换器\n");
    printf("========================================\n");
    printf("[1] 摄氏转华氏\n");
    printf("[2] 华氏转摄氏\n");
    printf("[3] 摄氏转开尔文\n");
    printf("[4] 退出\n");
    printf("========================================\n");
}

float celsiusToFahrenheit(float c) {
    return c * 9.0 / 5.0 + 32;
}

float fahrenheitToCelsius(float f) {
    return (f - 32) * 5.0 / 9.0;
}

float celsiusToKelvin(float c) {
    return c + 273.15;
}
```

**设计原则**：
1. **单一职责**：每个函数只做一件事
2. **可复用**：转换函数可在其他程序中使用
3. **易维护**：修改某个转换公式只需改一个函数

**拓展**：添加更多转换

```c
float kelvinToCelsius(float k) { return k - 273.15; }
float fahrenheitToKelvin(float f) { return celsiusToKelvin(fahrenheitToCelsius(f)); }
```

---

### 4.4 数组处理函数 🔴

```c
#include <stdio.h>

// 函数声明
int findMax(int arr[], int size);
int findMin(int arr[], int size);
float average(int arr[], int size);
void printArray(int arr[], int size);

int main() {
    int size;
    printf("请输入数组大小: ");
    scanf("%d", &size);
    
    int arr[size];
    printf("请输入 %d 个整数: ", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("\n");
    printf("数组: ");
    printArray(arr, size);
    
    printf("最大值: %d\n", findMax(arr, size));
    printf("最小值: %d\n", findMin(arr, size));
    printf("平均值: %.2f\n", average(arr, size));
    
    return 0;
}

int findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int findMin(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

float average(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (float)sum / size;
}

void printArray(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}
```

**关键点**：
- 数组作为参数传递时，传递的是指针（地址）
- 必须同时传递数组大小，因为数组名丢失了大小信息
- `int arr[]` 等价于 `int *arr`

**拓展**：更多统计函数

```c
int sum(int arr[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) total += arr[i];
    return total;
}

float median(int arr[], int size) {
    // 需要先排序（后续章节介绍）
    // 返回中位数
}

int count(int arr[], int size, int target) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) count++;
    }
    return count;
}
```

---

### 4.5 递归挑战 - 斐波那契数列 🔴

#### 递归实现（效率低）

```c
long long fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}
```

**问题**：大量重复计算，时间复杂度 O(2^n)

```
fib(5)
  → fib(4) + fib(3)
    → (fib(3) + fib(2)) + (fib(2) + fib(1))
      → ((fib(2) + fib(1)) + (fib(1) + fib(0))) + ...
```

#### 循环实现（高效）

```c
long long fibIterative(int n) {
    if (n <= 1) return n;
    
    long long prev = 0, curr = 1;
    for (int i = 2; i <= n; i++) {
        long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}
```

**时间复杂度**：O(n)，**空间复杂度**：O(1)

#### 优化递归（记忆化）

```c
#include <string.h>

#define MAX_N 100
long long memo[MAX_N];

long long fibMemo(int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];  // 已计算过
    
    memo[n] = fibMemo(n - 1) + fibMemo(n - 2);
    return memo[n];
}

int main() {
    memset(memo, -1, sizeof(memo));  // 初始化为 -1
    printf("fib(40) = %lld\n", fibMemo(40));
    return 0;
}
```

**性能对比**（计算 fib(40)）：

| 方法 | 时间 | 空间复杂度 |
|------|------|-----------|
| 递归 | ~数秒 | O(n) |
| 循环 | 毫秒级 | O(1) |
| 记忆化递归 | 毫秒级 | O(n) |

---

## 第五部分：综合应用

### 5.1 猜数字游戏 🟡

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // 初始化随机数生成器
    srand(time(NULL));
    
    // 生成 1-100 之间的随机数
    int secret = rand() % 100 + 1;
    int guess, attempts = 0;
    
    printf("========================================\n");
    printf("   猜数字游戏（1-100）\n");
    printf("========================================\n\n");
    
    do {
        printf("请输入猜测: ");
        scanf("%d", &guess);
        attempts++;
        
        if (guess < secret) {
            printf("太小了！\n");
        } else if (guess > secret) {
            printf("太大了！\n");
        } else {
            printf("恭喜，猜对了！你用了 %d 次尝试。\n", attempts);
        }
    } while (guess != secret);
    
    // 评价
    if (attempts <= 5) {
        printf("评价: 非常棒！\n");
    } else if (attempts <= 10) {
        printf("评价: 不错！\n");
    } else {
        printf("评价: 继续努力！\n");
    }
    
    return 0;
}
```

**知识点**：
- `srand(time(NULL))`：使用当前时间作为随机种子
- `rand() % 100 + 1`：生成 1-100 之间的随机数
- `do-while` 循环：至少执行一次

**拓展**：二分查找提示

```c
// 计算理论最少次数：log2(100) ≈ 7
int optimal = (int)(log2(100)) + 1;
printf("提示: 理论最少需要 %d 次\n", optimal);
```

---

### 5.2 简易学生成绩管理 🔴

```c
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 10
#define NAME_LENGTH 50

typedef struct {
    char name[NAME_LENGTH];
    int score;
} Student;

void inputStudents(Student students[], int *count);
void displayStudents(Student students[], int count);
void calculateStatistics(Student students[], int count);
void searchStudent(Student students[], int count);

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    
    inputStudents(students, &count);
    displayStudents(students, count);
    calculateStatistics(students, count);
    searchStudent(students, count);
    
    return 0;
}

void inputStudents(Student students[], int *count) {
    printf("请输入学生人数（最多 %d 人）: ", MAX_STUDENTS);
    scanf("%d", count);
    
    if (*count > MAX_STUDENTS) {
        *count = MAX_STUDENTS;
        printf("人数超限，仅输入前 %d 人\n", MAX_STUDENTS);
    }
    
    for (int i = 0; i < *count; i++) {
        printf("请输入第 %d 个学生的姓名和成绩: ", i + 1);
        scanf("%s %d", students[i].name, &students[i].score);
    }
}

void displayStudents(Student students[], int count) {
    printf("\n========================================\n");
    printf("   学生信息\n");
    printf("========================================\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %-20s %d\n", i + 1, students[i].name, students[i].score);
    }
}

void calculateStatistics(Student students[], int count) {
    if (count == 0) return;
    
    int sum = 0, max = students[0].score, min = students[0].score;
    int maxIndex = 0, minIndex = 0;
    
    for (int i = 0; i < count; i++) {
        sum += students[i].score;
        if (students[i].score > max) {
            max = students[i].score;
            maxIndex = i;
        }
        if (students[i].score < min) {
            min = students[i].score;
            minIndex = i;
        }
    }
    
    printf("\n========================================\n");
    printf("   统计信息\n");
    printf("========================================\n");
    printf("平均分: %.2f\n", (float)sum / count);
    printf("最高分: %d (%s)\n", max, students[maxIndex].name);
    printf("最低分: %d (%s)\n", min, students[minIndex].name);
}

void searchStudent(Student students[], int count) {
    char name[NAME_LENGTH];
    printf("\n请输入要查找的学生姓名: ");
    scanf("%s", name);
    
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("找到学生: %s, 成绩: %d\n", students[i].name, students[i].score);
            return;
        }
    }
    printf("未找到学生: %s\n", name);
}
```

**知识点**：
- 结构体（struct）：组合不同类型的数据
- 数组与结构体结合
- 字符串处理（`strcmp`）
- 指针传递（修改 count 值）

**拓展功能**：
- 成绩排序
- 添加/删除学生
- 保存到文件

---

### 5.3 进制转换器 🔴

```c
#include <stdio.h>
#include <string.h>

void decimalToBinary(int n);
void decimalToOctal(int n);
void decimalToHex(int n);
int binaryToDecimal(char binary[]);
void printMenu();

int main() {
    int choice, decimal;
    char binary[33];  // 最多 32 位二进制
    
    do {
        printMenu();
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("输入十进制数: ");
                scanf("%d", &decimal);
                printf("二进制: ");
                decimalToBinary(decimal);
                printf("\n\n");
                break;
            case 2:
                printf("输入十进制数: ");
                scanf("%d", &decimal);
                printf("八进制: ");
                decimalToOctal(decimal);
                printf("\n\n");
                break;
            case 3:
                printf("输入十进制数: ");
                scanf("%d", &decimal);
                printf("十六进制: ");
                decimalToHex(decimal);
                printf("\n\n");
                break;
            case 4:
                printf("输入二进制数: ");
                scanf("%s", binary);
                printf("十进制: %d\n\n", binaryToDecimal(binary));
                break;
            case 5:
                printf("退出程序\n");
                break;
            default:
                printf("无效选择\n\n");
        }
    } while (choice != 5);
    
    return 0;
}

void printMenu() {
    printf("========================================\n");
    printf("       进制转换器\n");
    printf("========================================\n");
    printf("[1] 十进制转二进制\n");
    printf("[2] 十进制转八进制\n");
    printf("[3] 十进制转十六进制\n");
    printf("[4] 二进制转十进制\n");
    printf("[5] 退出\n");
    printf("========================================\n");
}

void decimalToBinary(int n) {
    if (n == 0) {
        printf("0");
        return;
    }
    
    char binary[33];
    int index = 0;
    
    while (n > 0) {
        binary[index++] = (n % 2) + '0';
        n /= 2;
    }
    
    // 反向输出
    for (int i = index - 1; i >= 0; i--) {
        printf("%c", binary[i]);
    }
}

void decimalToOctal(int n) {
    printf("%o", n);  // 使用格式说明符
}

void decimalToHex(int n) {
    printf("%X", n);  // 使用格式说明符（大写）
}

int binaryToDecimal(char binary[]) {
    int decimal = 0;
    int len = strlen(binary);
    
    for (int i = 0; i < len; i++) {
        if (binary[i] == '1') {
            decimal = decimal * 2 + 1;
        } else if (binary[i] == '0') {
            decimal = decimal * 2;
        } else {
            printf("错误：无效的二进制数\n");
            return -1;
        }
    }
    
    return decimal;
}
```

**算法原理**：

1. **十进制转二进制**：不断除以 2，记录余数，倒序输出
   ```
   42 → 42/2=21...0
        21/2=10...1
        10/2=5...0
        5/2=2...1
        2/2=1...0
        1/2=0...1
   结果: 101010
   ```

2. **二进制转十进制**：从左到右，每位乘以 2 的幂次
   ```
   101010 → 1×2^5 + 0×2^4 + 1×2^3 + 0×2^2 + 1×2^1 + 0×2^0
         → 32 + 0 + 8 + 0 + 2 + 0 = 42
   ```

**拓展**：
- 任意进制转换
- 处理负数和浮点数
- 添加输入验证

---

## 总结与学习建议

### 完成练习后你应该掌握的能力

✅ **基础语法**：
- 熟练使用各种数据类型
- 理解变量作用域和生命周期
- 掌握运算符优先级和表达式求值

✅ **控制流**：
- 灵活运用条件语句（if、switch）
- 熟练使用三种循环结构
- 理解 break 和 continue 的使用场景

✅ **函数设计**：
- 能够将问题分解为多个函数
- 理解值传递和引用传递的区别
- 掌握递归的思想和优化方法

✅ **综合应用**：
- 能够设计简单的菜单驱动程序
- 具备基本的算法思维
- 养成良好的编码规范

### 下一步学习路径

1. **02_控制结构**：深入学习复杂的控制流技巧
2. **03_函数与数组**：掌握数组、多维数组、字符串处理
3. **04_指针与内存**：理解 C 语言最核心的特性
4. **05_文件操作**：学习数据持久化

### 推荐练习方式

1. **先独立思考**：不要急于查看答案
2. **多次迭代**：完成后思考能否优化
3. **对比方法**：学习不同解法的优缺点
4. **编写测试**：用不同输入验证程序的正确性
5. **代码复盘**：定期回顾之前写的代码

---

**继续加油，编程之路任重道远！** 🚀
