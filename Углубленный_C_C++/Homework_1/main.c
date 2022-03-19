#include "animal.h"
#include "constants.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *console_in = stdin;
    FILE *console_out = stdout;
    printf("HOOORAY3\n");
    Animal mas[MAXN];
    printf("Правила ввода: \n"
           "1) Вводимые пользователем строки могут содержать только буквы или "
           "знаки пробела."
           " Клички дополнительно могут содержать цифры. \n"
           "2) Длина одной строки не должна превышать %d символов\n",
           MAXLEN);
    int n = input_animals(console_in, console_out, mas);  // считаем животных
    for (int i = 0; i < n; i++)  // выведем всех животных после ввода
        show_animal(console_out, mas[i]);
    int stop_flag = 0;
    while (!stop_flag) {
        puts("Введите желаемый вид");
        char typ[MAXLEN];
        get_correct_string(console_in, console_out, PATTERN_ANIMAL,
                           typ);  // считаем вид животного
        show_by_group(console_out, mas, n,
                      typ);  // выведем всех представителей вида
        puts("Хотите продолжить? \"1\" - да, \"0\" - нет");
        char ans[MAXLEN];
        get_correct_string(console_in, console_out, PATTERN_ANSWER, ans);
        if (ans[0] == '0' && ans[1] == '\0')
            stop_flag = 1;
    }
    return 0;
}
