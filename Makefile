# Based on http://c.learncodethehardway.org/book/ex28.html

CFLAGS=-std=c99 -g -Isrc
# -Wall -Wextra -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl -lm
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/world

# The Target Build
all: $(TARGET) tests

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): build $(OBJECTS)
	gcc $(CFLAGS) -o $@ $(SOURCES) $(LIBS) && echo ">> BUILD SUCCESS"

build:
	@mkdir -p build

# tests
$(TESTS):
	gcc $(CFLAGS) -o $@ $(@).c $(LIBS)

.PHONY: tests
tests: $(TESTS)
	sh ./tests/runtests.sh

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true

check-syntax:
	gcc -o build/nul -S ${CHK_SOURCES}
