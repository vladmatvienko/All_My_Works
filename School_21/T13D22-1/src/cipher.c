#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int open_and_read_file(FILE **file);
void write_file(FILE *file, int *key_b);
void cezar_destroy_all_what_you_have();
int is_c_file(const char *filename);
int is_h_file(const char *filename);
void cezar_code(const char *filename, int shift);
void delete_symbols_in_h_files(const char *filename);

int main() {
    int choice = 0;
    char input[256];
    int key = 0;
    FILE *file = NULL;

    while (choice != -1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("n/a\n");
        } else {
            if (sscanf(input, "%d", &choice) != 1) {
                printf("n/a\n");
            } else {
                if (choice == 1) {
                    if (file != NULL) {
                        fclose(file);
                    }
                    key = open_and_read_file(&file);
                } else if (choice == 2) {
                    write_file(file, &key);
                } else if (choice == 3) {
                    cezar_destroy_all_what_you_have();
                } else if (choice == -1) {
                    choice = -1;
                } else {
                    printf("n/a\n");
                }
            }
        }
    }

    if (file != NULL) {
        fclose(file);
    }
    return 0;
}

int open_and_read_file(FILE **file) {
    int key = 0;
    char file_name[256];
    fgets(file_name, sizeof(file_name), stdin);
    file_name[strcspn(file_name, "\n")] = '\0';
    int p = 0;
    for (size_t i = 0; i < strlen(file_name); i++) {
        p = 0;
        if (file_name[i] == '.') {
            int count = strlen(file_name) - i - 1;
            if (count == 3) {
                if (file_name[i + 1] == 't' && file_name[i + 2] == 'x' && file_name[i + 3] == 't') {
                    *file = fopen(file_name, "r+");
                    if (*file == NULL) {
                        printf("n/a\n");
                        key = 1;
                        break;
                    }
                    char file_string[256];
                    while (fgets(file_string, sizeof(file_string), *file) != NULL) {
                        printf("%s", file_string);
                    }
                } else {
                    printf("n/a\n");
                    break;
                }
            } else {
                printf("n/a\n");
                break;
            }
            key = 1;
            break;
        }
        p = 1;
    }
    if (p == 1)
    {
        printf("n/a\n");
    }
    return key;
}

void write_file(FILE *file, int *key_b) {
    char file_string[256];
    if (fgets(file_string, sizeof(file_string), stdin) != NULL) {
        if (*key_b == 0)
        {
            printf("n/a\n");
            return;
        }
        file_string[strcspn(file_string, "\n")] = '\0';
        fprintf(file, "%s\n", file_string);
    } else {
        printf("n/a\n");
        return;
    }
    rewind(file);
    char file_string_out[256];
    while (fgets(file_string_out, sizeof(file_string_out), file) != NULL) {
        printf("%s", file_string_out);
    }
}

void cezar_destroy_all_what_you_have() {
    const char *dir_path = "ai_modules";
    int shift;
    scanf("%d", &shift);
    getchar();

    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        printf("n/a\n");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        char full_path[512];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        if (is_c_file(entry->d_name)) {
            cezar_code(full_path, shift);
        } else if (is_h_file(entry->d_name)) {
            delete_symbols_in_h_files(full_path);
        }
    }

    closedir(dir);
}

int is_c_file(const char *filename) {
    const char *ext = strrchr(filename, '.');
    return ext && strcmp(ext, ".c") == 0;
}

int is_h_file(const char *filename) {
    const char *ext = strrchr(filename, '.');
    return ext && strcmp(ext, ".h") == 0;
}

void cezar_code(const char *filename, int shift) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        printf("n/a\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *content = malloc(file_size + 1);
    if (content == NULL) {
        printf("n/a\n");
        fclose(file);
        return;
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0';

    for (int i = 0; i < file_size; i++) {
        if (isalpha(content[i])) {
            char base = islower(content[i]) ? 'a' : 'A';
            content[i] = (content[i] - base + shift) % 26 + base;
        }
    }
    rewind(file);
    fwrite(content, 1, file_size, file);
    fclose(file);
    free(content);
}

void delete_symbols_in_h_files(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("n/a\n");
        return;
    }
    fclose(file);
}
