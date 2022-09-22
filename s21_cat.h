#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_
const char* ERR =
    "s21_cat: illegal option -%s\nusage: cat [-benstETv] [file ...]\n";
const char* ERR_1 = "s21_cat: %s: No such file or directory\n";

#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct flags {
  int flag_b;
  int flag_e;
  int flag_n;
  int flag_s;
  int flag_t;
  int flag_E;
  int flag_T;
  int flag_v;
  int flag_error;
} one;

void s21_print_cat(struct flags* p_one, char**);
int s21_parser(int, char**, struct flags* p_one);

#endif  //  SRC_CAT_S21_CAT_H_
