# 文件操作练习题参考答案

以下示例代码仅供参考，实际实现时请根据需求进行拓展或优化。所有示例均假设使用 `gcc -Wall -Wextra -std=c11` 进行编译。

---

## 练习 1：日志等级统计

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <logfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    long counts[4] = {0};
    char buffer[1024];

    while (fgets(buffer, sizeof buffer, fp)) {
        if (strstr(buffer, "[INFO]")) {
            ++counts[0];
        } else if (strstr(buffer, "[WARN]")) {
            ++counts[1];
        } else if (strstr(buffer, "[ERROR]")) {
            ++counts[2];
        } else {
            ++counts[3];
        }
    }

    if (ferror(fp)) {
        perror("fgets");
        fclose(fp);
        return EXIT_FAILURE;
    }

    fclose(fp);

    printf("INFO   : %ld\n", counts[0]);
    printf("WARN   : %ld\n", counts[1]);
    printf("ERROR  : %ld\n", counts[2]);
    printf("UNKNOWN: %ld\n", counts[3]);

    return EXIT_SUCCESS;
}
```

---

## 练习 2：二进制文件复制

```c
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <src> <dst>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *src = fopen(argv[1], "rb");
    if (src == NULL) {
        perror("fopen src");
        return EXIT_FAILURE;
    }

    FILE *dst = fopen(argv[2], "wb");
    if (dst == NULL) {
        perror("fopen dst");
        fclose(src);
        return EXIT_FAILURE;
    }

    unsigned char buffer[4096];
    size_t total = 0;
    size_t nread;

    while ((nread = fread(buffer, 1, sizeof buffer, src)) > 0) {
        size_t nwritten = fwrite(buffer, 1, nread, dst);
        if (nwritten != nread) {
            perror("fwrite");
            fclose(src);
            fclose(dst);
            return EXIT_FAILURE;
        }
        total += nread;
    }

    if (ferror(src)) {
        perror("fread");
        fclose(src);
        fclose(dst);
        return EXIT_FAILURE;
    }

    if (fclose(src) == EOF) {
        perror("fclose src");
    }
    if (fclose(dst) == EOF) {
        perror("fclose dst");
    }

    printf("Copied %zu bytes from %s to %s\n", total, argv[1], argv[2]);
    return EXIT_SUCCESS;
}
```

> 若需要校验文件大小一致，可在复制完成后重新打开两个文件，使用 `fseek`/`ftell` 获取字节数并比较。

---

## 练习 3：文件统计器

```c
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int is_whitespace(int ch) {
    return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r' || ch == '\f' || ch == '\v';
}

static FILE *open_stream(const char *path, FILE **need_close) {
    if (strcmp(path, "-") == 0) {
        *need_close = NULL;
        return stdin;
    }
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        perror("fopen");
        return NULL;
    }
    *need_close = fp;
    return fp;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file|- >\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *need_close = NULL;
    FILE *fp = open_stream(argv[1], &need_close);
    if (fp == NULL) {
        return EXIT_FAILURE;
    }

    long lines = 0, words = 0, bytes = 0;
    int ch;
    int in_word = 0;

    while ((ch = fgetc(fp)) != EOF) {
        ++bytes;
        if (ch == '\n') {
            ++lines;
        }

        if (is_whitespace(ch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            ++words;
        }
    }

    if (ferror(fp)) {
        perror("fgetc");
        if (need_close) {
            fclose(need_close);
        }
        return EXIT_FAILURE;
    }

    if (need_close && fclose(need_close) == EOF) {
        perror("fclose");
    }

    printf("Lines: %ld, Words: %ld, Bytes: %ld\n", lines, words, bytes);
    return EXIT_SUCCESS;
}
```

---

## 练习 4：部分文件提取

```c
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static long read_long(const char *text) {
    char *end = NULL;
    long value = strtol(text, &end, 10);
    if (end == text || *end != '\0') {
        fprintf(stderr, "Invalid number: %s\n", text);
        exit(EXIT_FAILURE);
    }
    return value;
}

int main(int argc, char *argv[]) {
    if (argc < 4 || argc > 5) {
        fprintf(stderr, "Usage: %s <file> <offset> <length> [output]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *path = argv[1];
    long offset = read_long(argv[2]);
    long length = read_long(argv[3]);
    const char *out_path = (argc == 5) ? argv[4] : NULL;

    if (offset < 0 || length <= 0) {
        fprintf(stderr, "Offset must be >= 0 and length > 0\n");
        return EXIT_FAILURE;
    }

    FILE *in = fopen(path, "rb");
    if (in == NULL) {
        perror("fopen input");
        return EXIT_FAILURE;
    }

    if (fseek(in, 0, SEEK_END) != 0) {
        perror("fseek end");
        fclose(in);
        return EXIT_FAILURE;
    }

    long size = ftell(in);
    if (size == -1L) {
        perror("ftell");
        fclose(in);
        return EXIT_FAILURE;
    }

    if (offset > size) {
        fprintf(stderr, "Offset exceeds file size (%ld)\n", size);
        fclose(in);
        return EXIT_FAILURE;
    }

    if (fseek(in, offset, SEEK_SET) != 0) {
        perror("fseek set");
        fclose(in);
        return EXIT_FAILURE;
    }

    if (length > size - offset) {
        length = size - offset;
    }

    FILE *out = stdout;
    if (out_path != NULL) {
        out = fopen(out_path, "wb");
        if (out == NULL) {
            perror("fopen output");
            fclose(in);
            return EXIT_FAILURE;
        }
    }

    unsigned char buffer[4096];
    long remaining = length;
    while (remaining > 0) {
        size_t chunk = (remaining < (long)sizeof buffer) ? (size_t)remaining : sizeof buffer;
        size_t nread = fread(buffer, 1, chunk, in);
        if (nread == 0) {
            if (ferror(in)) {
                perror("fread");
                break;
            }
            if (feof(in)) {
                break;
            }
        }
        size_t nwritten = fwrite(buffer, 1, nread, out);
        if (nwritten != nread) {
            perror("fwrite");
            break;
        }
        remaining -= (long)nread;
    }

    if (fclose(in) == EOF) {
        perror("fclose input");
    }
    if (out_path != NULL && fclose(out) == EOF) {
        perror("fclose output");
    }

    return EXIT_SUCCESS;
}
```

> 可扩展思路：加入 `--buffer-size=N` 选项、自定义输出格式、支持按行提取等功能。
