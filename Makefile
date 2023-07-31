G =g++ -std=c++17
GCC =$(G) -Wall -Wextra -Werror
LIBS =-lgtest

all: test

clean:
	@rm -rf s21_*o
	@rm -rf *.a
	@rm -rf a.out*
	@rm -rf gtest.*o
	@rm -rf report
	@rm -rf test*
	@rm -rf *.gcda
	@rm -rf *.dSYM

test: clean s21_matrix_oop.a
	$(GCC) s21_matrix_oop.a gtest.cc -o test $(LIBS)
	./test --gtest_repeat=10 --gtest_break_on_failure
	@make leak
	@make clang

s21_matrix_oop.a:
	$(G) -c s21_*.cc
	ar rc s21_matrix_oop.a s21_*.o
	ranlib s21_matrix_oop.a
	rm *.o

gcov_report: clean
	$(GCC) --coverage gtest.cc s21_*.cc -o test $(LIBS)
	chmod +x *
	./test
	lcov --ignore-errors mismatch -t "test" -o test.info --no-external -c -d .
	genhtml -o report/ test.info
	open ./report/index.html

leak:
	@echo --------------------MEMORY_LEAKS-----------------------
	@$(GCC) gtest.cc s21_*.cc -lgtest -o leaks -g
	CK_FORK=no leaks --atExit -- ./leaks
	@rm ./leaks

clang:
	@echo -------------------CLANG_FORMAT------------------------
	clang-format -n s21_*.cc s21_*.h gtest.cc
