#pragma once
#include "constants.h"

typedef struct{
    char name[MAXLEN];
    char type[MAXLEN];
    char color[MAXLEN];
} Animal;

void show_by_group(Animal* mas, int n, char typ[]);
void show_animal(Animal a);