#pragma once
#include <regex.h>
#include <stdio.h>
#include "animal.h"

// ф-ия считывания животного, принимает поток вывода и ввода, для того чтобы вывод функции можно было логировать
int input_animals(FILE* input, FILE* output, Animal* mas); // считать животное

// ф-ия считывает стркоу по паттерну. В случае не совпадения - запрашивает ввод еще
void get_correct_string(FILE* input, FILE* output, const char* pattern, char* str); // считать корректное имя по маске

// ф-ия считывает maxlen элементов из буфера и очищает его до '\n'. В случае переполнения вернет overflow_flag = 1
int safe_input(FILE* input, char* str, int maxlen); // считывание maxlen символов с очисткой буфера при привышении