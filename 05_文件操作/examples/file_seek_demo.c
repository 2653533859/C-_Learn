#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void dump_position(FILE *fp, const char *label) {
    long position = ftell(fp);
    if (position == -1L) {
        perror("ftell");
        exit(EXIT_FAILURE);
    }
    printf("%s -> position: %ld\n", label, position);
}

int main(void) {
    const char *filename = "seek_demo.txt";
    const char *text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    FILE *fp = fopen(filename, "w+");
    if (fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    size_t written = fwrite(text, sizeof(char), strlen(text), fp);
    if (written != strlen(text)) {
        perror("fwrite");
        fclose(fp);
        return EXIT_FAILURE;
    }

    dump_position(fp, "After write");

    if (fseek(fp, 0, SEEK_SET) != 0) {
        perror("fseek SEEK_SET");
        fclose(fp);
        return EXIT_FAILURE;
    }

    dump_position(fp, "Rewound");

    if (fseek(fp, 5, SEEK_SET) != 0) {
        perror("fseek SEEK_SET 5");
        fclose(fp);
        return EXIT_FAILURE;
    }

    int ch = fgetc(fp);
    if (ch == EOF) {
        perror("fgetc");
        fclose(fp);
        return EXIT_FAILURE;
    }
    printf("Character at offset 5: %c\n", ch);
    dump_position(fp, "After reading offset 5");

    if (fseek(fp, -3, SEEK_END) != 0) {
        perror("fseek SEEK_END -3");
        fclose(fp);
        return EXIT_FAILURE;
    }

    ch = fgetc(fp);
    if (ch == EOF) {
        perror("fgetc");
        fclose(fp);
        return EXIT_FAILURE;
    }
    printf("Third character from end: %c\n", ch);
    dump_position(fp, "After reading from end");

    if (fclose(fp) == EOF) {
        perror("fclose");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
