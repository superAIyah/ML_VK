#include "safe_input.h"

int input_animals(FILE* input, FILE* output, Animal* mas) {
    int index = 0;  // индекс массива
    int stop = 0;  // флаг остановки ввода
    char str[MAXLEN];  // вводимый текст пользователем
    while (!stop) {
        Animal new_animal;
        fputs("Введите кличку нового животного\n", output);
        get_correct_string(input, output, PATTERN_NICKNAME, str);  // считываем корректную кличку
        snprintf(new_animal.name, MAXLEN, str);
        fputs("Введите вид животного\n", output);
        get_correct_string(input, output, PATTERN_ANIMAL, str);  // считываем корректный вид
        snprintf(new_animal.type, MAXLEN, str);
        fputs("Введите цвет нового животного.\n", output);
        get_correct_string(input, output, PATTERN_ANIMAL, str);  // считываем корректный цвет
        snprintf(new_animal.color, MAXLEN, str);
        mas[index] = new_animal;
        index++;
        fputs("Желаете продолжить ввод? \"1\" - да, \"0\" - нет\n", output);
        get_correct_string(input, output, PATTERN_ANSWER, str);
        if (str[0] == '0' && str[1] == '\0')
            stop = 1;
    }
    return index;
}

void get_correct_string(FILE* input, FILE* output, const char* pattern, char* str) {
    int regerr = 0;
    regex_t reg;
    regerr = regcomp(&reg, pattern, REG_EXTENDED);  // компиляция регулярного выражения
    if (regerr != 0) {
        fputs("Ошибка в регулярном выражении PATTERN\n", output);
        return;
    }
    do {
            regmatch_t pm;
            if (safe_input(input, str, MAXLEN)) {  // stack overflow
                fputs("Вы ввели кол-во символов, превышающее допустимое, попробуйте еще раз\n", output);
                continue;
            }
            regerr = regexec(&reg, str, 0, &pm, 0);  // проверка строки на соответсвие паттерна
            if (regerr != 0)
                fputs("Вы ввели некорректные символы, попробуйте еще раз\n", output);
        } while (regerr != 0);
}

int safe_input(FILE* input, char* str, int maxlen) {  // безопасное считывание строки без переполнения стека
    int index = 0;
    int overflow_flag = 0;
    char c = fgetc(input);
    while (c != '\n') {
        if (index == maxlen - 1) {  // введено больше MAXLEN букв
            overflow_flag = 1;  // флаг переполнения стека
        }
        if (!overflow_flag) {
            str[index] = c;
            index++;
        }
        c = fgetc(input);
    }
    str[index] = '\0';  // завершающий символ
    return overflow_flag;
}
