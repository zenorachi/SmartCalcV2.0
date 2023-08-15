CC = g++
CFLAGS := -lstdc++ -std=c++17 -Wall -Werror -Wextra

UNAME = $(shell uname)

OPEN :=
LEAKS :=

ifeq ($(UNAME), Linux)
OPEN += xdg-open
LEAKS += valgrind --leak-check=full -s -q --track-origins=yes
endif

ifeq ($(UNAME), Darwin)
OPEN += open
LEAKS += leaks -atExit --
endif

EXECUTABLE = test

SOURCE_MODEL = ./model/*.cc
SOURCE_TEST = ./tests/*.cc

INSTALL_SOURCE = model/*.cc model/*.h view/*.cc view/*.h controller/*.cc controller/*.h qcustomplot.cc qcustomplot.h SmartCalc.pro

all: install

install: clean uninstall
	@mkdir app
	cd app/ && cmake ../CMakeLists.txt && make

uninstall:
	@rm -rf ./app

clean:
	@rm -rf ./$(EXECUTABLE)
	@rm -rf *.gcno *.gcda
	@rm -rf ./report/
	@rm -rf *.o
	@rm -rf ~/Desktop/SmartCalc.tar.gz ~/Desktop/app
	@rm -rf ./docs/html ./docs/latex
	@rm -rf ./app

dvi:
	@cd docs && doxygen Doxyfile && open ./html/index.html

dist: install
	tar -cvzf ~/Desktop/SmartCalc.tar.gz ./app/SmartCalc-V2.0.app

tests:
	@$(CC) $(CFLAGS) $(SOURCE_MODEL) $(SOURCE_TEST) -lgtest -lgtest_main -o $(EXECUTABLE) && ./$(EXECUTABLE)

gcov_report: clean
	@$(CC) $(CFLAGS) $(SOURCE_MODEL) $(SOURCE_TEST) -lgtest_main -lgtest -o $(EXECUTABLE) --coverage
	@./$(EXECUTABLE)
	mkdir report
	gcovr -r . --html --html-details -o report/coverage_report.html
	rm -f *.gcda *.gcno
	$(OPEN) ./report/coverage_report.html

style:
	clang-format -n --style=google qcustomplot.h
	clang-format -n --style=google qcustomplot.cc
	clang-format -n --style=google ./model/*.h
	clang-format -n --style=google ./model/*.cc
	clang-format -n --style=google ./controller/*.h
	clang-format -n --style=google ./controller/*.cc
	clang-format -n --style=google ./view/*.h
	clang-format -n --style=google ./view/*.cc

clang_format:
	clang-format -i --style=google qcustomplot.h
	clang-format -i --style=google qcustomplot.cc
	clang-format -i --style=google ./model/*.h
	clang-format -i --style=google ./model/*.cc
	clang-format -i --style=google ./controller/*.h
	clang-format -i --style=google ./controller/*.cc
	clang-format -i --style=google ./view/*.h
	clang-format -i --style=google ./view/*.cc

leaks: tests
	@$(LEAKS) ./$(EXECUTABLE)

fsanitize:
	@$(CC) -fsanitize=address $(CFLAGS) $(SOURCE_MODEL) $(SOURCE_TEST) -lgtest -lgtest_main -o $(EXECUTABLE) && ./$(EXECUTABLE)

open:
	@$(OPEN) ./app/SmartCalc-V2.0.app

.PHONY: tests leaks clang-format
