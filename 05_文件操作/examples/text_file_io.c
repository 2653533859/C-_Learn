#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    const char *filename = "sample_text.txt";
    const char *lines[] = {
        "C programming makes file I/O manageable.\n",
        "Always check the return value of fopen.\n",
        "Remember to close files to flush buffers.\n"
    };
    size_t line_count = sizeof(lines) / sizeof(lines[0]);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < line_count; ++i) {
        if (fputs(lines[i], fp) == EOF) {
            perror("fputs");
            fclose(fp);
            return EXIT_FAILURE;
        }
    }

    if (fclose(fp) == EOF) {
        perror("fclose");
        return EXIT_FAILURE;
    }

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    char buffer[128];
    printf("Reading back from %s:\n", filename);
    while (fgets(buffer, sizeof buffer, fp) != NULL) {
        printf("%s", buffer);
    }

    if (ferror(fp)) {
        perror("fgets");
        fclose(fp);
        return EXIT_FAILURE;
    }

    if (fclose(fp) == EOF) {
        perror("fclose");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
