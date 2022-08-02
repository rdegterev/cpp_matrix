LIB_NAME   = matrix_oop.a

L_NAME     = -lmatrix_oop

SRCS       = matrix_oop.cpp

T_NAME     = unit.check

T_SRCS     = matrix_test.cpp
             
REPORT_DIR = report

LCOV_INFO  = coverage.info

HEADER     = matrix_oop.h

OBJ_       = $(SRCS:%.cpp=%.o)

CC         = g++ -std=c++17
gcov  : CC = g++ -std=c++17 --coverage
debug : CC = g++ -std=c++17 -g
vg    : CC = g++ -std=c++17 -ggdb3
CFLAGS     = -I. -Wall -Wextra -Werror
LIBCHECK   = -lgtest

OS = $(shell uname)
ifeq ($(OS), Linux)
	LINUX_LIBS= -lrt -lpthread -lm
#	LINUX_LIBS=-lsubunit -lrt -lpthread -lm
else
	LINUX_LIBS=
endif

.PHONY : all \
         re \
         clean clear \
         cpplint cppcheck leaks vg \
         test gcov_report

# all: cpplint cppcheck $(LIB_NAME)
all: $(LIB_NAME)

re: clean all

gcov: re test

debug: re

gcov_report:
	@make -i gcov
	@lcov -o $(LCOV_INFO) -c -d . --no-external
	@genhtml -o $(REPORT_DIR) $(LCOV_INFO)
	@open  $(REPORT_DIR)/index.html

$(LIB_NAME): $(OBJ_) $(HEADER)
	@ar -rcs $(LIB_NAME) $?
	@ranlib $@
	@cp $@ lib$@

%.o: %.cpp $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(T_NAME): $(LIB_NAME) $(T_SRCS)
	@$(CC) $(T_SRCS) $(LIBCHECK) -o $(T_NAME) $(LINUX_LIBS) -L. $(L_NAME)

test: clean $(T_NAME)
	@./$(T_NAME)


leaks: clean $(T_NAME)
	CK_FORK=no leaks --atExit -- ./$(T_NAME)

vg: clean $(T_NAME)
	CK_FORK=no valgrind \
				--leak-check=full  --show-leak-kinds=all \
				--track-origins=yes --verbose \
				--log-file=valgrind.txt ./$(T_NAME)

clean:
	@rm -rf *.o *.a *.gcno */*.gcno *.gcda */*.gcda *.gcov */*.gcov *.app $(T_NAME) coverage** report tests/coverage** tests/*.dSYM valgrind*.*

cpplint:
	@python3 ../materials/linters/cpplint.py  --quiet --extension=cpp $(SRCS) $(T_SRCS) *.cpp

cppcheck:
	@cppcheck -q --enable=all --suppress=missingIncludeSystem $(SRCS) $(T_SRCS) *.cpp

check: clean cpplint cppcheck leaks gcov_report

doc:
	../materials/build/./run2.sh
