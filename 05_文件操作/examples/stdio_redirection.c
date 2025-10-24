#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buffer[256];
    size_t total_bytes = 0;
    size_t line_count = 0;

    while (fgets(buffer, sizeof buffer, stdin)) {
        size_t len = strlen(buffer);
        total_bytes += len;
        ++line_count;
        if (fputs(buffer, stdout) == EOF) {
            perror("fputs");
            return EXIT_FAILURE;
        }
    }

    if (ferror(stdin)) {
        perror("fgets");
        return EXIT_FAILURE;
    }

    fprintf(stderr, "Processed %zu lines, %zu bytes\n", line_count, total_bytes);
    return EXIT_SUCCESS;
}
