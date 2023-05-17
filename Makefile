CC = g++
CFLAGS := -lstdc++ -std=c++17 -Wall -Werror -Wextra

UNAME = $(shell uname)

OPEN_REPORT :=
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
	qmake -o ./QMakefile SmartCalc.pro
	make -f ./QMakefile
	@cp ./SmartCalc.app/Contents/MacOS/SmartCalc ./app/
	@mv ./app/ ~/Desktop/

uninstall:
	@rm -rf ~/Desktop/app/
	@rm -rf ./SmartCalc.app

clean:
	@rm -rf ./$(EXECUTABLE)
	@rm -rf *.gcno *.gcda
	@rm -rf ./report/
	@rm -rf *.o
	@rm -rf QMakefile .qmake.stash ui_* moc_*
	@rm -rf ~/Desktop/SmartCalc.tar.gz ~/Desktop/SmartCalc
	@rm -rf ./docs/html ./docs/latex

dvi:
	@cd docs && doxygen Doxyfile && open ./html/index.html

dist: install
	tar -cvzf ~/Desktop/SmartCalc.tar.gz ./SmartCalc.app/Contents/MacOS/SmartCalc

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
	@~/Desktop/app/./SmartCalc

.PHONY: tests leaks clang-format