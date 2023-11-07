#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <termios.h>
#include <ctype.h>
#include "utils.h"

void clear_terminal() {
    puts("\033[2J\033[1;1H");
}

int get_terminal_width() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void draw_line(int width, char c) {
    for (int i = 0; i < width; i++) {
        putchar(c);
    }
    putchar('\n');
}

void print_newlines(int n) {
    for (int i = 0; i < n; i++) {
        putchar('\n');
    }
}

void print_spaces(int n) {
    for (int i = 0; i < n; i++) {
        putchar(' ');
    }
}

void print_unordered_list(const char *list[]) {
    int width = get_terminal_width();
    int indent = 1;
    int i = 0;

    while (list[i] != NULL) {
        const char *word = list[i];
        int line_length = 0;

        while (*word != '\0') {
            if (line_length == 0) {
                print_spaces(indent);
                printf("- ");
                line_length = indent + 2;
            }

            const char *next_space = strchr(word, ' ');
            int word_length = next_space ? (int)(next_space - word) : strlen(word);

            if (line_length + word_length >= width) {
                putchar('\n');
                line_length = 0;
                continue;
            }

            printf("%.*s", word_length, word);
            line_length += word_length;

            if (next_space) {
                word = next_space + 1;
                putchar(' ');
                line_length++;
            } else {
                break;
            }
        }

        putchar('\n');
        i++;
    }
}

void wait_for_enter() {
    struct termios old_attr, new_attr;

    tcgetattr(STDIN_FILENO, &old_attr);

    new_attr = old_attr;
    new_attr.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSANOW, &new_attr);

    while (fgetc(stdin) != '\n') {}

    tcsetattr(STDIN_FILENO, TCSANOW, &old_attr);
}

int strcasestr(const char* str, const char* substr) {
    if (!str || !substr) {
        return 1; // Handle NULL pointers
    }

    size_t lenStr = strlen(str);
    size_t lenSubstr = strlen(substr);
    if (lenSubstr > lenStr) {
        return 1; // Substring is longer than string
    }

    for (size_t i = 0; i <= lenStr - lenSubstr; ++i) {
        int found = 0;
        for (size_t j = 0; j < lenSubstr; ++j) {
            if (tolower((unsigned char)str[i + j]) != tolower((unsigned char)substr[j])) {
                found = 1;
                break;
            }
        }
        if (found == 0) {
            return 0; // Substring found
        }
    }
    return 1; // Substring not found
}
