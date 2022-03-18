#include "animal.h"

void show_animal(Animal a) { // вывод полей животного
    printf("name = %s\n", a.name);
    printf("type = %s\n", a.type);
    printf("color = %s\n", a.color);
}

void show_by_group(Animal* mas, int n, char typ[]) { // вывести животных по группе
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(mas[i].type, typ) == 0) { // сравниваем типы животных
            printf("%d animal:\n", cnt + 1);
            show_animal(mas[i]);
            cnt++;
        }
    }
    if (cnt == 0)
        puts("По заданному виду нет животных");
}