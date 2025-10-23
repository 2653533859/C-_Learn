/*
 * 文件名: basic_syntax_demo.c
 * 功能: 演示 C 语言基础语法要素
 * 内容: 数据类型、变量、常量、运算符、表达式
 */

#include <stdio.h>
#include <limits.h>  // 包含整型范围常量
#include <float.h>   // 包含浮点型范围常量

// 全局常量定义
#define PI 3.14159265
#define MAX_NAME_LENGTH 50

// 全局变量（示例用，实际开发中应谨慎使用）
int global_counter = 0;

// 函数声明
void demonstrate_data_types(void);
void demonstrate_variables(void);
void demonstrate_constants(void);
void demonstrate_operators(void);
void demonstrate_type_conversion(void);

int main() {
    printf("========================================\n");
    printf("   C 语言基础语法综合演示程序\n");
    printf("========================================\n\n");
    
    demonstrate_data_types();
    demonstrate_variables();
    demonstrate_constants();
    demonstrate_operators();
    demonstrate_type_conversion();
    
    printf("\n========================================\n");
    printf("   演示完成！\n");
    printf("========================================\n");
    
    return 0;
}

/*
 * 函数: demonstrate_data_types
 * 功能: 演示各种基本数据类型及其大小
 */
void demonstrate_data_types(void) {
    printf("【1. 数据类型演示】\n");
    printf("--------------------\n");
    
    // 整型
    char c = 'A';
    short s = 32767;
    int i = 2147483647;
    long l = 2147483647L;
    long long ll = 9223372036854775807LL;
    
    // 无符号整型
    unsigned int ui = 4294967295U;
    
    // 浮点型
    float f = 3.14159f;
    double d = 3.141592653589793;
    long double ld = 3.141592653589793238L;
    
    // 输出类型及其大小
    printf("类型          大小(字节)  示例值\n");
    printf("char          %2lu        '%c' (ASCII: %d)\n", sizeof(char), c, c);
    printf("short         %2lu        %d\n", sizeof(short), s);
    printf("int           %2lu        %d\n", sizeof(int), i);
    printf("long          %2lu        %ld\n", sizeof(long), l);
    printf("long long     %2lu        %lld\n", sizeof(long long), ll);
    printf("unsigned int  %2lu        %u\n", sizeof(unsigned int), ui);
    printf("float         %2lu        %.5f\n", sizeof(float), f);
    printf("double        %2lu        %.15f\n", sizeof(double), d);
    printf("long double   %2lu        %.18Lf\n", sizeof(long double), ld);
    
    // 显示取值范围
    printf("\n整型取值范围:\n");
    printf("int:          %d ~ %d\n", INT_MIN, INT_MAX);
    printf("unsigned int: 0 ~ %u\n", UINT_MAX);
    
    printf("\n");
}

/*
 * 函数: demonstrate_variables
 * 功能: 演示变量的声明、初始化、作用域
 */
void demonstrate_variables(void) {
    printf("【2. 变量演示】\n");
    printf("--------------------\n");
    
    // 局部变量
    int local_var = 100;
    printf("局部变量: local_var = %d\n", local_var);
    
    // 静态局部变量（函数调用间保持值）
    static int static_count = 0;
    static_count++;
    printf("静态局部变量: static_count = %d\n", static_count);
    
    // 全局变量
    global_counter++;
    printf("全局变量: global_counter = %d\n", global_counter);
    
    // 代码块作用域
    {
        int block_var = 50;
        printf("代码块内变量: block_var = %d\n", block_var);
        // block_var 在此代码块结束后销毁
    }
    // printf("%d", block_var);  // 错误：block_var 已不存在
    
    // 多变量声明
    int x = 1, y = 2, z = 3;
    printf("多变量声明: x=%d, y=%d, z=%d\n", x, y, z);
    
    // 交换变量（使用临时变量）
    int a = 10, b = 20, temp;
    printf("交换前: a=%d, b=%d\n", a, b);
    temp = a;
    a = b;
    b = temp;
    printf("交换后: a=%d, b=%d\n", a, b);
    
    // 使用异或交换（无需临时变量，但可读性差）
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    printf("异或交换后: a=%d, b=%d\n", a, b);
    
    printf("\n");
}

/*
 * 函数: demonstrate_constants
 * 功能: 演示常量的定义与使用
 */
void demonstrate_constants(void) {
    printf("【3. 常量演示】\n");
    printf("--------------------\n");
    
    // 使用 #define 定义的常量
    printf("宏常量 PI = %.8f\n", PI);
    printf("宏常量 MAX_NAME_LENGTH = %d\n", MAX_NAME_LENGTH);
    
    // 使用 const 关键字
    const int MAX_STUDENTS = 50;
    const double TAX_RATE = 0.08;
    
    printf("const 常量 MAX_STUDENTS = %d\n", MAX_STUDENTS);
    printf("const 常量 TAX_RATE = %.2f\n", TAX_RATE);
    
    // 字面常量
    printf("整型字面常量: %d\n", 42);
    printf("浮点字面常量: %.2f\n", 3.14);
    printf("字符字面常量: '%c'\n", 'X');
    printf("字符串字面常量: \"%s\"\n", "Hello, World!");
    
    // 枚举常量
    enum Weekday { MON = 1, TUE, WED, THU, FRI, SAT, SUN };
    enum Weekday today = WED;
    printf("枚举常量: today = %d (星期三)\n", today);
    
    printf("\n");
}

