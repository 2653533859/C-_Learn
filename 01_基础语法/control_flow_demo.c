/*
 * 文件名: control_flow_demo.c
 * 功能: 演示 C 语言控制流结构
 * 内容: 条件语句(if/switch)、循环语句(while/do-while/for)、跳转语句(break/continue)
 */

#include <stdio.h>

// 函数声明
void demonstrate_if_else(void);
void demonstrate_switch(void);
void demonstrate_while_loop(void);
void demonstrate_do_while_loop(void);
void demonstrate_for_loop(void);
void demonstrate_nested_loops(void);
void demonstrate_break_continue(void);

int main() {
    printf("========================================\n");
    printf("   C 语言控制流综合演示程序\n");
    printf("========================================\n\n");
    
    demonstrate_if_else();
    demonstrate_switch();
    demonstrate_while_loop();
    demonstrate_do_while_loop();
    demonstrate_for_loop();
    demonstrate_nested_loops();
    demonstrate_break_continue();
    
    printf("\n========================================\n");
    printf("   演示完成！\n");
    printf("========================================\n");
    
    return 0;
}

/*
 * 函数: demonstrate_if_else
 * 功能: 演示 if-else 条件语句
 */
void demonstrate_if_else(void) {
    printf("【1. if-else 条件语句演示】\n");
    printf("--------------------\n");
    
    // 简单 if 语句
    int age = 18;
    printf("年龄: %d\n", age);
    if (age >= 18) {
        printf("  → 已成年\n");
    }
    
    // if-else 语句
    int score = 75;
    printf("\n分数: %d\n", score);
    if (score >= 60) {
        printf("  → 及格\n");
    } else {
        printf("  → 不及格\n");
    }
    
    // if-else if-else 多分支
    score = 85;
    printf("\n分数: %d\n", score);
    if (score >= 90) {
        printf("  → 等级: 优秀 (A)\n");
    } else if (score >= 80) {
        printf("  → 等级: 良好 (B)\n");
    } else if (score >= 70) {
        printf("  → 等级: 中等 (C)\n");
    } else if (score >= 60) {
        printf("  → 等级: 及格 (D)\n");
    } else {
        printf("  → 等级: 不及格 (F)\n");
    }
    
    // 嵌套 if
    int num = 24;
    printf("\n数字: %d\n", num);
    if (num > 0) {
        if (num % 2 == 0) {
            printf("  → 正偶数\n");
        } else {
            printf("  → 正奇数\n");
        }
    } else if (num < 0) {
        printf("  → 负数\n");
    } else {
        printf("  → 零\n");
    }
    
    // 条件运算符（三目运算符）
    int a = 10, b = 20;
    int max = (a > b) ? a : b;
    printf("\n三目运算符: max(%d, %d) = %d\n", a, b, max);
    
    printf("\n");
}

/*
 * 函数: demonstrate_switch
 * 功能: 演示 switch 语句
 */
void demonstrate_switch(void) {
    printf("【2. switch 语句演示】\n");
    printf("--------------------\n");
    
    // 基本 switch
    int day = 3;
    printf("星期 %d: ", day);
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
            printf("无效日期\n");
    }
    
    // 多个 case 共享代码（故意不加 break）
    char grade = 'B';
    printf("\n等级 '%c': ", grade);
    switch (grade) {
        case 'A':
        case 'a':
            printf("优秀，继续保持！\n");
            break;
        case 'B':
        case 'b':
            printf("良好，再接再厉！\n");
            break;
        case 'C':
        case 'c':
            printf("中等，需要努力！\n");
            break;
        case 'D':
        case 'd':
        case 'F':
        case 'f':
            printf("不及格，加倍努力！\n");
            break;
        default:
            printf("无效等级\n");
    }
    
    // 简单计算器
    char op = '+';
    int x = 15, y = 5;
    printf("\n简单计算器: %d %c %d = ", x, op, y);
    switch (op) {
        case '+':
            printf("%d\n", x + y);
            break;
        case '-':
            printf("%d\n", x - y);
            break;
        case '*':
            printf("%d\n", x * y);
            break;
        case '/':
            if (y != 0) {
                printf("%.2f\n", (float)x / y);
            } else {
                printf("错误：除数不能为零\n");
            }
            break;
        default:
            printf("错误：不支持的运算符\n");
    }
    
    printf("\n");
}

/*
 * 函数: demonstrate_while_loop
 * 功能: 演示 while 循环
 */
void demonstrate_while_loop(void) {
    printf("【3. while 循环演示】\n");
    printf("--------------------\n");
    
    // 简单 while 循环：输出 1 到 5
    printf("输出 1 到 5: ");
    int i = 1;
    while (i <= 5) {
        printf("%d ", i);
        i++;
    }
    printf("\n");
    
    // 计算 1 到 100 的和
    int sum = 0;
    int n = 1;
    while (n <= 100) {
        sum += n;
        n++;
    }
    printf("1 到 100 的和: %d\n", sum);
    
    // 阶乘计算
    int num = 5;
    int factorial = 1;
    int temp = num;
    while (temp > 0) {
        factorial *= temp;
        temp--;
    }
    printf("%d! = %d\n", num, factorial);
    
    // 找出第一个大于 1000 的 2 的幂
    int power = 1;
    int exponent = 0;
    while (power <= 1000) {
        power *= 2;
        exponent++;
    }
    printf("第一个大于 1000 的 2 的幂: 2^%d = %d\n", exponent, power);
    
    printf("\n");
}

