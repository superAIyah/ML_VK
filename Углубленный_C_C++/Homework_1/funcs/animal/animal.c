#include "animal.h"

void show_animal(FILE* output, Animal a) {  // вывод полей животного
    fprintf(output, "name = %s\n", a.name);
    fprintf(output, "type = %s\n", a.type);
    fprintf(output, "color = %s\n", a.color);
}

void show_by_group(FILE* output, Animal* mas, int n, char typ[]) {  // вывести животных по группе
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(mas[i].type, typ) == 0) {  // сравниваем типы животных
            fprintf(output, "%d animal:\n", cnt + 1);
            show_animal(output, mas[i]);
            cnt++;
        }
    }
    if (cnt == 0)
        fputs("По заданному виду нет животных", output);
}
