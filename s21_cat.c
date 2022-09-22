// Copyright 2022 by sparrvio

#include "./s21_cat.h"

int main(int argc, char* argv[]) {
  if (argc == 1) {
    while (1) putchar(getchar());
  }
  opterr = 0;
  struct flags one = {0};
  struct flags* p_one = &one;
  s21_parser(argc, argv, p_one);
  if (one.flag_error == 0) {
    while (optind < argc) {
      s21_print_cat(p_one, argv);
      optind++;
    }
  } else {
    fprintf(stderr, ERR, argv[one.flag_error]);
  }
  return 0;
}

int s21_parser(int argc, char** argv, struct flags* p_one) {
  const char* short_options = "benstETv";
  const struct option long_options[] = {{"number-nonblank", 0, NULL, 'b'},
                                        {"number", 0, NULL, 'n'},
                                        {"squeeze-blank", 0, NULL, 's'},
                                        {NULL, 0, NULL, 0}};
  int sym = 0;
  while (sym != -1) {
    sym = getopt_long(argc, argv, short_options, long_options, NULL);
    switch (sym) {
      case 'b':
        p_one->flag_b = 1;
        break;
      case 'e':
        p_one->flag_e = 1;
        p_one->flag_v = 1;
        break;
      case 'n':
        p_one->flag_n = 1;
        break;
      case 's':
        p_one->flag_s = 1;
        break;
      case 't':
        p_one->flag_t = 1;
        p_one->flag_v = 1;
        break;
      case 'E':
        p_one->flag_E = 1;
        break;
      case 'T':
        p_one->flag_T = 1;
        break;
      case 'v':
        p_one->flag_v = 1;
        break;
      case '?':
        p_one->flag_error = optind - 1;
        break;
    }
  }
  if (p_one->flag_b == 1) p_one->flag_n = 0;
  return 0;
}

void s21_print_cat(struct flags* p_one, char** argv) {
  int print_ch;
  int before_ch = '\n';
  int index = 0;
  int count = 1;
  char* file = argv[optind];
  FILE* mf;
  mf = fopen(file, "r+");
  if (mf != NULL) {
    while ((print_ch = getc(mf)) != EOF) {
      if (p_one->flag_s == 1) {
        if (print_ch == '\n') {
          index++;
          if (index == 3) {
            index--;
            continue;
          }
        } else {
          index = 0;
        }
      }
      if (p_one->flag_n == 1 && before_ch == '\n') {
        printf("%6d\t", count++);
      }
      if (p_one->flag_b == 1 && before_ch == '\n' && print_ch != '\n' &&
          print_ch != -1) {
        printf("%6d\t", count++);
      }
      if ((*p_one).flag_e == 1 && print_ch == '\n') {
        putchar('$');
      }
      if ((*p_one).flag_t == 1 && print_ch == '\t') {
        putchar('^');
        print_ch = 'I';
      }
      if ((*p_one).flag_v == 1) {
        if ((print_ch >= 0 && print_ch < 9) ||
            (print_ch > 10 && print_ch < 32)) {
          putchar('^');
          print_ch = print_ch + 64;
        } else if (print_ch > 127 && print_ch < 160) {
          printf("M-^");
          print_ch = print_ch - 64;
        } else if (print_ch == 127) {
          putchar('^');
          print_ch = '?';
        }
      }
      before_ch = print_ch;
      if (print_ch != -1) putchar(print_ch);
    }
  } else {
    fprintf(stderr, ERR_1, argv[optind]);
  }
  if (mf) fclose(mf);
}
