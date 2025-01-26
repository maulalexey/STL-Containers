GCC = g++
CFLAGS  = -g -std=c++17 -Wall -Wextra
TEST_SOURCE := $(shell find . -iname "*.cpp")
HEADER_SOURCE := $(shell find . -iname "*.h")

# ifeq ($(shell uname -s),Darwin)
# 	TEST_FLAGS = -lgtest -lpthread
# else
# 	TEST_FLAGS = -lgtest -lpthread -lrt -lsubunit
# endif

TEST_FLAGS = -lgtest -lpthread

all: test

clean:
	rm -rf test

test: ${TEST_SOURCE} ${HEADER_SOURCE}
	$(GCC) $(CFLAGS) $^ -o $@ $(TEST_FLAGS)
	./$@

format:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n *.h
	clang-format -n tests/*.cpp
	clang-format -n containers/*.h
	clang-format -n containersplus/*.h
	clang-format -i *.h
	clang-format -i tests/*.cpp
	clang-format -i containers/*.h
	clang-format -i containersplus/*.h
	rm -rf .clang-format