#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 2

void insertLine(char ***lines, int *count, int *capacity, int index, const char *text);
void deleteLine(char ***lines, int *count, int index);
void printAllLines(char **lines, int count);
void freeAll(char ***lines, int *count);
void shrinkToFit(char ***lines, int *capacity, int count);
void saveToFile(char **lines, int count, const char *filename);
void loadFromFile(char ***lines, int *count, int *capacity, const char *filename);


char* allocString(const char *src) {
    char *p = (char*) malloc(strlen(src) + 1);
    if (!p) {
        printf("Memory error!\n");
        exit(1);
    }
    strcpy(p, src);
    return p;
}

int main() {
    char **lines = (char**) malloc(INITIAL_CAPACITY * sizeof(char*));
    if (!lines) { printf("Memory failed!\n"); return 0; }

    int count = 0, capacity = INITIAL_CAPACITY;

    insertLine(&lines, &count, &capacity, 0, "Hello World");
    insertLine(&lines, &count, &capacity, 1, "This is a simple editor");
    insertLine(&lines, &count, &capacity, 1, "Inserted line!");

    printAllLines(lines, count);

    deleteLine(&lines, &count, 1);
    printf("\nAfter delete:\n");
    printAllLines(lines, count);

    shrinkToFit(&lines, &capacity, count);

    saveToFile(lines, count, "output.txt");

    freeAll(&lines, &count);

    loadFromFile(&lines, &count, &capacity, "output.txt");
    printf("\nLoaded from file:\n");
    printAllLines(lines, count);

    freeAll(&lines, &count);
    return 0;
}


void insertLine(char ***lines, int *count, int *capacity, int index, const char *text) {
    if (*count == *capacity) {
        *capacity *= 2;
        *lines = (char**) realloc(*lines, *capacity * sizeof(char*));
        if (!*lines) { printf("Realloc failed!\n"); exit(1); }
    }

    for (int i = *count; i > index; i--) {
        (*lines)[i] = (*lines)[i-1];
    }

    (*lines)[index] = allocString(text);
    (*count)++;
}

void deleteLine(char ***lines, int *count, int index) {
    if (index < 0 || index >= *count) return;

    free((*lines)[index]);

    for (int i = index; i < *count - 1; i++) {
        (*lines)[i] = (*lines)[i+1];
    }

    (*count)--;
}

void printAllLines(char **lines, int count) {
    for (int i = 0; i < count; i++) {
        printf("%d: %s\n", i, lines[i]);
    }
}

void freeAll(char ***lines, int *count) {
    for (int i = 0; i < *count; i++) {
        free((*lines)[i]);
    }
    free(*lines);
    *lines = NULL;
    *count = 0;
}

void shrinkToFit(char ***lines, int *capacity, int count) {
    *capacity = count;
    *lines = (char**) realloc(*lines, count * sizeof(char*));
}

void saveToFile(char **lines, int count, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) { printf("File error!\n"); return; }

    for (int i = 0; i < count; i++)
        fprintf(f, "%s\n", lines[i]);

    fclose(f);
}

void loadFromFile(char ***lines, int *count, int *capacity, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) { printf("File not found.\n"); return; }

    *count = 0;
    *capacity = INITIAL_CAPACITY;
    *lines = (char**) malloc(*capacity * sizeof(char*));

    char buffer[500];

    while (fgets(buffer, sizeof(buffer), f)) {
        buffer[strcspn(buffer, "\n")] = 0;  
        insertLine(lines, count, capacity, *count, buffer);
    }

    fclose(f);
}

