#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*FuncType)(FILE *fp, void*);

void compile_with_emcc(const char *source_file, const char *output_file) {
    // Формируем строку с командой для компиляции с помощью emcc
    char command[512];
    snprintf(command, sizeof(command), "emcc %s -s WASM=1 -o %s", source_file, output_file);

    // Вызов команды через system()
    int result = system(command);

    // Проверка успешности выполнения команды
    if (result == 0) {
        printf("Команда выполнена успешно: %s -> %s\n", source_file, output_file);
    } else {
        printf("Произошла ошибка при выполнении команды: %s -> %s\n", source_file, output_file);
    }
}