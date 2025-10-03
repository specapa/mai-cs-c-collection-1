#include <gtest/gtest.h>
#include <climits>

extern "C" {
    #include "file_process.h"
}

// Вспомогательная функция: строку → FILE*
FILE* make_input(const char* input) {
    FILE* f = tmpfile();
    fputs(input, f);
    rewind(f);
    return f;
}

// Вспомогательная функция: прочитать всё из FILE* в строку
std::string read_output(FILE* f) {
    fflush(f);
    rewind(f);
    std::string result;
    int c;
    while ((c = fgetc(f)) != EOF) {
        result.push_back((char)c);
    }
    return result;
}

TEST(FileProcTest, RemoveDigits) {
    FILE* in = make_input("a1b2c3\n");
    FILE* out = tmpfile();

    process_flag_d(in, out);

    std::string result = read_output(out);
    EXPECT_EQ(result, "abc\n");

    fclose(in);
    fclose(out);
}

TEST(FileProcTest, CountLetters) {
    FILE* in = make_input("abc123\nzz!\n");
    FILE* out = tmpfile();

    process_flag_i(in, out);

    std::string result = read_output(out);
    EXPECT_EQ(result, "3\n2\n");

    fclose(in);
    fclose(out);
}

TEST(FileProcTest, CountSpecials) {
    FILE* in = make_input("abc123?!\nZZ$@\n");
    FILE* out = tmpfile();

    process_flag_s(in, out);

    std::string result = read_output(out);
    EXPECT_EQ(result, "2\n2\n");  // ?! и $@
}

TEST(FileProcTest, ReplaceNonDigitsWithHex) {
    FILE* in = make_input("a1b\n");
    FILE* out = tmpfile();

    process_flag_a(in, out);

    std::string result = read_output(out);
    // 'a' = 0x61, 'b' = 0x62, '\n' = 0x0A
    EXPECT_EQ(result, "611620A"); // поправим пробелы ниже
}