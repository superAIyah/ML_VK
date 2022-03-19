#include <gtest/gtest.h>
#define MAXSZ 1000

extern "C" {
    #include <stdio.h>
    #include <string.h>
    #include "constants.h"
    #include "animal.h"
    #include "safe_input.h"
}

void read_all(FILE* stream, char* res) { // функция, считывающая поток в строку
    char c;
    char* start = res;
    while( (c = fgetc(stream)) != EOF){
		*(start++) = c;
	}
    *(start) = '\0';
}

TEST(show_animal, Test_output) {
    //Arrange
    Animal tiger = {"Richard", "African", "orange"};
    char* expected = "name = Richard\n"
                     "type = African\n"
                     "color = orange\n";
    //ACT
    FILE* output = fopen("file.txt", "w");

    show_animal(output, tiger);
    fclose(output);

    output = fopen("file.txt", "r");
    char result[MAXSZ];
    read_all(output, result);
    fclose(output);
    //ASSERT
    EXPECT_EQ(strcmp(expected, result), 0);
}

class GroupTest : public ::testing::Test {
protected:
    char* animals_input = "tiger1\n"
                        "russian\n"
                        "orange\n"
                        "1\n"
                        "cat\n"
                        "american\n"
                        "black\n"
                        "1\n"
                        "leopard\n"
                        "russian\n"
                        "gray\n"
                        "0\n"; // 3 animals input to work with

    Animal mas[MAXLEN];
    FILE* input = fmemopen(animals_input, strlen(animals_input), "r");
    FILE* output = fopen("file.txt", "w");
    int n;

    void SetUp() override {
        n = input_animals(input, output, mas);
        fclose(output);
    };
};

TEST_F(GroupTest, group_exist) {
    char* expected_exist = "1 animal:\n" // animals "russian" group
                        "name = tiger1\n"
                        "type = russian\n"
                        "color = orange\n"
                        "2 animal:\n"
                        "name = leopard\n"
                        "type = russian\n"
                        "color = gray\n";

    output = fopen("file.txt", "w");
    char* typ = "russian";
    show_by_group(output, mas, n, typ);
    fclose(output);

    output = fopen("file.txt", "r");
    char result[MAXSZ];
    read_all(output, result);
    fclose(output);

    EXPECT_EQ(strcmp(result, expected_exist), 0);
}

TEST_F(GroupTest, group_NOT_exist) {
    char* expected_not_exist = "По заданному виду нет животных";
    output = fopen("file.txt", "w");
    char* typ = "Turkey";
    show_by_group(output, mas, n, typ);
    fclose(output);

    output = fopen("file.txt", "r");
    char result[MAXSZ];
    read_all(output, result);
    fclose(output);

    EXPECT_EQ(strcmp(result, expected_not_exist), 0);
}

//cd build/
//lcov -t "tests/test_funcs" -o coverage.info -c -d funcs/
//genhtml -o report coverage.info
//cd report
//python3 -m http.server 8000

TEST (wrong_input, symbol_and_overflow) {
    char* expected = "Вы ввели некорректные символы, попробуйте еще раз\n"
                     "Вы ввели кол-во символов, превышающее допустимое, попробуйте еще раз\n";

    int i;
    char wrong_input[1000]; // создаем строку где сначала вводим ...
    char* start = &wrong_input[0];
    char* wrong_name = "abracadabra7;!2d."; // ... недопустимые символы, ...
    for (i = 0; i < strlen(wrong_name); i++) {
        *(start + i) = *(wrong_name + i);
    }
    int tmp = strlen(wrong_name);
    wrong_input[tmp] = '\n';
    for (i = tmp + 1; i < 200; i++) // ... очень длинну строку 
        wrong_input[i] = '1';
    wrong_input[i] = '\n';
    wrong_input[i + 1] = 'a'; // finally correct string to finish function
    wrong_input[i + 2] = '\n'; // end of the string
    wrong_input[i + 3] = '\0';

    FILE* input = fmemopen(wrong_input, strlen(wrong_input), "r");
    FILE* output = fopen("file.txt", "w");

    char res[MAXLEN];
    get_correct_string(input, output, PATTERN_NICKNAME, res);
    fclose(output);

    output = fopen("file.txt", "r"); // считываем то, что записали
    char result[MAXSZ];
    read_all(output, result);
    fclose(output);
    EXPECT_EQ(strcmp(expected, result), 0);
    EXPECT_EQ(1, 1);
}

TEST(reg_exp_test, bad_pattern) {
    char* expected = "Ошибка в регулярном выражении PATTERN\n";

    char* bad_pattern = "[abracadabra7;!2d.[";
    FILE* input = fmemopen(bad_pattern, strlen(bad_pattern), "r");
    FILE* output = fopen("file.txt", "w");

    char res[MAXLEN];
    get_correct_string(input, output, bad_pattern, res);
    fclose(output);

    output = fopen("file.txt", "r"); // считываем то, что записали
    char result[MAXSZ];
    read_all(output, result);
    fclose(output);

    EXPECT_EQ(strcmp(result, expected), 0);
}