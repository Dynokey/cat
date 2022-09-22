CC = gcc 
GFLAGS = -Wall -Werror -Wextra  #-g -fsanitize=address
src = s21_cat.c s21_cat.h

all: s21_cat

s21_cat: $(src)
	$(CC) $(GFLAGS) $(src) -o s21_cat

test: s21_cat
	@cp ../../data-samples/s21_cat_test.sh s21_cat_test.sh
	@cp ../../data-samples/text.txt text.txt
	@chmod +x s21_cat_test.sh
	@./s21_cat_test.sh
	@cat -b -e -n -s -t -v text.txt > t1.txt && ./s21_cat -b -e -n -s -t -v text.txt > t2.txt && diff -s t1.txt t2.txt
	@cat -e -n -s -t -v text.txt > t1.txt && ./s21_cat -v -t -s -n -e text.txt > t2.txt && diff -s t1.txt t2.txt
	@cat -n -s -t -v text.txt > t1.txt && ./s21_cat -nstv text.txt > t2.txt && diff -s t1.txt t2.txt
	@cat -s -t -v text.txt > t1.txt && ./s21_cat -s -t -v text.txt > t2.txt && diff -s t1.txt t2.txt
	@cat -t -v text.txt > t1.txt && ./s21_cat -t -v text.txt > t2.txt && diff -s t1.txt t2.txt
	@cat -b text.txt > t1.txt && ./s21_cat --number-nonblank text.txt > t2.txt && diff -s t1.txt t2.txt
	@cat -n text.txt > t1.txt && ./s21_cat --number text.txt > t2.txt && diff -s t1.txt t2.txt
	@cat -s text.txt > t1.txt && ./s21_cat --squeeze-blank text.txt > t2.txt && diff -s t1.txt t2.txt
	
check:
	@cppcheck *.h *.c
	@cp ../../materials/linters/cpplint.py ./cpplint.py
	@cp ../../materials/linters/CPPLINT.cfg ./CPPLINT.cfg
	@python3 cpplint.py --extension=c *.c *.h
	@#cp ../../materials/linters/CPPLINT.cfg ./CPPLINT.cfg
	@#python3 ../../materials/linters/cpplint.py --extension=c *.c *.h
	@#cppcheck --enable=all --suppress=missingIncludeSystem *.c

valgrind:
	@cp ../../data-samples/text.txt text.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out_e.txt ./s21_cat -e text.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out_n.txt ./s21_cat -n text.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out_s.txt ./s21_cat -s text.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out_t.txt ./s21_cat -t text.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out_E.txt ./s21_cat -E text.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out_T.txt ./s21_cat -T text.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out_v.txt ./s21_cat -v text.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out_b.txt ./s21_cat -b text.txt

leaks: s21_cat
	CK_FORK=no leaks --atExit -- ./s21_cat text.txt

clean:
	@rm -rf s21_cat CPPLINT.cfg cpplint.py *.txt s21_cat_test.sh *o *out