/*
 * 函数: demonstrate_do_while_loop
 * 功能: 演示 do-while 循环
 */
void demonstrate_do_while_loop(void) {
    printf("【4. do-while 循环演示】\n");
    printf("--------------------\n");
    
    // do-while 至少执行一次
    printf("输出 1 到 3: ");
    int i = 1;
    do {
        printf("%d ", i);
        i++;
    } while (i <= 3);
    printf("\n");
    
    // 即使条件不满足也会执行一次
    printf("条件初始为假的 do-while: ");
    int j = 10;
    do {
        printf("执行了一次 (j=%d)\n", j);
        j++;
    } while (j < 5);
    
    // 菜单驱动示例（模拟）
    printf("\n菜单驱动示例（自动选择）:\n");
    int choice = 0;
    int count = 0;
    do {
        printf("  [1] 新建  [2] 打开  [3] 退出\n");
        // 模拟用户输入
        count++;
        if (count == 1) choice = 1;
        else if (count == 2) choice = 2;
        else choice = 3;
        
        printf("  选择: %d\n", choice);
        
        switch (choice) {
            case 1:
                printf("  → 新建文件\n");
                break;
            case 2:
                printf("  → 打开文件\n");
                break;
            case 3:
                printf("  → 退出程序\n");
                break;
            default:
                printf("  → 无效选择\n");
        }
    } while (choice != 3);
    
    printf("\n");
}

/*
 * 函数: demonstrate_for_loop
 * 功能: 演示 for 循环
 */
void demonstrate_for_loop(void) {
    printf("【5. for 循环演示】\n");
    printf("--------------------\n");
    
    // 基本 for 循环
    printf("输出 0 到 4: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    // 递减循环
    printf("倒计时 5 到 1: ");
    for (int i = 5; i >= 1; i--) {
        printf("%d ", i);
    }
    printf("\n");
    
    // 步长为 2
    printf("偶数 0 到 10: ");
    for (int i = 0; i <= 10; i += 2) {
        printf("%d ", i);
    }
    printf("\n");
    
    // 计算平方和
    int sum_of_squares = 0;
    for (int i = 1; i <= 10; i++) {
        sum_of_squares += i * i;
    }
    printf("1² + 2² + ... + 10² = %d\n", sum_of_squares);
    
    // 无限循环（带 break）
    printf("找出第一个能被 7 整除的三位数: ");
    for (int i = 100; ; i++) {  // 无结束条件
        if (i % 7 == 0) {
            printf("%d\n", i);
            break;
        }
    }
    
    printf("\n");
}

/*
 * 函数: demonstrate_nested_loops
 * 功能: 演示嵌套循环
 */
void demonstrate_nested_loops(void) {
    printf("【6. 嵌套循环演示】\n");
    printf("--------------------\n");
    
    // 乘法表（九九表）
    printf("九九乘法表:\n");
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= i; j++) {
            printf("%d*%d=%2d ", j, i, i * j);
        }
        printf("\n");
    }
    
    // 打印矩形
    printf("\n打印 4x6 矩形:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            printf("* ");
        }
        printf("\n");
    }
    
    // 打印直角三角形
    printf("\n打印直角三角形:\n");
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }
    
    // 打印等腰三角形
    printf("\n打印等腰三角形:\n");
    int height = 5;
    for (int i = 1; i <= height; i++) {
        // 打印空格
        for (int j = 1; j <= height - i; j++) {
            printf(" ");
        }
        // 打印星号
        for (int j = 1; j <= 2 * i - 1; j++) {
            printf("*");
        }
        printf("\n");
    }
    
    printf("\n");
}

/*
 * 函数: demonstrate_break_continue
 * 功能: 演示 break 和 continue 语句
 */
void demonstrate_break_continue(void) {
    printf("【7. break 和 continue 演示】\n");
    printf("--------------------\n");
    
    // break 示例：找到第一个目标后退出
    printf("查找数组中第一个负数:\n");
    int numbers[] = {10, 5, -3, 8, -1, 6};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    for (int i = 0; i < size; i++) {
        if (numbers[i] < 0) {
            printf("  找到第一个负数: %d (索引 %d)\n", numbers[i], i);
            break;  // 立即退出循环
        }
    }
    
    // continue 示例：跳过偶数
    printf("\n输出 1 到 10 的奇数: ");
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  // 跳过本次迭代
        }
        printf("%d ", i);
    }
    printf("\n");
    
    // break 在嵌套循环中的使用
    printf("\n在二维数组中查找目标值 5:\n");
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    int found = 0;
    int target = 5;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (matrix[i][j] == target) {
                printf("  找到 %d 在位置 [%d][%d]\n", target, i, j);
                found = 1;
                break;  // 只退出内层循环
            }
        }
        if (found) break;  // 退出外层循环
    }
    
    // continue 跳过特定条件
    printf("\n计算 1 到 20 中非 3 的倍数的和: ");
    int sum = 0;
    for (int i = 1; i <= 20; i++) {
        if (i % 3 == 0) {
            continue;  // 跳过 3 的倍数
        }
        sum += i;
    }
    printf("%d\n", sum);
    
    // 综合示例：素数判断
    printf("\n输出 2 到 30 之间的素数: ");
    for (int num = 2; num <= 30; num++) {
        int is_prime = 1;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                is_prime = 0;
                break;  // 不是素数，提前退出
            }
        }
        if (is_prime) {
            printf("%d ", num);
        }
    }
    printf("\n");
    
    printf("\n");
}
