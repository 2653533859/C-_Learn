#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[32];
    int level;
    double completion;
} Task;

static void print_task(const Task *task) {
    printf("%-10s | Level: %2d | Progress: %5.1f%%\n",
           task->name, task->level, task->completion * 100.0);
}

int main(void) {
    const char *filename = "tasks.bin";
    Task tasks[] = {
        {"Scanner", 1, 0.35},
        {"Parser", 2, 0.75},
        {"Emitter", 3, 0.90}
    };
    size_t count = sizeof(tasks) / sizeof(tasks[0]);

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    size_t written = fwrite(tasks, sizeof(Task), count, fp);
    if (written != count) {
        perror("fwrite");
        fclose(fp);
        return EXIT_FAILURE;
    }

    if (fclose(fp) == EOF) {
        perror("fclose");
        return EXIT_FAILURE;
    }

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    Task buffer[4];
    size_t read_count = fread(buffer, sizeof(Task), count, fp);
    if (read_count != count) {
        if (ferror(fp)) {
            perror("fread");
            fclose(fp);
            return EXIT_FAILURE;
        }
    }

    if (fclose(fp) == EOF) {
        perror("fclose");
        return EXIT_FAILURE;
    }

    printf("Loaded %zu tasks from %s:\n", read_count, filename);
    for (size_t i = 0; i < read_count; ++i) {
        print_task(&buffer[i]);
    }

    return EXIT_SUCCESS;
}
