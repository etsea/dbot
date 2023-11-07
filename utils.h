#ifndef UTILS_H
#define UTILS_H

void clear_terminal();
int get_terminal_width();
void draw_line(int width, char c);
void print_newlines(int n);
void print_spaces(int n);
void print_unordered_list(const char *list[]);
void wait_for_enter();
int strcasestr(const char* str, const char* substr);

#endif