/*
 * 函数: demonstrate_operators
 * 功能: 演示各类运算符的使用
 */
void demonstrate_operators(void) {
    printf("【4. 运算符演示】\n");
    printf("--------------------\n");
    
    // 算术运算符
    int a = 10, b = 3;
    printf("算术运算 (a=10, b=3):\n");
    printf("  a + b = %d\n", a + b);
    printf("  a - b = %d\n", a - b);
    printf("  a * b = %d\n", a * b);
    printf("  a / b = %d (整数除法)\n", a / b);
    printf("  a %% b = %d (取模)\n", a % b);
    
    // 自增自减
    int x = 5;
    int result;
    printf("\n自增自减 (x=5):\n");
    result = x++;
    printf("  x++ = %d, 之后 x = %d\n", result, x);
    result = ++x;
    printf("  ++x = %d, 之后 x = %d\n", result, x);
    x = 5;
    result = x--;
    printf("  x-- = %d, 之后 x = %d\n", result, x);
    result = --x;
    printf("  --x = %d, 之后 x = %d\n", result, x);
    
    // 关系运算符
    printf("\n关系运算 (a=10, b=3):\n");
    printf("  a == b: %d\n", a == b);
    printf("  a != b: %d\n", a != b);
    printf("  a > b:  %d\n", a > b);
    printf("  a < b:  %d\n", a < b);
    printf("  a >= b: %d\n", a >= b);
    printf("  a <= b: %d\n", a <= b);
    
    // 逻辑运算符
    int p = 1, q = 0;
    printf("\n逻辑运算 (p=1, q=0):\n");
    printf("  p && q: %d\n", p && q);
    printf("  p || q: %d\n", p || q);
    printf("  !p:     %d\n", !p);
    printf("  !q:     %d\n", !q);
    
    // 位运算符
    unsigned char m = 0b00001111;  // 15
    unsigned char n = 0b00110011;  // 51
    printf("\n位运算 (m=0x%X, n=0x%X):\n", m, n);
    printf("  m & n:  0x%X (%u)\n", m & n, m & n);
    printf("  m | n:  0x%X (%u)\n", m | n, m | n);
    printf("  m ^ n:  0x%X (%u)\n", m ^ n, m ^ n);
    printf("  ~m:     0x%X (%u)\n", (unsigned char)~m, (unsigned char)~m);
    printf("  m << 2: 0x%X (%u)\n", m << 2, m << 2);
    printf("  m >> 2: 0x%X (%u)\n", m >> 2, m >> 2);
    
    // 赋值运算符
    int num = 100;
    printf("\n赋值运算 (num=100):\n");
    printf("  num += 10: %d\n", num += 10);
    printf("  num -= 5:  %d\n", num -= 5);
    printf("  num *= 2:  %d\n", num *= 2);
    printf("  num /= 4:  %d\n", num /= 4);
    printf("  num %%= 7:  %d\n", num %= 7);
    
    // 三目运算符
    int max = (a > b) ? a : b;
    int min = (a < b) ? a : b;
    printf("\n三目运算符:\n");
    printf("  max(10, 3) = %d\n", max);
    printf("  min(10, 3) = %d\n", min);
    
    // sizeof 运算符
    printf("\nsizeof 运算符:\n");
    printf("  sizeof(int) = %lu\n", sizeof(int));
    printf("  sizeof(a) = %lu\n", sizeof(a));
    
    printf("\n");
}

/*
 * 函数: demonstrate_type_conversion
 * 功能: 演示类型转换（隐式和显式）
 */
void demonstrate_type_conversion(void) {
    printf("【5. 类型转换演示】\n");
    printf("--------------------\n");
    
    // 隐式转换（自动类型提升）
    int i = 10;
    float f = 3.5f;
    double result = i + f;  // i 自动转换为 float
    printf("隐式转换: int(10) + float(3.5) = %.2f\n", result);
    
    // 整数除法与浮点除法
    int a = 7, b = 2;
    printf("\n整数除法与浮点除法:\n");
    printf("  7 / 2 = %d (整数除法)\n", a / b);
    printf("  7 / 2.0 = %.2f (浮点除法)\n", a / 2.0);
    printf("  (float)7 / 2 = %.2f (显式转换)\n", (float)a / b);
    
    // 显式转换（强制类型转换）
    double pi = 3.14159;
    int truncated = (int)pi;
    printf("\n显式转换:\n");
    printf("  (int)%.5f = %d (截断小数)\n", pi, truncated);
    
    // 字符与整数的转换
    char ch = 'A';
    int ascii = (int)ch;
    printf("\n字符与整数:\n");
    printf("  字符 '%c' 的 ASCII 值 = %d\n", ch, ascii);
    printf("  ASCII 值 66 对应字符 = '%c'\n", (char)66);
    
    // 溢出示例
    unsigned char c = 255;
    printf("\n溢出示例:\n");
    printf("  unsigned char (255) + 1 = %u (溢出)\n", (unsigned char)(c + 1));
    
    printf("\n");
}
