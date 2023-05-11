#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_FILENAME_LEN 256
#define MAX_BUFFER_LEN 1024


int count_chars(const char* filename) {
    FILE* fp;
    int ch, count = 0;

    if ((fopen_s(&fp, filename, "r")) != 0) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    while ((ch = fgetc(fp)) != EOF) {
        count++;
    }

    fclose(fp);
    return count;
}

int count_words(const char* filename) {
    FILE* fp;
    int ch, count = 0;
    char buffer[MAX_BUFFER_LEN];
    size_t len;

    if ((fopen_s(&fp, filename, "r")) != 0) {
        perror("Failed to open file");
        exit(1);
    }

    while (fgets(buffer, MAX_BUFFER_LEN, fp)) {
        len = strlen(buffer);
        for (size_t i = 0; i < len; i++) {
            if (isspace(buffer[i]) || buffer[i] == ',') {
                count++;
            }
        }
    }

    fclose(fp);
    return count;
}

int main(int argc, char* argv[]) {
    char filename[MAX_FILENAME_LEN];
    int count;

    if (argc != 3) {
        exit(1);
    }

    if ((strcmp(argv[1], "-c") != 0) && (strcmp(argv[1], "-w") != 0)) {
        exit(1);
    }

    strncpy_s(filename, argv[2], MAX_FILENAME_LEN);

    if (strcmp(argv[1], "-c") == 0) {
        count = count_chars(filename);
        printf("×Ö·ûÊý: %d\n", count);
    }
    else {
        count = count_words(filename);
        printf("µ¥´ÊÊý: %d\n", count);
    }

    return 0;
}