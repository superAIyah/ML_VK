#pragma once
#include "constants.h"
#include <stdio.h>

typedef struct{
    char name[MAXLEN];
    char type[MAXLEN];
    char color[MAXLEN];
} Animal;

void show_by_group(FILE* output, Animal* mas, int n, char typ[]);
void show_animal(FILE* output, Animal a);